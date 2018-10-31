//
// SimpleMediaServer.cpp
//
// $Id: //poco/1.7/UPnP/samples/SimpleMediaServer/src/SimpleMediaServer.cpp#1 $
//
// This sample implements a simple UPnP MediaServer.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//


#include "UPnPS/MediaServer1/ContentDirectory1ServerHelper.h"
#include "UPnPS/MediaServer1/ConnectionManager1ServerHelper.h"
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
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/FileStream.h"
#include "Poco/UUID.h"
#include "Poco/Buffer.h"
#include "Poco/Ascii.h"
#include "ContentDirectory1Impl.h"
#include "ConnectionManager1Impl.h"
#include "RootDeviceDescription.h"
#include "ContentDirectory1.h"
#include "ConnectionManager1.h"
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


class MediaRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	enum
	{
		BUFFER_SIZE = 8192
	};
	
	MediaRequestHandler(const std::string& mediaPath):
		_mediaPath(mediaPath)
	{
	}
	
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
	{
		std::string decodedPath;
		Poco::URI::decode(request.getURI(), decodedPath);
		Poco::Path requestPath(decodedPath, Poco::Path::PATH_UNIX);
		Poco::Path mediaPath(_mediaPath);
		mediaPath.makeDirectory();
		for (int i = 1; i < requestPath.depth(); i++)
		{
			mediaPath.pushDirectory(requestPath[i]);
		}
		mediaPath.setFileName(requestPath.getFileName());
		Poco::File mediaFile(mediaPath.toString());
		if (mediaFile.path().find("..") != std::string::npos)
		{
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			response.send();
		}
		if (mediaFile.exists())
		{
			Poco::Timestamp dateTime    = mediaFile.getLastModified();
			Poco::File::FileSize length = mediaFile.getSize();
			std::string contentType     = ContentDirectory1Impl::contentTypeForExtension(mediaPath.getExtension());
			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_HEAD || request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
			{
				response.set("Last-Modified", Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::HTTP_FORMAT));
				response.set("Accept-Ranges", "bytes");
				response.setContentType(contentType);
				response.set("contentFeatures.dlna.org", ContentDirectory1Impl::dlnaContentFeaturesForExtension(mediaPath.getExtension()));
				response.set("transferMode.dlna.org", request.get("transferMode.dlna.org", "Streaming"));
			}
			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_HEAD)
			{
#if defined(POCO_HAVE_INT64)	
				response.setContentLength64(length);
#else
				response.setContentLength(static_cast<int>(length));
#endif
				response.send();				
			}
			else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
			{
				if (request.has("Range"))
				{
					Poco::File::FileSize rangeStart  = 0;
					Poco::File::FileSize rangeLength = 0;
					if (parseRange(request.get("Range"), length, rangeStart, rangeLength))
					{
						sendFileRange(response, mediaPath.toString(), length, rangeStart, rangeLength);
					}
					else
					{
						response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_REQUESTED_RANGE_NOT_SATISFIABLE);
						response.send();
					}
				}
				else
				{
					response.sendFile(mediaPath.toString(), contentType);
				}
			}
			else
			{
				response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
				response.send();
			}
		}
		else 
		{
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
			response.send();
		}
	}
	
	bool parseRange(const std::string& range, Poco::File::FileSize fileSize, Poco::File::FileSize& rangeStart, Poco::File::FileSize& rangeLength)
	{
		std::string::const_iterator it = range.begin();
		std::string::const_iterator end = range.end();
		while (it != end && Poco::Ascii::isSpace(*it)) ++it;
		std::string unit;
		while (it != end && *it != '=') unit += *it++;
		if (unit == "bytes" && it != end)
		{
			++it;
			if (it != end && *it == '-')
			{
				++it;
				rangeLength = 0;
				while (it != end && Poco::Ascii::isDigit(*it))
				{
					rangeLength *= 10;
					rangeLength += *it - '0';
					++it;
				}
				rangeStart = fileSize - rangeLength;
				return true;
			}
			else if (it != end && Poco::Ascii::isDigit(*it))
			{
				rangeStart = 0;
				while (it != end && Poco::Ascii::isDigit(*it))
				{
					rangeStart *= 10;
					rangeStart += *it - '0';
					++it;
				}
				if (it != end && *it == '-')
				{
					++it;
					if (it != end)
					{
						rangeLength = 0;
						while (it != end && Poco::Ascii::isDigit(*it))
						{
							rangeLength *= 10;
							rangeLength += *it - '0';
							++it;
						}
						rangeLength = rangeLength - rangeStart + 1;
					}
					else
					{
						rangeLength = fileSize - rangeStart;
					}
					return true;
				}
			}
		}
		return false;
	}
	
	void sendFileRange(Poco::Net::HTTPServerResponse& response, const std::string& path, Poco::File::FileSize length, Poco::File::FileSize rangeStart, Poco::File::FileSize rangeLength)
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT);
#if defined(POCO_HAVE_INT64)	
		response.setContentLength64(rangeLength);
#else
		response.setContentLength(static_cast<int>(rangeLength));
#endif
		response.set("Content-Range", Poco::format("bytes %?d-%?d/%?d", rangeStart, rangeStart + rangeLength - 1, length));
		std::ostream& ostr = response.send();
		
		Poco::FileInputStream istr(path);
		istr.seekg(static_cast<std::streampos>(rangeStart));
		Poco::Buffer<char> buffer(BUFFER_SIZE);
		while (rangeLength > 0)
		{
			std::streamsize chunk = BUFFER_SIZE;
			if (chunk > rangeLength) chunk = static_cast<std::streamsize>(rangeLength);
			istr.read(buffer.begin(), chunk);
			std::streamsize n = istr.gcount();
			if (n == 0) break;
			ostr.write(buffer.begin(), n);
			rangeLength -= n;
		}
	}
	
private:
	std::string _mediaPath;
};


class RequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	RequestHandlerFactory(const std::string& mediaPath, Poco::UPnP::SOAP::Listener& soapListener, Poco::UPnP::GENA::Listener& genaListener):
		_mediaPath(mediaPath),
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
			else if (path == "/upnp/ContentDirectory1.xml")
				return new ContentDirectory1;
			else if (path == "/upnp/ConnectionManager1.xml")
				return new ConnectionManager1;
			else if (path.compare(0, 14, "/upnp-control/") == 0)
				return new Poco::UPnP::SOAP::RequestHandler(_soapListener);
			else if (path.compare(0, 7, "/media/") == 0)
				return new MediaRequestHandler(_mediaPath);
			else if (path == "/" || path == "/index.html")
				return new IndexPage;
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
	std::string _mediaPath;
	Poco::UPnP::SOAP::Listener& _soapListener;
	Poco::UPnP::GENA::Listener& _genaListener;
	Poco::Logger& _logger;
};


class SimpleMediaServerApp: public ServerApplication
{
public:
	SimpleMediaServerApp(): 
		_helpRequested(false),
		_pTimer(0)
	{
	}
	
	~SimpleMediaServerApp()
	{
		delete _pTimer;
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
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<SimpleMediaServerApp>(this, &SimpleMediaServerApp::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<SimpleMediaServerApp>(this, &SimpleMediaServerApp::handleConfig)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A simple UPnP MediaServer application.");
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
			_pTimer = new Poco::Util::Timer;

			// Find network interface
			std::string mcastInterfaceName = config().getString("upnp.interface", "");
			Poco::Net::NetworkInterface mcastInterface(mcastInterfaceName.empty() ? findActiveNetworkInterface() : Poco::Net::NetworkInterface::forName(mcastInterfaceName, Poco::Net::NetworkInterface::IPv4_ONLY));
			Poco::Net::IPAddress ipAddress(mcastInterface.address());

			logger().information(Poco::format("Using multicast network interface %s (%s).", mcastInterface.name(), ipAddress.toString()));

			Poco::UInt16 httpPort = config().getInt("http.port", 8000);
			Poco::UUID deviceUUID(config().getString("upnp.device.uuid"));
			int adLifetime = config().getInt("upnp.adLifetime", 60);
			std::string mediaPath = config().getString("media.path");
		
			// Set up HTTP server
			Poco::Net::HTTPServerParams::Ptr pHTTPParams = new Poco::Net::HTTPServerParams;
			pHTTPParams->setSoftwareVersion(config().getString("http.softwareVersion", ""));
			pHTTPParams->setMaxQueued(config().getInt("http.maxQueued", 4));
			pHTTPParams->setMaxThreads(config().getInt("http.maxThreads", 4));
			pHTTPParams->setTimeout(Poco::Timespan(config().getInt("http.timeout", 5), 0));
			pHTTPParams->setKeepAlive(config().getBool("http.keepAlive", false));
			pHTTPParams->setMaxKeepAliveRequests(config().getInt("http.maxKeepAliveRequests", 10));
			pHTTPParams->setKeepAliveTimeout(Poco::Timespan(config().getInt("http.keepAliveTimeout", 10), 0));
			
			Poco::Net::SocketAddress httpSA(ipAddress, httpPort);	
			
			// Set up UPnP SOAP and GENA
			Poco::UPnP::GENA::TransportFactory::registerFactory();
			Poco::UPnP::SOAP::Listener::Ptr pSOAPListener = new Poco::UPnP::SOAP::Listener(httpSA.toString());
			Poco::UPnP::GENA::Listener::Ptr pGENAListener = new Poco::UPnP::GENA::Listener(httpSA.toString(), *_pTimer);
			Poco::Net::ServerSocket httpSocket(httpPort);
			Poco::Net::HTTPServer httpServer(new RequestHandlerFactory(mediaPath, *pSOAPListener, *pGENAListener), httpSocket, pHTTPParams);
			httpServer.start();
			
			std::string soapListenerId = Poco::RemotingNG::ORB::instance().registerListener(pSOAPListener);
			std::string genaListenerId = Poco::RemotingNG::ORB::instance().registerListener(pGENAListener);
			
			// Register UPnP services
			Poco::SharedPtr<ContentDirectory1Impl> pContentDirectory1Impl = new ContentDirectory1Impl(httpSA.toString(), mediaPath);
			Poco::SharedPtr<ConnectionManager1Impl> pConnectionManager1Impl = new ConnectionManager1Impl;
			UPnPS::MediaServer1::ContentDirectory1ServerHelper::registerObject(pContentDirectory1Impl, "ContentDirectory.1", soapListenerId);
			std::string contentDirectoryURI = UPnPS::MediaServer1::ContentDirectory1ServerHelper::registerObject(pContentDirectory1Impl, "ContentDirectory.1", genaListenerId);
			UPnPS::MediaServer1::ConnectionManager1ServerHelper::registerObject(pConnectionManager1Impl, "ConnectionManager.1", soapListenerId);
			std::string connectionManagerURI = UPnPS::MediaServer1::ConnectionManager1ServerHelper::registerObject(pConnectionManager1Impl, "ConnectionManager.1", genaListenerId);

			// Enable GENA events
			UPnPS::MediaServer1::ContentDirectory1ServerHelper::enableEvents(contentDirectoryURI, pGENAListener->protocol());
			UPnPS::MediaServer1::ConnectionManager1ServerHelper::enableEvents(connectionManagerURI, pGENAListener->protocol());
			pGENAListener->registerStateProvider(contentDirectoryURI, pContentDirectory1Impl.get());
			pGENAListener->registerStateProvider(connectionManagerURI, pConnectionManager1Impl.get());
	
			// Set up SSDP and publish services
			Poco::Net::SocketAddress ssdpSA(Poco::Net::IPAddress(), SSDPResponder::MULTICAST_PORT);
			Poco::Net::MulticastSocket ssdpSocket(ssdpSA, true);
			ssdpSocket.setLoopback(true);
			ssdpSocket.setTimeToLive(4);
			ssdpSocket.setInterface(mcastInterface);
			SSDPResponder responder(*_pTimer, ssdpSocket);
			std::string deviceLocation = "http://" + httpSA.toString() + "/upnp/rootdevice.xml";
			responder.publish(new Advertisement(Advertisement::AD_ROOT_DEVICE, deviceUUID, deviceLocation, adLifetime));
			responder.publish(new Advertisement(Advertisement::AD_DEVICE, deviceUUID, deviceLocation, adLifetime));
			responder.publish(new Advertisement(deviceUUID, Poco::UPnP::URN("urn:schemas-upnp-org:device:MediaServer:1"), deviceLocation, adLifetime));
			responder.publish(new Advertisement(deviceUUID, Poco::UPnP::URN("urn:schemas-upnp-org:service:ContentDirectory:1"), deviceLocation, adLifetime));
			responder.publish(new Advertisement(deviceUUID, Poco::UPnP::URN("urn:schemas-upnp-org:service:ConnectionManager:1"), deviceLocation, adLifetime));
			ssdpSocket.joinGroup(responder.groupAddress().host(), mcastInterface);
			responder.start();
									
			waitForTerminationRequest();
			
			// Shut down
			httpServer.stop();
			responder.stop();
			Poco::Thread::sleep(500); // wait for goodbye messages to be sent
			ssdpSocket.leaveGroup(responder.groupAddress().host(), mcastInterface);

			Poco::RemotingNG::ORB::instance().shutdown();
		}
		return Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
	Poco::Util::Timer* _pTimer;
};


POCO_SERVER_MAIN(SimpleMediaServerApp)

