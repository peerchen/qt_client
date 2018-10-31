//
// RootDeviceDescription.cpp
//
// This file has been generated from RootDeviceDescription.cpsp.
//


#include "RootDeviceDescription.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/StreamCopier.h"
#include <sstream>


#include "Poco/Util/Application.h"


void RootDeviceDescription::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setContentType("text/xml");
	if (request.has("Accept-Language"))
		response.set("Content-Language", "en");

	Poco::Net::HTMLForm form(request, request.stream());
	std::stringstream responseStream;
	responseStream << "";
	responseStream << "";
	responseStream << "";
#line 7 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"

Poco::Util::Application& app = Poco::Util::Application::instance();
	responseStream << "<?xml version=\"1.0\"?>\n";
	responseStream << "<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n";
	responseStream << "  <specVersion>\n";
	responseStream << "    <major>1</major>\n";
	responseStream << "    <minor>0</minor>\n";
	responseStream << "  </specVersion>\n";
	responseStream << "  <URLBase>http://";
#line 15 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( request.serverAddress().toString() );
	responseStream << "</URLBase>\n";
	responseStream << "  <device>\n";
	responseStream << "    <deviceType>urn:schemas-upnp-org:device:DimmableLight:1</deviceType>\n";
	responseStream << "    <friendlyName>";
#line 18 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( app.config().getString("upnp.device.friendlyName") );
	responseStream << "</friendlyName>\n";
	responseStream << "    <manufacturer>";
#line 19 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( app.config().getString("upnp.device.manufacturer") );
	responseStream << "</manufacturer>\n";
	responseStream << "    <manufacturerURL>";
#line 20 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( app.config().getString("upnp.device.manufacturerURL") );
	responseStream << "</manufacturerURL>\n";
	responseStream << "    <modelDescription>";
#line 21 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( app.config().getString("upnp.device.modelDescription") );
	responseStream << "</modelDescription>\n";
	responseStream << "    <modelName>";
#line 22 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( app.config().getString("upnp.device.modelName") );
	responseStream << "</modelName>\n";
	responseStream << "    <UDN>uuid:";
#line 23 "/ws/poco-1.7/UPnP/samples/NetworkLight/src/RootDeviceDescription.cpsp"
	responseStream << ( app.config().getString("upnp.device.uuid") );
	responseStream << "</UDN>\n";
	responseStream << "    <serviceList>\n";
	responseStream << "      <service>\n";
	responseStream << "        <serviceType>urn:schemas-upnp-org:service:SwitchPower:1</serviceType>\n";
	responseStream << "        <serviceId>urn:upnp-org:serviceId:SwitchPower.1</serviceId>\n";
	responseStream << "        <SCPDURL>/upnp/SwitchPower1.xml</SCPDURL>\n";
	responseStream << "        <controlURL>/upnp-control/UPnPS.LightingControls1.SwitchPower/SwitchPower.1</controlURL>\n";
	responseStream << "        <eventSubURL>/upnp-eventing/UPnPS.LightingControls1.SwitchPower/SwitchPower.1</eventSubURL>\n";
	responseStream << "      </service>\n";
	responseStream << "      <service>\n";
	responseStream << "        <serviceType>urn:schemas-upnp-org:service:Dimming:1</serviceType>\n";
	responseStream << "        <serviceId>urn:upnp-org:serviceId:Dimming.1</serviceId>\n";
	responseStream << "        <SCPDURL>/upnp/Dimming1.xml</SCPDURL>\n";
	responseStream << "        <controlURL>/upnp-control/UPnPS.LightingControls1.Dimming/Dimming.1</controlURL>\n";
	responseStream << "        <eventSubURL>/upnp-eventing/UPnPS.LightingControls1.Dimming/Dimming.1</eventSubURL>\n";
	responseStream << "      </service>\n";
	responseStream << "    </serviceList>\n";
	responseStream << "    <presentationURL>/index.html</presentationURL>\n";
	responseStream << "  </device>\n";
	responseStream << "</root>\n";
	responseStream << "";
	response.setContentLength(static_cast<int>(responseStream.tellp()));
	Poco::StreamCopier::copyStream(responseStream, response.send());
}
