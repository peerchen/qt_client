//
// FISWriter.cpp
//
// $Id: //poco/1.7/FastInfoset/samples/FISWriter/src/FISWriter.cpp#1 $
//
// This sample demonstrates the FastInfosetWriter class.
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


#include "Poco/FastInfoset/FastInfosetWriter.h"
#include "Poco/Exception.h"
#include "Poco/Path.h"
#include <fstream>
#include <cmath>


int main(int argc, char** argv)
{
	std::ofstream ostr("sample.fis", std::ios::binary);
	
	Poco::FastInfoset::FastInfosetWriter writer(ostr);
	writer.startDocument();
	writer.startElement("", "", "root");
	writer.startElement("", "", "string");
	writer.characters("Hello, world!");
	writer.endElement("", "", "string");
	writer.startElement("", "", "integer");
	writer.encodedData(42);
	writer.endElement("", "", "integer");
	writer.startElement("", "", "float");
	writer.encodedData(4*std::atan(1.0));
	writer.endElement("", "", "float");
	writer.endElement("", "", "root");
	writer.endDocument();

	return 0;
}
