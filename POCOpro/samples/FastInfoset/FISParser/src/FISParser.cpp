//
// FISParser.cpp
//
// $Id: //poco/1.7/FastInfoset/samples/FISParser/src/FISParser.cpp#1 $
//
// This sample demonstrates the FastInfosetParser class.
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


#include "Poco/FastInfoset/FastInfosetParser.h"
#include "Poco/FastInfoset/FISContentHandler.h"
#include "Poco/SAX/Attributes.h"
#include "Poco/Exception.h"
#include <iostream>


class MyHandler: public Poco::FastInfoset::FISContentHandler
{
public:
	// ContentHandler
	void setDocumentLocator(const Poco::XML::Locator* loc)
	{
		// not used by FastInfoset parser
	}
	
	void startDocument()
	{
		std::cout << "Start document" << std::endl;
	}

	void endDocument()
	{
		std::cout << "End document" << std::endl;
	}

	void startElement(const std::string& uri, 
					  const std::string& localName, 
					  const std::string& qname, 
					  const Poco::XML::Attributes& attrs)
	{
		std::cout << "Start element" << std::endl;
		std::cout << "  uri:       " << uri << std::endl
				  << "  localName: " << localName << std::endl
				  << "  qname:     " << qname << std::endl;
		std::cout << "  Attributes: " << std::endl;
		for (int i = 0; i < attrs.getLength(); ++i)
		{
			std::cout << "    "
				<< attrs.getLocalName(i) << " = " << attrs.getValue(i) << std::endl;
		}
	}
	
	void endElement(const std::string& uri, 
					const std::string& localName, 
					const std::string& qname)
	{
		std::cout << "End element" << std::endl;
		std::cout << "  uri:       " << uri << std::endl
				  << "  localName: " << localName << std::endl
				  << "  qname:     " << qname << std::endl;
	}
	
	void characters(const char ch[], int start, int length)
	{
		std::cout << "character data: " << std::string(ch + start, length) << std::endl;
	}
	
	void ignorableWhitespace(const char ch[], int start, int length)
	{
	}
	
	void processingInstruction(const std::string& target, const std::string& data)
	{
	}
	
	void startPrefixMapping(const std::string& prefix, const std::string& uri)
	{
	}
	
	void endPrefixMapping(const std::string& prefix)
	{
	}
	
	void skippedEntity(const std::string& name)
	{
	}
	
	// FISContentHandler
 	void binaryData(const char* data, std::size_t size)
	{
		std::cout << "binary data (size " << size << ")" << std::endl;
	}
	
	void encodedData(Poco::Int16 value)
	{
		std::cout << "short: " << value << std::endl;
	}
				
	void encodedData(Poco::Int32 value)
	{
		std::cout << "int: " << value << std::endl;
	}

	void encodedData(Poco::Int64 value)
	{
		std::cout << "long: " << value << std::endl;
	}

	void encodedData(bool value)
	{
		std::cout << "bool: " << value << std::endl;
	}
		
	void encodedData(float value)
	{
		std::cout << "float: " << value << std::endl;
	}
		
	void encodedData(double value)
	{
		std::cout << "double: " << value << std::endl;
	}
		
	void encodedData(const Poco::UUID& value)
	{
		std::cout << "UUID: " << value.toString() << std::endl;
	}
};


int main(int argc, char* argv[])
{
	MyHandler myHandler;
	Poco::FastInfoset::FastInfosetParser parser;
	parser.setContentHandler(&myHandler);

	try
	{
		for (int i = 1; i < argc; i++)
		{
			parser.parse(argv[i]);
		}
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}
	return 0;
}
