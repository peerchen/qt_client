//
// IGDClient.cpp
//
// $Id: //poco/1.7/UPnP/samples/IGDClient/src/IGDClient.cpp#1 $
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "IGDClient.h"
#include "UPnPS/InternetGateway1/WANIPConnectionClientHelper.h"
#include "UPnPS/InternetGateway1/WANIPConnectionProxy.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionClientHelper.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionProxy.h"
#include "Poco/UPnP/SSDP/SSDPResponder.h"
#include "Poco/UPnP/SSDP/Advertisement.h"
#include "Poco/UPnP/SOAP/TransportFactory.h"
#include "Poco/UPnP/SOAP/Transport.h"
#include "Poco/UPnP/GENA/RequestHandler.h"
#include "Poco/UPnP/URN.h"
#include "Poco/UPnP/UPnPException.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Delegate.h"
#include "Poco/NumberParser.h"
#include "Poco/Format.h"
#include "Poco/AutoPtr.h"


namespace
{
	class GENARequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
	{
	public:
		GENARequestHandlerFactory(Poco::UPnP::GENA::Listener& genaListener):
			_genaListener(genaListener),
			_logger(Poco::Logger::get("GENARequestHandlerFactory"))
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
	
	class SearchTask: public Poco::Util::TimerTask
	{
	public:
		SearchTask(Poco::UPnP::SSDP::SSDPResponder& responder):
			_responder(responder)
		{
		}
		
		void run()
		{
			_responder.search("urn:schemas-upnp-org:device:WANConnectionDevice:1");
		}
		
	private:
		Poco::UPnP::SSDP::SSDPResponder& _responder;
	};
}


Poco::AtomicCounter IGDClient::_initCounter;


IGDClient::IGDClient():
	_interface(findActiveNetworkInterface()),
	_wanConnectionFound(false),
	_logger(Poco::Logger::get("IGDClient"))
{
	initialize();
	start();
}


IGDClient::IGDClient(const Poco::Net::NetworkInterface& interfc):
	_interface(interfc),
	_wanConnectionFound(false),
	_logger(Poco::Logger::get("IGDClient"))
{
	initialize();
	start();
}


IGDClient::~IGDClient()
{
	stop();
	uninitialize();
}


bool IGDClient::ready()
{
	return _wanConnectionFound.tryWait(1);
}

	
bool IGDClient::waitReady(long milliseconds)
{
	return _wanConnectionFound.tryWait(milliseconds);
}


void IGDClient::addPortMapping(const PortMapping& mapping)
{
	if (_pWANIPConnection)
	{
		_pWANIPConnection->addPortMapping(mapping.remoteHost, mapping.externalPort, mapping.protocol, mapping.internalPort, mapping.internalClient, mapping.enabled, mapping.description, mapping.leaseDuration);
	}
	else if (_pWANPPPConnection)
	{
		_pWANPPPConnection->addPortMapping(mapping.remoteHost, mapping.externalPort, mapping.protocol, mapping.internalPort, mapping.internalClient, mapping.enabled, mapping.description, mapping.leaseDuration);
	}
	else throw Poco::IllegalStateException("IGDClient not ready");
}

	
void IGDClient::deletePortMapping(const std::string& remoteHost, Poco::UInt16 externalPort, const std::string& protocol)
{
	if (_pWANIPConnection)
	{
		_pWANIPConnection->deletePortMapping(remoteHost, externalPort, protocol);
	}
	else if (_pWANPPPConnection)
	{
		_pWANPPPConnection->deletePortMapping(remoteHost, externalPort, protocol);
	}
	else throw Poco::IllegalStateException("IGDClient not ready");
}

	
void IGDClient::getPortMapping(Poco::UInt16 index, PortMapping& mapping)
{
	if (_pWANIPConnection)
	{
		_pWANIPConnection->getGenericPortMappingEntry(index, mapping.remoteHost, mapping.externalPort, mapping.protocol, mapping.internalPort, mapping.internalClient, mapping.enabled, mapping.description, mapping.leaseDuration);
	}
	else if (_pWANPPPConnection)
	{
		_pWANPPPConnection->getGenericPortMappingEntry(index, mapping.remoteHost, mapping.externalPort, mapping.protocol, mapping.internalPort, mapping.internalClient, mapping.enabled, mapping.description, mapping.leaseDuration);	
	}
	else throw Poco::IllegalStateException("IGDClient not ready");
}


void IGDClient::listPortMappings(std::vector<PortMapping>& mappings)
{
	Poco::UInt16 index = 0;
	try
	{
		for (;;)
		{
			PortMapping mapping;
			getPortMapping(index, mapping);
			
			mappings.push_back(mapping);
			index++;
		}				
	}
	catch (Poco::UPnP::UPnPException& exc)
	{
		if (exc.code() != 713 /* SpecifiedArrayIndexInvalid */ && exc.code() != Poco::UPnP::UPnPException::CODE_ARGUMENT_VALUE_OUT_OF_RANGE)
			throw;
	}
}

	
std::string IGDClient::externalIPAddress()
{
	std::string externalIPAddress;
	if (_pWANIPConnection)
	{
		_pWANIPConnection->getExternalIPAddress(externalIPAddress);
	}
	else if (_pWANPPPConnection)
	{
		_pWANPPPConnection->getExternalIPAddress(externalIPAddress);
	}
	else throw Poco::IllegalStateException("IGDClient not ready");
	return externalIPAddress;
}


Poco::Net::NetworkInterface IGDClient::findActiveNetworkInterface()
{
	Poco::Net::NetworkInterface::NetworkInterfaceList ifs = Poco::Net::NetworkInterface::list();
	for (Poco::Net::NetworkInterface::NetworkInterfaceList::iterator it = ifs.begin(); it != ifs.end(); ++it)
	{
		if (!it->address().isWildcard() && !it->address().isLoopback() && it->supportsIPv4()) return *it;
	}
	throw Poco::IOException("No configured Ethernet interface found");
}


void IGDClient::findService(const Poco::Util::XMLConfiguration& deviceDescription, const Poco::URI& baseURL, const std::string& basePath)
{
	int i = 0;
	while (deviceDescription.hasProperty(Poco::format("%s.serviceList.service[%d].serviceType", basePath, i)))
	{
		std::string serviceType = deviceDescription.getString(Poco::format("%s.serviceList.service[%d].serviceType", basePath, i));
		std::string controlURL  = deviceDescription.getString(Poco::format("%s.serviceList.service[%d].controlURL", basePath, i));
		std::string eventSubURL = deviceDescription.getString(Poco::format("%s.serviceList.service[%d].eventSubURL", basePath, i), "");
		
		_logger.information(Poco::format("Found service: %s.", serviceType));				
		if (serviceType == "urn:schemas-upnp-org:service:WANIPConnection:1")
		{
			if (!_pWANIPConnection)
			{
				Poco::URI wanIPConnectionURL(baseURL, controlURL);
				_pWANIPConnection = UPnPS::InternetGateway1::WANIPConnectionClientHelper::find(wanIPConnectionURL.toString(), "upnp-control");
				Poco::URI wanIPConnectionEventSubURL(baseURL, eventSubURL);
				setupConnection(_pWANIPConnection, wanIPConnectionEventSubURL);
				_wanConnectionFound.set();
			}
		}
		else if (serviceType == "urn:schemas-upnp-org:service:WANPPPConnection:1")
		{
			if (!_pWANPPPConnection)
			{
				Poco::URI wanPPPConnectionURL(baseURL, controlURL);
				_pWANPPPConnection = UPnPS::InternetGateway1::WANPPPConnectionClientHelper::find(wanPPPConnectionURL.toString(), "upnp-control");
				Poco::URI wanPPPConnectionEventSubURL(baseURL, eventSubURL);
				setupConnection(_pWANPPPConnection, wanPPPConnectionEventSubURL);
				_wanConnectionFound.set();
			}
		}
		i++;
	}
	
	i = 0;
	while (deviceDescription.hasProperty(Poco::format("%s.deviceList.device[%d].deviceType", basePath, i)))
	{
		findService(deviceDescription, baseURL, Poco::format("%s.deviceList.device[%d]", basePath, i));
		i++;
	}
}


void IGDClient::fetchDeviceDescription(const std::string& location)
{
	_logger.information("Retrieving device description from " + location + ".");
	Poco::URI uri(location);
	Poco::Net::HTTPClientSession cs(uri.getHost(), uri.getPort());
	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathEtc(), Poco::Net::HTTPRequest::HTTP_1_1);
	cs.sendRequest(request);
	Poco::Net::HTTPResponse response;
	std::istream& istr = cs.receiveResponse(response);
	if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
	{
		Poco::AutoPtr<Poco::Util::XMLConfiguration> pDeviceDescription = new Poco::Util::XMLConfiguration(istr);

		Poco::URI baseURL(pDeviceDescription->getString("URLBase", location));

		Poco::FastMutex::ScopedLock lock(_mutex);	
		findService(*pDeviceDescription, baseURL, "device");
	}
}


void IGDClient::onAdvertisementSeen(Poco::UPnP::SSDP::Advertisement::Ptr& pAdvertisement)
{
	if (pAdvertisement->type() == Poco::UPnP::SSDP::Advertisement::AD_DEVICE_TYPE)
	{
		if (pAdvertisement->notificationType() == "urn:schemas-upnp-org:device:WANConnectionDevice:1")
		{
			std::string location = pAdvertisement->location();
			_logger.information(Poco::format("Found WANConnectionDevice device at %s.", location));
			
			Poco::FastMutex::ScopedLock lock(_mutex);
			if (!_pWANIPConnection && !_pWANPPPConnection)
			{
				_timer.schedule(new FetchDeviceDescriptionTask(*this, location), Poco::Timestamp());
			}
		}
	}
}


void IGDClient::onConnectionStatusChanged(const std::string& newStatus)
{
	_logger.information("Connection status changed: " + newStatus);
	connectionStatusChanged(this, newStatus);
}


void IGDClient::onExternalIPAddressChanged(const std::string& newExternalIPAddress)
{
	_logger.information("External IP address changed: " + newExternalIPAddress);
	externalIPAddressChanged(this, newExternalIPAddress);
}


void IGDClient::onPortMappingNumberOfEntriesChanged(const Poco::UInt16& numberOfEntries)
{
	_logger.information(Poco::format("Port mapping number of entries changed: %hu", numberOfEntries));
	portMappingNumberOfEntriesChanged(this, numberOfEntries);
}


void IGDClient::start()
{
	Poco::Net::IPAddress ipAddress(_interface.address());
	_logger.information(Poco::format("Starting IGDClient on multicast network interface %s (%s).", _interface.name(), ipAddress.toString()));

	Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), Poco::UPnP::SSDP::SSDPResponder::MULTICAST_PORT);
	_multicastSocket = Poco::Net::MulticastSocket(sa, true);
	_multicastSocket.setTimeToLive(4);
	_multicastSocket.setInterface(_interface);
	_pSSDPResponder = new Poco::UPnP::SSDP::SSDPResponder(_timer, _multicastSocket);
	_pSSDPResponder->advertisementSeen += Poco::delegate(this, &IGDClient::onAdvertisementSeen);
	_multicastSocket.joinGroup(_pSSDPResponder->groupAddress().host(), _interface);

	Poco::Net::ServerSocket httpSocket(Poco::Net::SocketAddress(ipAddress, 0));
	Poco::Net::SocketAddress httpSA(ipAddress, httpSocket.address().port());
	_pGENAListener = new Poco::UPnP::GENA::Listener(httpSA.toString(), _timer);
	_pHTTPServer = new Poco::Net::HTTPServer(new GENARequestHandlerFactory(*_pGENAListener), httpSocket, new Poco::Net::HTTPServerParams);
	_pHTTPServer->start();		
	_genaListenerId = Poco::RemotingNG::ORB::instance().registerListener(_pGENAListener);

	_pSSDPResponder->start();
	
	Poco::Timestamp now;
	_timer.schedule(new SearchTask(*_pSSDPResponder), now);
	_timer.schedule(new SearchTask(*_pSSDPResponder), now + 100000);
	_timer.schedule(new SearchTask(*_pSSDPResponder), now + 200000);
}


void IGDClient::stop()
{
	shutdownConnection(_pWANIPConnection);
	shutdownConnection(_pWANPPPConnection);

	_pHTTPServer->stop();
	_pHTTPServer = 0;
	
	_pSSDPResponder->stop();
	_multicastSocket.leaveGroup(_pSSDPResponder->groupAddress().host(), _interface);
	_pSSDPResponder->advertisementSeen -= Poco::delegate(this, &IGDClient::onAdvertisementSeen);
	_pSSDPResponder = 0;

	Poco::RemotingNG::ORB::instance().unregisterListener(_genaListenerId, true);
}


void IGDClient::initialize()
{
	if (++_initCounter == 1)
	{
		Poco::UPnP::SOAP::TransportFactory::registerFactory();
	}
}


void IGDClient::uninitialize()
{
	if (--_initCounter == 0)
	{
		Poco::UPnP::SOAP::TransportFactory::unregisterFactory();
	}
}


template <class C> void IGDClient::setupConnection(Poco::AutoPtr<C> pConn, const Poco::URI& eventSubURL)
{
	pConn.template cast<Poco::RemotingNG::Proxy>()->remoting__setEventURI(eventSubURL);
	static_cast<Poco::UPnP::SOAP::Transport&>(pConn.template cast<Poco::RemotingNG::Proxy>()->remoting__transport()).setChunkedTransferEncoding(false);
	pConn->connectionStatusChanged += Poco::delegate(this, &IGDClient::onConnectionStatusChanged);
	pConn->externalIPAddressChanged += Poco::delegate(this, &IGDClient::onExternalIPAddressChanged);
	pConn->portMappingNumberOfEntriesChanged += Poco::delegate(this, &IGDClient::onPortMappingNumberOfEntriesChanged);
	try
	{
		pConn->remoting__enableEvents(_pGENAListener);
	}
	catch (Poco::Exception& exc)
	{
		_logger.warning("Cannot subscribe to events: " + exc.displayText());
	}
}


template <class C> void IGDClient::shutdownConnection(Poco::AutoPtr<C> pConn)
{
	if (pConn)
	{
		pConn->remoting__enableEvents(_pGENAListener, false);
		pConn->connectionStatusChanged -= Poco::delegate(this, &IGDClient::onConnectionStatusChanged);
		pConn->externalIPAddressChanged -= Poco::delegate(this, &IGDClient::onExternalIPAddressChanged);
		pConn->portMappingNumberOfEntriesChanged -= Poco::delegate(this, &IGDClient::onPortMappingNumberOfEntriesChanged);
		pConn = 0;
	}
}
