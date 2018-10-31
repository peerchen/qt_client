//
// PizzaDetailsSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Pizzeria_PizzaDetails_INCLUDED
#define TypeSerializer_Pizzeria_PizzaDetails_INCLUDED


#include "Pizzeria/PizzaDetails.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::PizzaDetails>
{
public:
	static void serialize(const std::string& name, const Pizzeria::PizzaDetails& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMESPACE);
		static const std::string REMOTING__NAMESPACE("http://www.appinf.com/webservices/PizzaDeliveryService/");
		remoting__staticInitEnd(REMOTING__NAMESPACE);
		ser.registerNamespace(REMOTING__NAMESPACE);
		ser.serializeStructBegin(name);
		ser.pushProperty(SerializerBase::PROP_NAMESPACE, REMOTING__NAMESPACE);
		serializeImpl(value, ser);
		ser.popProperty(SerializerBase::PROP_NAMESPACE);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Pizzeria::PizzaDetails& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"calories","carboHydrates","percentFat",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<double >::serialize(REMOTING__NAMES[0], value.getCalories(), ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[1], value.getCarboHydrates(), ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[2], value.getPercentFat(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_PizzaDetails_INCLUDED

