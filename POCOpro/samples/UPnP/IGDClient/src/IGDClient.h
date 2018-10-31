//
// IGDClient.h
//
// $Id: //poco/1.7/UPnP/samples/IGDClient/src/IGDClient.h#1 $
//
// This class implements a simple control point for the Internet Gateway device.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef IGDClient_H_INCLUDED
#define IGDClient_H_INCLUDED


#include "UPnPS/InternetGateway1/IWANIPConnection.h"
#include "UPnPS/InternetGateway1/IWANPPPConnection.h"
#include "Poco/UPnP/SSDP/Advertisement.h"
#include "Poco/UPnP/SSDP/SSDPResponder.h"
#include "Poco/UPnP/GENA/Listener.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Util/XMLConfiguration.h"
#include "Poco/Util/Timer.h"
#include "Poco/URI.h"
#include "Poco/BasicEvent.h"
#include "Poco/AtomicCounter.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"


class IGDClient
	/// This class implements a client for an UPnP
	/// Internet Gateway Device.
{
public:
	Poco::BasicEvent<const std::string> connectionStatusChanged;
	Poco::BasicEvent<const std::string> externalIPAddressChanged;
	Poco::BasicEvent<const Poco::UInt16> portMappingNumberOfEntriesChanged;

	IGDClient();
		/// Creates the IGDClient using the first active network interface.
		
	IGDClient(const Poco::Net::NetworkInterface& interfc);
		/// Creates the IGDClient using the given network interface.
		
	~IGDClient();
		/// Destroys the IGDClient.
		
	struct PortMapping
		/// The parameters of a port mapping entry.
		///   * remoteHost contains the IP address of the remote host that may connect to the port.
		///     Can be empty to allow any host to connect.
		///   * externalPort is the external port number.
		///   * protocol specifies the network protocol. Can be "TCP" or "UDP".
		///   * internalPort specifies the internal port number connections are forwarded to.
		///   * internalClient specifies the IP address of the host connections are forwarded to.
		///   * enabled specifies whether the port mapping is initially enabled or not.
		///   * description contains text describing the purpose of the mapping.
		///   * leaseDuration specifies the time in seconds the port mapping will be maintained.
	{
		std::string  remoteHost;
		Poco::UInt16 externalPort;
		std::string  protocol;
		Poco::UInt16 internalPort;
		std::string  internalClient;
		bool         enabled;
		std::string  description;
		Poco::UInt32 leaseDuration;
	};
	
	bool ready();
		/// Returns true if a WANPPPConnection or WANIPConnection
		/// has been found.
		
	bool waitReady(long milliseconds);
		/// Waits until either a WANPPPConnection or WANIPConnection
		/// has been found or the timeout expires.
		/// Return true if ready, false otherwise.
		
	void addPortMapping(const PortMapping& mapping);
		/// Adds a port mapping to the IGD.
		
	void deletePortMapping(const std::string& remoteHost, Poco::UInt16 externalPort, const std::string& protocol);
		/// Deletes the port mapping identified by remoteHost, externalPort and protocol from the IGD.

	void getPortMapping(Poco::UInt16 index, PortMapping& mapping);
		/// Get a single port mapping by index.
		
	void listPortMappings(std::vector<PortMapping>& mappings);
		/// Returns a list of all defined port mappings in the IGD.
		
	std::string externalIPAddress();
		/// Returns the external IP address of the IGD.
		
	static Poco::Net::NetworkInterface findActiveNetworkInterface();
		/// Finds an active network interface. The returned
		/// network interface can be passed to the IGDClient constructor.
		///
		/// Throws a Poco::IOException if no active network interface
		/// is available.

protected:
	class FetchDeviceDescriptionTask: public Poco::Util::TimerTask
	{
	public:
		FetchDeviceDescriptionTask(IGDClient& igd, const std::string& location):
			_igd(igd),
			_location(location)
		{
		}
		
		void run()
		{
			_igd.fetchDeviceDescription(_location);
		}
		
	private:
		IGDClient& _igd;
		std::string _location;
	};

	void fetchDeviceDescription(const std::string& location);
	void findService(const Poco::Util::XMLConfiguration& deviceDescription, const Poco::URI& baseURL, const std::string& basePath);
	void onAdvertisementSeen(Poco::UPnP::SSDP::Advertisement::Ptr& pAdvertisement);
	void onConnectionStatusChanged(const std::string& newStatus);
	void onExternalIPAddressChanged(const std::string& newExternalIPAddress);
	void onPortMappingNumberOfEntriesChanged(const Poco::UInt16& numberOfEntries);
	void start();
	void stop();
	void initialize();
	void uninitialize();
	template <class C> void setupConnection(Poco::AutoPtr<C> pConn, const Poco::URI& eventSubURL);
	template <class C> void shutdownConnection(Poco::AutoPtr<C> pConn);
	
private:
	IGDClient(const IGDClient&);
	IGDClient& operator = (const IGDClient&);
	
	Poco::Net::NetworkInterface _interface;
	Poco::Net::MulticastSocket _multicastSocket;
	Poco::SharedPtr<Poco::UPnP::SSDP::SSDPResponder> _pSSDPResponder;
	Poco::SharedPtr<Poco::Net::HTTPServer> _pHTTPServer;
	Poco::UPnP::GENA::Listener::Ptr _pGENAListener;
	std::string _genaListenerId;
	Poco::Util::Timer _timer;
	UPnPS::InternetGateway1::IWANIPConnection::Ptr  _pWANIPConnection;
	UPnPS::InternetGateway1::IWANPPPConnection::Ptr _pWANPPPConnection;
	Poco::Event _wanConnectionFound;
	Poco::FastMutex _mutex;
	Poco::Logger& _logger;

	static Poco::AtomicCounter _initCounter;
	
	friend class FetchDeviceDescriptionTask;
};


#endif // IGDClient_H_INCLUDED
