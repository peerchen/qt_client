//
// NetworkLightController.cpp
//
// $Id: //poco/1.7/UPnP/samples/NetworkLightController/src/NetworkLightController.cpp#1 $
//
// This sample implements a simple control point for the NetworkLight device.
//
// Copyright (c) 2008-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/Util/Application.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/Util/XMLConfiguration.h"
#include "Poco/UPnP/SSDP/SSDPResponder.h"
#include "Poco/UPnP/SSDP/Advertisement.h"
#include "Poco/UPnP/SOAP/TransportFactory.h"
#include "Poco/UPnP/GENA/Listener.h"
#include "Poco/UPnP/GENA/RequestHandler.h"
#include "Poco/UPnP/ServiceDesc/ServiceCollection.h"
#include "Poco/UPnP/URN.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/URI.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Delegate.h"
#include "Poco/AutoPtr.h"
#include "Poco/Format.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "UPnPS/LightingControls1/SwitchPowerProxy.h"
#include "UPnPS/LightingControls1/SwitchPowerClientHelper.h"
#include "UPnPS/LightingControls1/DimmingProxy.h"
#include "UPnPS/LightingControls1/DimmingClientHelper.h"
#include <iostream>


using Poco::Util::Application;
using Poco::UPnP::SSDP::SSDPResponder;
using Poco::UPnP::SSDP::Advertisement;


class RequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	RequestHandlerFactory(Poco::UPnP::GENA::Listener& genaListener):
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
		
		if (method == "NOTIFY")
		{
			return new Poco::UPnP::GENA::RequestHandler(_genaListener);
		}
		else return 0;
	}
	
private:
	Poco::UPnP::GENA::Listener& _genaListener;
	Poco::Logger& _logger;
};


class NetworkLightController: public Application
{
public:
	NetworkLightController()
	{
	}
	
	~NetworkLightController()
	{
	}

protected:
	class FetchDeviceDescriptionTask: public Poco::Util::TimerTask
	{
	public:
		FetchDeviceDescriptionTask(NetworkLightController& nlc, const std::string& location):
			_nlc(nlc),
			_location(location)
		{
		}
		
		void run()
		{
			_nlc.fetchDeviceDescription(_location);
		}
		
	private:
		NetworkLightController& _nlc;
		std::string _location;
	};
	
	void fetchDeviceDescription(const std::string& location)
	{
		logger().information("Retrieving device description...");
		
		Poco::URI uri(location);
		Poco::SharedPtr<std::istream> pStream = Poco::URIStreamOpener::defaultOpener().open(uri);
		Poco::AutoPtr<Poco::Util::XMLConfiguration> pDeviceDescription = new Poco::Util::XMLConfiguration(*pStream);

		Poco::FastMutex::ScopedLock lock(_mutex);
		
		Poco::URI baseURL(pDeviceDescription->getString("URLBase", location));
		int i = 0;
		while (pDeviceDescription->hasProperty(Poco::format("device.serviceList.service[%d].serviceType", i)))
		{
			std::string serviceType = pDeviceDescription->getString(Poco::format("device.serviceList.service[%d].serviceType", i));
			std::string serviceId   = pDeviceDescription->getString(Poco::format("device.serviceList.service[%d].serviceId", i));
			std::string controlURL  = pDeviceDescription->getString(Poco::format("device.serviceList.service[%d].controlURL", i));
			std::string eventSubURL = pDeviceDescription->getString(Poco::format("device.serviceList.service[%d].eventSubURL", i), "");
			std::string scpdURL     = pDeviceDescription->getString(Poco::format("device.serviceList.service[%d].SCPDURL", i));
			
			logger().information(Poco::format("Found: %s.", serviceType));				
			if (serviceType == "urn:schemas-upnp-org:service:SwitchPower:1")
			{
				if (!_pSwitchPower)
				{
					Poco::URI switchPowerControlURL(baseURL, controlURL);
					_pSwitchPower = UPnPS::LightingControls1::SwitchPowerClientHelper::find(switchPowerControlURL.toString());
					Poco::URI switchPowerEventSubURL(baseURL, eventSubURL);
					_pSwitchPower.cast<UPnPS::LightingControls1::SwitchPowerProxy>()->remoting__setEventURI(switchPowerEventSubURL);
					_switchPowerFound.set();
					Poco::URI switchPowerSCPDURL(baseURL, scpdURL);
					_services.loadService(serviceId, serviceType, switchPowerSCPDURL);
				}
			}
			else if (serviceType == "urn:schemas-upnp-org:service:Dimming:1")
			{
				if (!_pDimming)
				{
					Poco::URI dimmingControlURL(baseURL, controlURL);
					_pDimming = UPnPS::LightingControls1::DimmingClientHelper::find(dimmingControlURL.toString());
					Poco::URI dimmingEventSubURL(baseURL, eventSubURL);
					_pDimming.cast<UPnPS::LightingControls1::DimmingProxy>()->remoting__setEventURI(dimmingEventSubURL);
					_dimmingFound.set();
					Poco::URI dimmingSCPDURL(baseURL, scpdURL);
					_services.loadService(serviceId, serviceType, dimmingSCPDURL);
				}
			}
			i++;
		}
	}
	
	void onAdvertisementSeen(Advertisement::Ptr& pAdvertisement)
	{
		if (pAdvertisement->type() == Advertisement::AD_DEVICE_TYPE)
		{
			if (pAdvertisement->notificationType() == "urn:schemas-upnp-org:device:DimmableLight:1")
			{
				std::string location = pAdvertisement->location();
				logger().information(Poco::format("Found DimmableLight device at %s.", location));
				
				Poco::FastMutex::ScopedLock lock(_mutex);
				if (!_pSwitchPower || !_pDimming)
				{
					_timer.schedule(new FetchDeviceDescriptionTask(*this, location), Poco::Timestamp());
				}
			}
		}
	}
	
	void onStatusChanged(const bool& status)
	{
		logger().information(Poco::format("Status changed to %s.", std::string(status ? "ON" : "OFF")));
	}
	
	void onLoadLevelStatusChanged(const Poco::UInt8& level)
	{
		logger().information(Poco::format("Load level changed to %u.", static_cast<unsigned>(level)));
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

	void listServices()
	{
		Poco::UPnP::ServiceDesc::ServiceCollection::ServiceInfos infos = _services.services();
		for (Poco::UPnP::ServiceDesc::ServiceCollection::ServiceInfos::const_iterator it = infos.begin(); it != infos.end(); ++it)
		{
			std::cout << "ServiceId:   " << it->first << std::endl;
			std::cout << "ServiceType: " << it->second->serviceType << std::endl;
			std::cout << "Actions:" << std::endl;
			const Poco::UPnP::ServiceDesc::Service::Actions& actions = it->second->pService->actions();
			for (Poco::UPnP::ServiceDesc::Service::Actions::const_iterator ita = actions.begin(); ita != actions.end(); ++ita)
			{
				std::cout << "\t" << (*ita)->name() << std::endl;
			}
		}
	}
	
	void printHelp()
	{
		std::cout 
			<< "The following commands are available:\n" 
			<< "\t 0: Turn the light OFF.\n"
			<< "\t 1: Turn the light ON.\n"
			<< "\t +: Step up brightness.\n"
			<< "\t -: Step down brightness.\n"
			<< "\t >: Ramp up brightness.\n"
			<< "\t <: Ramp down brightness.\n"
			<< "\t S: List available services.\n"
			<< "\t Q: Quit." << std::endl;
	}

	int main(const std::vector<std::string>& args)
	{
		// Register SOAP transport
		Poco::UPnP::SOAP::TransportFactory::registerFactory();
		
		// Register HTTPStreamFactory
		Poco::Net::HTTPStreamFactory::registerFactory();
	
		// Find suitable multicast interface
		Poco::Net::NetworkInterface mcastInterface(findActiveNetworkInterface());
		Poco::Net::IPAddress ipAddress(mcastInterface.address());
		logger().information(Poco::format("Using multicast network interface %s (%s).", mcastInterface.name(), ipAddress.toString()));

		// Set up multicast socket and SSDPResponder
		Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), SSDPResponder::MULTICAST_PORT);
		Poco::Net::MulticastSocket socket(sa, true);
		socket.setTimeToLive(4);
		socket.setInterface(mcastInterface);
		SSDPResponder ssdpResponder(_timer, socket);
		ssdpResponder.advertisementSeen += Poco::delegate(this, &NetworkLightController::onAdvertisementSeen);
		socket.joinGroup(ssdpResponder.groupAddress().host(), mcastInterface);
		ssdpResponder.start();
		
		// Search for DimmableLight devices
		ssdpResponder.search("urn:schemas-upnp-org:device:DimmableLight:1");
		
		// Set up HTTP server for GENA and GENA Listener
		Poco::Net::ServerSocket httpSocket(Poco::Net::SocketAddress(ipAddress, 0));
		Poco::Net::SocketAddress httpSA(ipAddress, httpSocket.address().port());
		Poco::UPnP::GENA::Listener::Ptr pGENAListener = new Poco::UPnP::GENA::Listener(httpSA.toString(), _timer);
		Poco::Net::HTTPServer httpServer(new RequestHandlerFactory(*pGENAListener), httpSocket, new Poco::Net::HTTPServerParams);
		httpServer.start();		
		Poco::RemotingNG::ORB::instance().registerListener(pGENAListener);
		
		// Wait until services have been found
		logger().information("Waiting for services...");
		_switchPowerFound.wait();
		_dimmingFound.wait();
		
		// Subscribe to events
		logger().information("Subscribing for events...");
		_pSwitchPower->statusChanged += Poco::delegate(this, &NetworkLightController::onStatusChanged);
		_pSwitchPower->remoting__enableEvents(pGENAListener);
		_pDimming->loadLevelStatusChanged += Poco::delegate(this, &NetworkLightController::onLoadLevelStatusChanged);
		_pDimming->remoting__enableEvents(pGENAListener);
		
		bool status = false;
		_pSwitchPower->getStatus(status);
		logger().information(std::string("The light is ") + (status ? "ON" : "OFF") + ".");
		
		bool quit = false;
		while (!quit)
		{
			std::cout << "Enter command (0, 1, +, -, >, <, S, Q, H for Help): " << std::flush;
			char cmd;
			std::cin >> cmd;
			try
			{
				switch (cmd)
				{
				case '0':
					_pSwitchPower->setTarget(false);
					break;
				case '1':
					_pSwitchPower->setTarget(true);
					break;
				case '+':
					_pDimming->stepUp();
					break;
				case '-':
					_pDimming->stepDown();
					break;
				case '>':
					_pDimming->startRampUp();
					break;
				case '<':
					_pDimming->startRampDown();
					break;
				case 'h':
				case 'H':
					printHelp();
					break;
				case 's':
				case 'S':
					listServices();
					break;
				case 'q':
				case 'Q':
					quit = true;
					break;
				default:
					std::cout << "Unknown command: " << cmd << std::endl;
					break;
				}
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
			}
		}

		// Shut down 
		_pSwitchPower->statusChanged -= Poco::delegate(this, &NetworkLightController::onStatusChanged);
		_pDimming->loadLevelStatusChanged += Poco::delegate(this, &NetworkLightController::onLoadLevelStatusChanged);
		httpServer.stop();

		ssdpResponder.stop();
		socket.leaveGroup(ssdpResponder.groupAddress().host(), mcastInterface);
		ssdpResponder.advertisementSeen -= Poco::delegate(this, &NetworkLightController::onAdvertisementSeen);
		
		Poco::RemotingNG::ORB::instance().shutdown();
		
		return Application::EXIT_OK;
	}
	
private:
	Poco::Util::Timer _timer;
	std::string _usn;
	UPnPS::LightingControls1::ISwitchPower::Ptr _pSwitchPower;
	UPnPS::LightingControls1::IDimming::Ptr     _pDimming;
	Poco::Event _switchPowerFound;
	Poco::Event _dimmingFound;
	Poco::UPnP::ServiceDesc::ServiceCollection _services;
	Poco::FastMutex _mutex;
	
	friend class FetchDeviceDescriptionTask;
};


POCO_APP_MAIN(NetworkLightController)
