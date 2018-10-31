//
// IndexPage.cpp
//
// This file has been generated from IndexPage.cpsp on 2011-03-31 07:21:26.
//


#include "IndexPage.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


IndexPage::IndexPage(DimmableLight& context):
	_context(context)
{
}


void IndexPage::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

	Poco::Net::HTMLForm form(request, request.stream());
	std::ostream& responseStream = response.send();
	responseStream << "";
	responseStream << "\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "<html>\n";
	responseStream << "<head>\n";
	responseStream << "<title>Applied Informatics UPnP DimmableLight Demo</title>\n";
	responseStream << "<meta http-equiv=\"refresh\" content=\"1\">\n";
	responseStream << "</head>\n";
	responseStream << "<body>\n";
	responseStream << "<h1>Applied Informatics UPnP DimmableLight Demo</h1>\n";
	responseStream << "<ul>\n";
	responseStream << "<li>Status: ";
#line 12 "/ws/poco-1.4/UPnP/samples/NetworkLight/src/IndexPage.cpsp"
	responseStream << ( context().isOn() ? "ON" : "OFF" );
	responseStream << "</li>\n";
	responseStream << "<li>Level: ";
#line 13 "/ws/poco-1.4/UPnP/samples/NetworkLight/src/IndexPage.cpsp"
	responseStream << ( (int) context().getLevel() );
	responseStream << " %</li>\n";
	responseStream << "</ul>\n";
	responseStream << "<hr>\n";
	responseStream << "<i>Copyright &copy; 2011 by Applied Informatics Software Engineering GmbH.</i>\n";
	responseStream << "</body>\n";
	responseStream << "</html>\n";
	responseStream << "";
}
