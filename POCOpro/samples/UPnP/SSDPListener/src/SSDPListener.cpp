//
// SSDPListener.cpp
//
// $Id: //poco/1.7/UPnP/samples/SSDPListener/src/SSDPListener.cpp#1 $
//
// This sample demonstrates the SSDPResponder class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/UPnP/SSDP/SSDPResponder.h"
#include "Poco/UPnP/SSDP/Advertisement.h"
#include "Poco/UPnP/URN.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/UUID.h"
#include "Poco/Delegate.h"
#include "Poco/NumberParser.h"
#include "Poco/Thread.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::UPnP::SSDP::SSDPResponder;
using Poco::UPnP::SSDP::Advertisement;
using Poco::UPnP::URN;


class SSDPListener: public ServerApplication
{
public:
	SSDPListener(): 
		_helpRequested(false),
		_lifetime(Advertisement::DEFAULT_LIFETIME)
	{
	}
	
	~SSDPListener()
	{
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
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
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handleHelp)));

		options.addOption(
			Option("search", "s", "Search for devices or services. Search for the special "
			                      "service type ssdp:all to discover all devices and services.")
				.required(false)
				.repeatable(false)
				.argument("<search-target>")
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handleSearch)));

		options.addOption(
			Option("publish", "P", "Publish an advertisement for a device.")
				.required(false)
				.repeatable(false)
				.argument("<device-UUID>")
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handlePublish)));

		options.addOption(
			Option("location", "L", "Specify the location of the device description.")
				.required(false)
				.repeatable(false)
				.argument("<URI>")
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handleLocation)));

		options.addOption(
			Option("lifetime", "T", "Specify the lifetime of the advertisements.")
				.required(false)
				.repeatable(false)
				.argument("<seconds>")
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handleLifetime)));

		options.addOption(
			Option("device", "D", "Publish an advertisement for a device type.")
				.required(false)
				.repeatable(true)
				.argument("<device-URN>")
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handleDevice)));

		options.addOption(
			Option("service", "S", "Publish an advertisement for a service type.")
				.required(false)
				.repeatable(true)
				.argument("<service-URN>")
				.callback(OptionCallback<SSDPListener>(this, &SSDPListener::handleService)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}
	
	void handleSearch(const std::string& name, const std::string& value)
	{
		_searchTarget = value;
	}

	void handlePublish(const std::string& name, const std::string& value)
	{
		_deviceUUID.parse(value);
	}
	
	void handleLocation(const std::string& name, const std::string& value)
	{
		_location = value;
	}

	void handleLifetime(const std::string& name, const std::string& value)
	{
		_lifetime = Poco::NumberParser::parse(value);
	}

	void handleDevice(const std::string& name, const std::string& value)
	{
		_devices.push_back(URN(value));
	}

	void handleService(const std::string& name, const std::string& value)
	{
		_services.push_back(URN(value));
	}
	
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A utility for discovering UPnP devices on the network.");
		helpFormatter.format(std::cout);
	}
	
	void onAdvertisementSeen(Advertisement::Ptr& pAdvertisement)
	{
		std::string type;
		switch (pAdvertisement->type())
		{
		case Advertisement::AD_ROOT_DEVICE:
			type = "ROOT DEVICE";
			break;
		case Advertisement::AD_DEVICE:
			type = "DEVICE";
			break;
		case Advertisement::AD_DEVICE_TYPE:
			type = "DEVICE TYPE";
			break;
		case Advertisement::AD_SERVICE_TYPE:
			type = "SERVICE_TYPE";
			break;
		}
		std::cout << "+ " << type << ": " << pAdvertisement->notificationType().toString() << "\n"
			<< "  USN: " << pAdvertisement->uniqueServiceName().toString() << "\n"
			<< "  Location: " << pAdvertisement->location() << "\n"
			<< "  Lifetime: " << pAdvertisement->lifetime() << "\n" 
			<< "  Host: " << pAdvertisement->attributes()["Host"] << "\n"
			<< "  Server: " << pAdvertisement->attributes().get("Server", "n/a") << "\n"
			<< std::endl;
	}
	
	void onAdvertisementGone(std::string& urn)
	{
		std::cout << "- " << urn << "\n" << std::endl;
	}
	
	void createAdvertisements(SSDPResponder& responder)
	{
		if (!_deviceUUID.isNull())
		{
			responder.publish(new Advertisement(Advertisement::AD_ROOT_DEVICE, _deviceUUID, _location, _lifetime));
			responder.publish(new Advertisement(Advertisement::AD_DEVICE, _deviceUUID, _location, _lifetime));
			for (std::vector<URN>::iterator it = _devices.begin(); it != _devices.end(); ++it)
			{
				responder.publish(new Advertisement(_deviceUUID, *it, _location, _lifetime));
			}
			for (std::vector<URN>::iterator it = _services.begin(); it != _services.end(); ++it)
			{
				responder.publish(new Advertisement(_deviceUUID, *it, _location, _lifetime));
			}
		}
	}

	int main(const std::vector<std::string>& args)
	{
		if (!_helpRequested)
		{
			Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), SSDPResponder::MULTICAST_PORT);
			Poco::Net::MulticastSocket socket(sa, true);
			socket.setLoopback(true);
			socket.setTimeToLive(4);
			SSDPResponder responder(socket);
			responder.advertisementSeen += Poco::delegate(this, &SSDPListener::onAdvertisementSeen);
			responder.advertisementGone += Poco::delegate(this, &SSDPListener::onAdvertisementGone);
			createAdvertisements(responder);
			socket.joinGroup(responder.groupAddress().host());
			responder.start();
			
			if (!_searchTarget.empty())
			{
				responder.search(_searchTarget);
			}
			
			waitForTerminationRequest();
			
			responder.stop();
			socket.leaveGroup(responder.groupAddress().host());
			responder.advertisementSeen -= Poco::delegate(this, &SSDPListener::onAdvertisementSeen);
			responder.advertisementGone -= Poco::delegate(this, &SSDPListener::onAdvertisementGone);
			
			if (!_deviceUUID.isNull())
			{
				Poco::Thread::sleep(1000); // give some time to send byebye messages
			}
		}
		return Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
	std::string _searchTarget;
	Poco::UUID _deviceUUID;
	std::string _location;
	int _lifetime;
	std::vector<URN> _devices;
	std::vector<URN> _services;
};


POCO_SERVER_MAIN(SSDPListener)
