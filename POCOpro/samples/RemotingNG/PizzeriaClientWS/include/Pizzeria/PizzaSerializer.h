//
// PizzaSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Pizzeria_Pizza_INCLUDED
#define TypeSerializer_Pizzeria_Pizza_INCLUDED


#include "Pizzeria/ExtToppingDeserializer.h"
#include "Pizzeria/ExtToppingSerializer.h"
#include "Pizzeria/Pizza.h"
#include "Pizzeria/PizzaDetailsDeserializer.h"
#include "Pizzeria/PizzaDetailsSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::Pizza>
{
public:
	static void serialize(const std::string& name, const Pizzeria::Pizza& value, Serializer& ser)
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

	static void serializeImpl(const Pizzeria::Pizza& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"basePrice","details","name","toppings",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[0], value.getBasePrice(), ser);
		TypeSerializer<Pizzeria::PizzaDetails >::serialize(REMOTING__NAMES[1], value.getDetails(), ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.getName(), ser);
		TypeSerializer<std::vector < Pizzeria::ExtTopping > >::serialize(REMOTING__NAMES[3], value.getToppings(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_Pizza_INCLUDED

