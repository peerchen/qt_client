//
// ArrayOfForecastDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeDeserializer_WeatherWS_ArrayOfForecast_INCLUDED
#define TypeDeserializer_WeatherWS_ArrayOfForecast_INCLUDED


#include "Poco/RemotingNG/TypeDeserializer.h"
#include "WeatherWS/ArrayOfForecast.h"
#include "WeatherWS/ForecastDeserializer.h"
#include "WeatherWS/ForecastSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<WeatherWS::ArrayOfForecast>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, WeatherWS::ArrayOfForecast& value)
	{
		remoting__staticInitBegin(REMOTING__NAMESPACE);
		static const std::string REMOTING__NAMESPACE("http://ws.cdyne.com/WeatherWS/");
		remoting__staticInitEnd(REMOTING__NAMESPACE);
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		deser.pushProperty(SerializerBase::PROP_NAMESPACE, REMOTING__NAMESPACE);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.popProperty(SerializerBase::PROP_NAMESPACE);
			deser.deserializeStructEnd(name);
		}
		else deser.popProperty(SerializerBase::PROP_NAMESPACE);
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, WeatherWS::ArrayOfForecast& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"Forecast"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		std::vector < Poco::SharedPtr < WeatherWS::Forecast > > gen_forecast;
		ret = TypeDeserializer<std::vector < Poco::SharedPtr < WeatherWS::Forecast > > >::deserialize(REMOTING__NAMES[0], false, deser, gen_forecast);
		if (ret) value.setForecast(gen_forecast);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_WeatherWS_ArrayOfForecast_INCLUDED

