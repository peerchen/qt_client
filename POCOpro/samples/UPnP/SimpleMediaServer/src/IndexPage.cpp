//
// IndexPage.cpp
//
// This file has been generated from IndexPage.cpsp on 2011-07-17 12:13:14.
//


#include "IndexPage.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


void IndexPage::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");
	if (request.has("Accept-Language"))
		response.set("Content-Language", "en");

	Poco::Net::HTMLForm form(request, request.stream());
	std::ostream& responseStream = response.send();
	responseStream << "";
	responseStream << "\n";
	responseStream << "<html>\n";
	responseStream << "<head>\n";
	responseStream << "<title>Applied Informatics UPnP MediaServer Demo</title>\n";
	responseStream << "</head>\n";
	responseStream << "<body>\n";
	responseStream << "<h1>Applied Informatics UPnP MediaServer Demo</h1>\n";
	responseStream << "<p>A simple implementation of the UPnP MediaServer device.</p>\n";
	responseStream << "<hr>\n";
	responseStream << "<i>Copyright &copy; 2011 by Applied Informatics Software Engineering GmbH.</i>\n";
	responseStream << "</body>\n";
	responseStream << "</html>\n";
	responseStream << "";
}
