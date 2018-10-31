//
// FIS2DOM.cpp
//
// $Id: //poco/1.7/FastInfoset/samples/FIS2DOM/src/FIS2DOM.cpp#1 $
//
// This sample demonstrates how to build a DOM tree using the Fast Infoset parser.
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
#include "Poco/DOM/DOMBuilder.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"
#include <iostream>


using Poco::FastInfoset::FastInfosetParser;
using Poco::XML::DOMBuilder;
using Poco::XML::Document;
using Poco::XML::NodeIterator;
using Poco::XML::NodeFilter;
using Poco::XML::Node;
using Poco::AutoPtr;


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "usage: " << argv[0] << ": <fisfile>" << std::endl;
		return 1;
	}
		
	try
	{
		FastInfosetParser parser;
		DOMBuilder domBuilder(parser);
		AutoPtr<Document> pDoc = domBuilder.parse(argv[1]);

		NodeIterator it(pDoc, NodeFilter::SHOW_ALL);
		Node* pNode = it.nextNode();
		while (pNode)
		{
			std::cout << pNode->nodeName() << ":" << pNode->nodeValue() << std::endl;
			pNode = it.nextNode();
		}
	}
	catch (Poco::Exception& e)
	{
		std::cerr << e.displayText() << std::endl;
		return 2;
	}
	
	return 0;
}
