//
// FIS2XML.cpp
//
// $Id: //poco/1.7/FastInfoset/samples/FIS2XML/src/FIS2XML.cpp#1 $
//
// This sample demonstrates the Fast Infoset Converter::convertToFIS() function.
//
// Copyright (c) 2006-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics
// Software Engineering GmbH.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part, without
// prior written permission from Applied Informatics.
//


#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/IntValidator.h"
#include "Poco/FastInfoset/Converter.h"
#include "Poco/Exception.h"
#include "Poco/FileStream.h"
#include "Poco/NumberParser.h"
#include "Poco/SharedPtr.h"
#include <iostream>
#include <fstream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::FastInfoset::Converter;


class FIS2XMLConverterApp: public Application
{
public:
	FIS2XMLConverterApp(): 
		_helpRequested(false),
		_options(0)
	{
	}

protected:		
	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<FIS2XMLConverterApp>(this, &FIS2XMLConverterApp::handleHelp)));

		options.addOption(
			Option("xml-declaration", "x", "Write an XML declaration at the beginning of the resulting XML document.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<FIS2XMLConverterApp>(this, &FIS2XMLConverterApp::handleXMLDeclaration)));

		options.addOption(
			Option("pretty-print", "p", "Pretty-print (indent) the resulting XML document.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<FIS2XMLConverterApp>(this, &FIS2XMLConverterApp::handlePrettyPrint)));
	}
	
	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		stopOptionsProcessing();
	}

	void handleXMLDeclaration(const std::string& name, const std::string& value)
	{
		_options += Converter::CONV_WRITE_XML_DECLARATION;
	}

	void handlePrettyPrint(const std::string& name, const std::string& value)
	{
		_options += Converter::CONV_PRETTY_PRINT_XML;
	}
	
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option> ...] <xml input file> <fast infoset output file>");
		helpFormatter.setHeader(
			"\n"
			"The Applied Informatics Fast Infoset to XML Converter.\n"
			"Copyright (c) 2006-2010 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program converts Fast Infoset documents into equivalent "
			"XML documents.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setFooter(
			"Note: To read from standard input, or write to standard output, "
			"specify a '-' as the respective file name. \n\n"
			"For more information, please see the Applied Informatics C++ Libraries and Tools "
			"documentation at <http://docs.appinf.com/>."
		);
		helpFormatter.format(std::cout);
	}
	
	int main(const std::vector<std::string>& args)
	{
		if (!_helpRequested && args.size() == 2)
		{
			std::istream* pInputStream(0);
			std::ostream* pOutputStream(0);
			Poco::SharedPtr<Poco::FileInputStream> pInputFile(0);
			Poco::SharedPtr<Poco::FileOutputStream> pOutputFile(0);
			if (args[0] == "-") 
			{
				pInputStream = &std::cin;
			}
			else
			{
				pInputFile = new Poco::FileInputStream(args[0]);
				pInputStream = pInputFile;
			}
			if (args[1] == "-") 
			{
				pOutputStream = &std::cout;
			}
			else
			{
				pOutputFile = new Poco::FileOutputStream(args[1]);
				pOutputStream = pOutputFile;
			}
			Poco::FastInfoset::Converter::convertToXML(*pInputStream, *pOutputStream, _options);
		}
		else
		{
			displayHelp();
		}
		return Application::EXIT_OK;
	}
		
private:
	bool _helpRequested;
	int _options;
};


POCO_APP_MAIN(FIS2XMLConverterApp)
