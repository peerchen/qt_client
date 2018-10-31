//
// IGDClientApp.cpp
//
// $Id: //poco/1.7/UPnP/samples/IGDClient/src/IGDClientApp.cpp#1 $
//
// This sample implements a simple control point for the Internet Gateway device.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "IGDClient.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"
#include "Poco/Event.h"
#include "Poco/NumberParser.h"
#include <iostream>


using Poco::Util::Application;
using Poco::UPnP::SSDP::SSDPResponder;
using Poco::UPnP::SSDP::Advertisement;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;


class IGDClientApp: public Application
{
public:
	IGDClientApp():
		_externalPort(0),
		_protocol("TCP"),
		_internalPort(0),
		_lease(3600),
		_sleep(0),
		_helpRequested(false)
	{
		setUnixOptions(true);
	}
	
	~IGDClientApp()
	{
	}

protected:
	void onConnectionStatusChanged(const std::string& newStatus)
	{
		logger().information("Connection status changed: " + newStatus);
	}

	void onExternalIPAddressChanged(const std::string& newExternalIPAddress)
	{
		logger().information("External IP address changed: " + newExternalIPAddress);
	}
	
	void onPortMappingNumberOfEntriesChanged(const Poco::UInt16& numberOfEntries)
	{
		logger().information(Poco::format("Port mapping number of entries changed: %hu", numberOfEntries));
	}

	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested || args.empty())
		{
			displayHelp();
			return Application::EXIT_OK;
		}
		
		IGDClient igdClient;
		
		igdClient.connectionStatusChanged += Poco::delegate(this, &IGDClientApp::onConnectionStatusChanged);
		igdClient.externalIPAddressChanged += Poco::delegate(this, &IGDClientApp::onExternalIPAddressChanged);
		igdClient.portMappingNumberOfEntriesChanged += Poco::delegate(this, &IGDClientApp::onPortMappingNumberOfEntriesChanged);
		
		logger().information("Waiting for services...");
		if (!igdClient.waitReady(5000))
		{
			logger().notice("No IGD found. Exiting.");
			return Application::EXIT_UNAVAILABLE;
		}
		
		try
		{
			if (args[0] == "map")
			{
				IGDClient::PortMapping mapping;
				mapping.remoteHost     = _remoteHost;
				mapping.externalPort   = _externalPort;
				mapping.protocol       = _protocol;
				mapping.internalPort   = _internalPort;
				mapping.internalClient = _client;
				mapping.enabled        = true;
				mapping.description    = _description;
				mapping.leaseDuration  = _lease;
				igdClient.addPortMapping(mapping);
				logger().information("Port mapping added.");
			}
			else if (args[0] == "unmap")
			{
				igdClient.deletePortMapping(_remoteHost, _externalPort, _protocol);
				logger().information("Port mapping removed.");
			}
			else if (args[0] == "list")
			{
				std::vector<IGDClient::PortMapping> mappings;
				igdClient.listPortMappings(mappings);
				if (mappings.empty())
				{
					logger().information("No port mappings found.");
				}
				else
				{
					for (std::vector<IGDClient::PortMapping>::const_iterator it = mappings.begin(); it != mappings.end(); ++it)
					{
						logger().information(Poco::format(
							"Port Mapping:\n"
							"    Remote Host:     %s\n"
							"    External Port:   %hu\n"
							"    Protocol:        %s\n"
							"    Internal Port:   %hu\n"
							"    Internal Client: %s\n",
							it->remoteHost, it->externalPort, it->protocol, it->internalPort, it->internalClient)
						  + Poco::format(
							"    enabled:         %s\n"
							"    description:     %s\n"
							"    lease duration:  %u",
							std::string(it->enabled ? "YES" : "NO"), it->description, it->leaseDuration));
					}
				}
			}
			else if (args[0] == "addr")
			{
				logger().information(std::string("External IP Address: ") + igdClient.externalIPAddress());
			}
		}
		catch (Poco::Exception& exc)
		{
			logger().log(exc);
		}
		
		Poco::Thread::sleep(1000*_sleep);

		return Application::EXIT_OK;
	}

	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleHelp)));

		options.addOption(
			Option("remoteHost", "r", "Specify remote host IP address.")
				.required(false)
				.repeatable(false)
				.argument("address")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleRemoteHost)));

		options.addOption(
			Option("externalPort", "x", "Specify external port number.")
				.required(false)
				.repeatable(false)
				.argument("port")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleExternalPort)));

		options.addOption(
			Option("protocol", "p", "Specify protocol (TCP or UDP).")
				.required(false)
				.repeatable(false)
				.argument("TCP|UDP")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleProtocol)));

		options.addOption(
			Option("internalPort", "i", "Specify internal port number.")
				.required(false)
				.repeatable(false)
				.argument("port")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleInternalPort)));

		options.addOption(
			Option("internalHost", "c", "Specify internal client host IP address.")
				.required(false)
				.repeatable(false)
				.argument("address")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleClient)));

		options.addOption(
			Option("description", "d", "Specify description.")
				.required(false)
				.repeatable(false)
				.argument("description")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleDescription)));

		options.addOption(
			Option("lease", "l", "Specify lease duration in seconds.")
				.required(false)
				.repeatable(false)
				.argument("seconds")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleLease)));

		options.addOption(
			Option("waitEvent", "w", "Wait a number of seconds for events.")
				.required(false)
				.repeatable(false)
				.argument("seconds")
				.callback(OptionCallback<IGDClientApp>(this, &IGDClientApp::handleWaitEvent)));
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUnixStyle(true);
		helpFormatter.setIndent(4);
		helpFormatter.setUsage("[addr|map|unmap|list] [OPTIONS]");
		helpFormatter.setHeader(
			"A simple client for UPnP Internet Gateway Devices.\n\n"
			"The following options are supported:");
		helpFormatter.setFooter(Poco::format(
			"Examples:\n"
			"  %[0]s addr\n"
			"    -> Displays the external IP address.\n"
			"  %[0]s map -x8080 -pTCP -i80 -c192.168.1.101 -d'Sample Mapping' -l3600\n"
			"    -> Creates a port mapping.\n"
			"  %[0]s unmap -x8080 -pTCP\n"
			"    -> Deletes a port mapping.\n"
			"  %[0]s list\n"
			"    -> Lists all port mappings.\n",
			commandName()));
		helpFormatter.format(std::cout);
	}
	
	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		stopOptionsProcessing();
	}

	void handleRemoteHost(const std::string& name, const std::string& value)
	{
		_remoteHost = value;
	}

	void handleExternalPort(const std::string& name, const std::string& value)
	{
		_externalPort = static_cast<Poco::UInt16>(Poco::NumberParser::parse(value));
	}
	
	void handleProtocol(const std::string& name, const std::string& value)
	{
		_protocol = value;
	}

	void handleInternalPort(const std::string& name, const std::string& value)
	{
		_internalPort = static_cast<Poco::UInt16>(Poco::NumberParser::parse(value));
	}

	void handleClient(const std::string& name, const std::string& value)
	{
		_client = value;
	}

	void handleDescription(const std::string& name, const std::string& value)
	{
		_description = value;
	}

	void handleLease(const std::string& name, const std::string& value)
	{
		_lease = Poco::NumberParser::parse(value);
	}
	
	void handleWaitEvent(const std::string& name, const std::string& value)
	{
		_sleep = Poco::NumberParser::parse(value);
	}

private:
	std::string _remoteHost;
	Poco::UInt16 _externalPort;
	std::string _protocol;
	Poco::UInt16 _internalPort;
	std::string _client;
	std::string _description;
	Poco::UInt32 _lease;
	int _sleep;
	bool _helpRequested;
};


POCO_APP_MAIN(IGDClientApp)
