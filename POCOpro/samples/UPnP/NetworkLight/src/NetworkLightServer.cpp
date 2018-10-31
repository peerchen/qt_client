//
// NetworkLightServer.cpp
//
// $Id: //poco/1.7/UPnP/samples/NetworkLight/src/NetworkLightServer.cpp#1 $
//
// This sample implements a server for the UPnP DimmableLight device.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//


#include "UPnPS/LightingControls1/SwitchPowerServerHelper.h"
#include "UPnPS/LightingControls1/DimmingServerHelper.h"
#include "Poco/UPnP/SOAP/Listener.h"
#include "Poco/UPnP/SOAP/RequestHandler.h"
#include "Poco/UPnP/GENA/TransportFactory.h"
#include "Poco/UPnP/GENA/Listener.h"
#include "Poco/UPnP/GENA/RequestHandler.h"
#include "Poco/UPnP/SSDP/SSDPResponder.h"
#include "Poco/UPnP/SSDP/Advertisement.h"
#include "Poco/UPnP/URN.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/Timer.h"
#include "Poco/UUID.h"
#include "DimmableLight.h"
#include "SwitchPowerImpl.h"
#include "DimmingImpl.h"
#include "RootDeviceDescription.h"
#include "SwitchPower1.h"
#include "Dimming1.h"
#include "IndexPage.h"
#include <iostream>


using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::UPnP::SSDP::SSDPResponder;
using Poco::UPnP::SSDP::Advertisement;


class NotFoundPage: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");
		response.send()
			<< "<html><head><title>Not Found</title></head><body><h1>Not Found</h1></body>";
	}
};


class RequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	RequestHandlerFactory(DimmableLight& dimmableLight, Poco::UPnP::SOAP::Listener& soapListener, Poco::UPnP::GENA::Listener& genaListener):
		_dimmableLight(dimmableLight),
		_soapListener(soapListener),
		_genaListener(genaListener),
		_logger(Poco::Logger::get("RequestHandlerFactory"))
	{
	}
	
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
	{
		const std::string& path = request.getURI();
		const std::string& method = request.getMethod();
		if (_logger.information())
		{
			_logger.information(method + " " + path + " (" + request.clientAddress().toString() + ")");
		}
		
		// check required for UPnP conformance tests
		if (method == Poco::Net::HTTPRequest::HTTP_GET || method == Poco::Net::HTTPRequest::HTTP_HEAD || method == Poco::Net::HTTPRequest::HTTP_POST)
		{
			if (path == "/upnp/rootdevice.xml")
				return new RootDeviceDescription;
			else if (path == "/upnp/SwitchPower1.xml")
				return new SwitchPower1;
			else if (path == "/upnp/Dimming1.xml")
				return new Dimming1;
			else if (path.compare(0, 14, "/upnp-control/") == 0)
				return new Poco::UPnP::SOAP::RequestHandler(_soapListener);
			else if (path == "/" || path == "/index.html")
				return new IndexPage(_dimmableLight);
			else
				return new NotFoundPage;
		}
		else if (method == "SUBSCRIBE" || method == "UNSUBSCRIBE")
		{
			if (path.compare(0, 15, "/upnp-eventing/") == 0)
				return new Poco::UPnP::GENA::RequestHandler(_genaListener);
			else
				return 0;
		}
		else return 0;		
	}
	
private:
	DimmableLight& _dimmableLight;
	Poco::UPnP::SOAP::Listener& _soapListener;
	Poco::UPnP::GENA::Listener& _genaListener;
	Poco::Logger& _logger;
};


class NetworkLightServerApp: public ServerApplication
{
public:
	NetworkLightServerApp(): 
		_helpRequested(false)
	{
	}
	
	~NetworkLightServerApp()
	{
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); 
		ServerApplication::initialize(self);
	}
		
	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<NetworkLightServerApp>(this, &NetworkLightServerApp::handleHelp)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A UPnP sample application implementing a DimmableLight device.");
		helpFormatter.format(std::cout);
	}

	Poco::Net::NetworkInterface findActiveNetworkInterface()
	{
		Poco::Net::NetworkInterface::NetworkInterfaceList ifs = Poco::Net::NetworkInterface::list();
		for (Poco::Net::NetworkInterface::NetworkInterfaceList::iterator it = ifs.begin(); it != ifs.end(); ++it)
		{
			if (!it->address().isWildcard() && !it->address().isLoopback() && it->supportsIPv4()) return *it;
		}
		throw Poco::IOException("No configured Ethernet interface found");
	}
	
	int main(const std::vector<std::string>& args)
	{
		if (!_helpRequested)
		{
			Poco::Util::Timer timer;
			DimmableLight dimmableLight;

			// Find network interface
			std::string mcastInterfaceName = config().getString("upnp.interface", "");
			Poco::Net::NetworkInterface mcastInterface(mcastInterfaceName.empty() ? findActiveNetworkInterface() : Poco::Net::NetworkInterface::forName(mcastInterfaceName, Poco::Net::NetworkInterface::IPv4_ONLY));
			Poco::Net::IPAddress ipAddress(mcastInterface.address());

			logger().information(Poco::format("Using multicast network interface %s (%s).", mcastInterface.name(), ipAddress.toString()));
			
			// Set up HTTP server
			Poco::UInt16 httpPort = config().getInt("http.port", 8000);
			Poco::Net::HTTPServerParams::Ptr pHTTPParams = new Poco::Net::HTTPServerParams;
			pHTTPParams->setSoftwareVersion(config().getString("http.softwareVersion", ""));
			pHTTPParams->setMaxQueued(config().getInt("http.maxQueued", 4));
			pHTTPParams->setMaxThreads(config().getInt("http.maxThreads", 4));
			pHTTPParams->setTimeout(Poco::Timespan(config().getInt("http.timeout", 5), 0));
			pHTTPParams->setKeepAlive(config().getBool("http.keepAlive", false));
			pHTTPParams->setMaxKeepAliveRequests(config().getInt("http.maxKeepAliveRequests", 10));
			pHTTPParams->setKeepAliveTimeout(Poco::Timespan(config().getInt("http.keepAliveTimeout", 10), 0));
						
			// Set up UPnP SOAP and GENA
			Poco::UPnP::GENA::TransportFactory::registerFactory();
			Poco::Net::SocketAddress httpSA(ipAddress, httpPort);	
			Poco::UPnP::SOAP::Listener::Ptr pSOAPListener = new Poco::UPnP::SOAP::Listener(httpSA.toString());
			Poco::UPnP::GENA::Listener::Ptr pGENAListener = new Poco::UPnP::GENA::Listener(httpSA.toString(), timer);
			Poco::Net::ServerSocket httpSocket(httpPort);
			Poco::Net::HTTPServer httpServer(new RequestHandlerFactory(dimmableLight, *pSOAPListener, *pGENAListener), httpSocket, pHTTPParams);
			httpServer.start();
			
			std::string soapListenerId = Poco::RemotingNG::ORB::instance().registerListener(pSOAPListener);
			std::string genaListenerId = Poco::RemotingNG::ORB::instance().registerListener(pGENAListener);
			
			// Register UPnP services
			Poco::SharedPtr<SwitchPowerImpl> pSwitchPowerImpl = new SwitchPowerImpl(dimmableLight);
			UPnPS::LightingControls1::SwitchPowerServerHelper::registerObject(pSwitchPowerImpl, "SwitchPower.1", soapListenerId);
			std::string switchPowerURI = UPnPS::LightingControls1::SwitchPowerServerHelper::registerObject(pSwitchPowerImpl, "SwitchPower.1", genaListenerId);
			Poco::SharedPtr<DimmingImpl> pDimmingImpl = new DimmingImpl(dimmableLight);
			UPnPS::LightingControls1::DimmingServerHelper::registerObject(pDimmingImpl, "Dimming.1", soapListenerId);
			std::string dimmableURI = UPnPS::LightingControls1::DimmingServerHelper::registerObject(pDimmingImpl, "Dimming.1", genaListenerId);

			// Enable GENA events
			UPnPS::LightingControls1::SwitchPowerServerHelper::enableEvents(switchPowerURI, pGENAListener->protocol());
			pGENAListener->registerStateProvider(switchPowerURI, pSwitchPowerImpl.get());
			UPnPS::LightingControls1::DimmingServerHelper::enableEvents(dimmableURI, pGENAListener->protocol());
			pGENAListener->registerStateProvider(dimmableURI, pDimmingImpl.get());
	
			// Set up SSDP and publish services
			Poco::Net::SocketAddress ssdpSA(Poco::Net::IPAddress(), SSDPResponder::MULTICAST_PORT);
			Poco::Net::MulticastSocket ssdpSocket(ssdpSA, true);
			ssdpSocket.setLoopback(true);
			ssdpSocket.setTimeToLive(4);
			ssdpSocket.setInterface(mcastInterface);
			SSDPResponder responder(timer, ssdpSocket);
			std::string deviceLocation = "http://" + httpSA.toString() + "/upnp/rootdevice.xml";
			Poco::UUID deviceUUID(config().getString("upnp.device.uuid"));
			int adLifetime = config().getInt("upnp.adLifetime", 60);
			responder.publish(new Advertisement(Advertisement::AD_ROOT_DEVICE, deviceUUID, deviceLocation, adLifetime));
			responder.publish(new Advertisement(Advertisement::AD_DEVICE, deviceUUID, deviceLocation, adLifetime));
			responder.publish(new Advertisement(deviceUUID, Poco::UPnP::URN("urn:schemas-upnp-org:device:DimmableLight:1"), deviceLocation, adLifetime));
			responder.publish(new Advertisement(deviceUUID, Poco::UPnP::URN("urn:schemas-upnp-org:service:SwitchPower:1"), deviceLocation, adLifetime));
			responder.publish(new Advertisement(deviceUUID, Poco::UPnP::URN("urn:schemas-upnp-org:service:Dimming:1"), deviceLocation, adLifetime));
			ssdpSocket.joinGroup(responder.groupAddress().host(), mcastInterface);
			responder.start();
									
			waitForTerminationRequest();
			
			// Shut down
			httpServer.stop();
			responder.stop();
			Poco::Thread::sleep(500); // wait for advertisements to be sent
			ssdpSocket.leaveGroup(responder.groupAddress().host(), mcastInterface);

			Poco::RemotingNG::ORB::instance().shutdown();
		}
		return Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
};


POCO_SERVER_MAIN(NetworkLightServerApp)

