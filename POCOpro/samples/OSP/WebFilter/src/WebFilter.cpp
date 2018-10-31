//
// WebFilter.cpp
//
// $Id: //poco/1.7/OSP/samples/WebFilter/src/WebFilter.cpp#1 $
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/OSP/Web/WebFilter.h"
#include "Poco/OSP/Web/WebFilterFactory.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include "Poco/ClassLibrary.h"


class DateTimeFilter: public Poco::OSP::Web::WebFilter
{
public:
	void process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle)
	{
		std::string content;
		Poco::StreamCopier::copyToString(resourceStream, content);
		std::string dateTime = Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT);
		Poco::replaceInPlace(content, std::string("$$DATETIME$$"), dateTime);
		response.setContentType("text/html");
		response.send() << content;
	}
};


class DateTimeFilterFactory: public Poco::OSP::Web::WebFilterFactory
{
public:
	Poco::OSP::Web::WebFilter* createFilter(const Poco::OSP::Web::WebFilter::Args& args)
	{
		return new DateTimeFilter;
	}
};


POCO_BEGIN_NAMED_MANIFEST(WebFilter, Poco::OSP::Web::WebFilterFactory)
	POCO_EXPORT_CLASS(DateTimeFilterFactory)
POCO_END_MANIFEST
