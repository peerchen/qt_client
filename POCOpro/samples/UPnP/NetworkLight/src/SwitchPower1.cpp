//
// SwitchPower1.cpp
//
// This file has been generated from SwitchPower1.cpsp on 2011-03-30 10:18:41.
//


#include "SwitchPower1.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


#include "Poco/DateTime.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#line 9 "/ws/poco-1.4/UPnP/samples/NetworkLight/src/SwitchPower1.cpsp"


// res/SwitchPower1.xml
static const unsigned char data[] = {
	0x3C, 0x73, 0x63, 0x70, 0x64, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 
	0x65, 0x53, 0x74, 0x61, 0x74, 0x65, 0x54, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 
	0x20, 0x3C, 0x73, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 
	0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x54, 0x61, 0x72, 0x67, 
	0x65, 0x74, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x3C, 0x73, 0x65, 0x6E, 0x64, 0x45, 0x76, 0x65, 0x6E, 0x74, 0x73, 0x41, 0x74, 0x74, 0x72, 0x69, 0x62, 
	0x75, 0x74, 0x65, 0x3E, 0x6E, 0x6F, 0x3C, 0x2F, 0x73, 0x65, 0x6E, 0x64, 0x45, 0x76, 0x65, 0x6E, 0x74, 
	0x73, 0x41, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x3C, 0x64, 0x61, 0x74, 0x61, 0x54, 0x79, 0x70, 0x65, 0x3E, 0x62, 0x6F, 0x6F, 0x6C, 
	0x65, 0x61, 0x6E, 0x3C, 0x2F, 0x64, 0x61, 0x74, 0x61, 0x54, 0x79, 0x70, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6C, 0x74, 0x56, 0x61, 0x6C, 0x75, 
	0x65, 0x3E, 0x30, 0x3C, 0x2F, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6C, 0x74, 0x56, 0x61, 0x6C, 0x75, 0x65, 
	0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 0x73, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 
	0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x73, 0x74, 0x61, 0x74, 
	0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3C, 0x2F, 0x6E, 0x61, 
	0x6D, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x64, 0x61, 0x74, 0x61, 0x54, 
	0x79, 0x70, 0x65, 0x3E, 0x62, 0x6F, 0x6F, 0x6C, 0x65, 0x61, 0x6E, 0x3C, 0x2F, 0x64, 0x61, 0x74, 0x61, 
	0x54, 0x79, 0x70, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x64, 0x65, 0x66, 
	0x61, 0x75, 0x6C, 0x74, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x3E, 0x30, 0x3C, 0x2F, 0x64, 0x65, 0x66, 0x61, 
	0x75, 0x6C, 0x74, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 
	0x73, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 
	0x20, 0x3C, 0x2F, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x53, 0x74, 0x61, 0x74, 0x65, 0x54, 0x61, 
	0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x4C, 0x69, 
	0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 
	0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x53, 0x65, 0x74, 0x54, 0x61, 
	0x72, 0x67, 0x65, 0x74, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 
	0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 
	0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x6E, 0x61, 
	0x6D, 0x65, 0x3E, 0x6E, 0x65, 0x77, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x56, 0x61, 0x6C, 0x75, 0x65, 
	0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x3C, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x69, 0x6E, 0x3C, 0x2F, 
	0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 
	0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x3C, 
	0x2F, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 
	0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 
	0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 
	0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 
	0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 
	0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x47, 0x65, 0x74, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x3C, 0x2F, 0x6E, 
	0x61, 0x6D, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 
	0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x52, 0x65, 0x74, 0x54, 
	0x61, 0x72, 0x67, 0x65, 0x74, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 
	0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x64, 0x69, 0x72, 0x65, 
	0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x6F, 0x75, 0x74, 0x3C, 0x2F, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 
	0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 
	0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 
	0x62, 0x6C, 0x65, 0x3E, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x3C, 0x2F, 0x72, 0x65, 0x6C, 0x61, 0x74, 
	0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 
	0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 
	0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 
	0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 
	0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 
	0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x47, 
	0x65, 0x74, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x0D, 0x0A, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 
	0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 
	0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x52, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x53, 0x74, 0x61, 0x74, 
	0x75, 0x73, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x20, 0x3C, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x6F, 0x75, 
	0x74, 0x3C, 0x2F, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 
	0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x53, 0x74, 0x61, 0x74, 
	0x75, 0x73, 0x3C, 0x2F, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x56, 
	0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 
	0x20, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 
	0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 
	0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 
	0x0A, 0x3C, 0x2F, 0x73, 0x63, 0x70, 0x64, 0x3E, 0x0D, 0x0A, 
};


static bool checkModified(Poco::Net::HTTPServerRequest& request)
{
	Poco::DateTime modified(2011, 3, 30, 10, 18, 39);
	request.response().setChunkedTransferEncoding(false);
	request.response().set("Last-Modified", Poco::DateTimeFormatter::format(modified, Poco::DateTimeFormat::HTTP_FORMAT));
	if (request.has("If-Modified-Since"))
	{
		Poco::DateTime modifiedSince;
		int tzd;
		Poco::DateTimeParser::parse(request.get("If-Modified-Since"), modifiedSince, tzd);
		if (modified <= modifiedSince)
		{
			request.response().setContentLength(0);
			request.response().setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_MODIFIED);
			request.response().send();
			return false;
		}
	}
	request.response().setContentLength(static_cast<int>(sizeof(data)));
	return true;
}


void SwitchPower1::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/xml");

	if (!(checkModified(request))) return;

	std::ostream& responseStream = response.send();
	responseStream << "";
	responseStream << "";
	responseStream << "";
	responseStream << "";
#line 113 "/ws/poco-1.4/UPnP/samples/NetworkLight/src/SwitchPower1.cpsp"

	responseStream.write(reinterpret_cast<const char*>(data), sizeof(data));
	responseStream << "";
}