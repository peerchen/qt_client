//
// XML2FIS.cpp
//
// $Id: //poco/1.7/FastInfoset/samples/XML2FIS/src/XML2FIS.cpp#1 $
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


class XML2FISConverterApp: public Application
{
public:
	XML2FISConverterApp(): 
		_helpRequested(false),
		_maxIndexedStringLength(16),
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
				.callback(OptionCallback<XML2FISConverterApp>(this, &XML2FISConverterApp::handleHelp)));

		options.addOption(
			Option("max-indexed-length", "m", 
				"Specifies the maximum length of strings entered into the vocabulary. "
				"Specifying a higher value results in potentially smaller Fast Infoset "
				"documents at the expense of higher memory usage during conversion.")
				.required(false)
				.repeatable(false)
				.argument("value")
				.validator(new Poco::Util::IntValidator(0, 1024))
				.callback(OptionCallback<XML2FISConverterApp>(this, &XML2FISConverterApp::handleMaxIndexedLength)));

		options.addOption(
			Option("remove-ignorable-whitespace", "w", 
				"Remove all whitespace-only content between elements.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<XML2FISConverterApp>(this, &XML2FISConverterApp::handleRemoveIgnorableWhitespace)));
	}
	
	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		stopOptionsProcessing();
	}
	
	void handleMaxIndexedLength(const std::string& name, const std::string& value)
	{
		_maxIndexedStringLength = Poco::NumberParser::parse(value);
	}
	
	void handleRemoveIgnorableWhitespace(const std::string& name, const std::string& value)
	{
		_options += Converter::CONV_REMOVE_IGNORABLE_WHITESPACE;
	}
	
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option> ...] <fast infoset input file> <xml output file>");
		helpFormatter.setHeader(
			"\n"
			"The Applied Informatics XML to Fast Infoset Converter.\n"
			"Copyright (c) 2006-2010 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program converts XML documents into equivalent "
			"Fast Infoset documents.\n\n"
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
			Poco::FastInfoset::Converter::convertToFIS(*pInputStream, *pOutputStream, _maxIndexedStringLength, _options);
		}
		else
		{
			displayHelp();
		}
		return Application::EXIT_OK;
	}
		
private:
	bool _helpRequested;
	int  _maxIndexedStringLength;
	int  _options;
};


POCO_APP_MAIN(XML2FISConverterApp)
