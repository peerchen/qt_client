//
// ExtToppingSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Pizzeria_ExtTopping_INCLUDED
#define TypeSerializer_Pizzeria_ExtTopping_INCLUDED


#include "Pizzeria/ExtTopping.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::ExtTopping>
{
public:
	static void serialize(const std::string& name, const Pizzeria::ExtTopping& value, Serializer& ser)
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

	static void serializeImpl(const Pizzeria::ExtTopping& value, Serializer& ser)
	{
		// Pizzeria::Topping
		{
		remoting__staticInitBegin(REMOTING__NAMES__PIZZERIA__TOPPING);
		static const std::string REMOTING__NAMES__PIZZERIA__TOPPING[] = {"name","price",""};
		remoting__staticInitEnd(REMOTING__NAMES__PIZZERIA__TOPPING);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES__PIZZERIA__TOPPING[0], value.getName(), ser);
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES__PIZZERIA__TOPPING[1], value.getPrice(), ser);
		}
		
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"addInfo",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.getAddInfo(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_ExtTopping_INCLUDED

