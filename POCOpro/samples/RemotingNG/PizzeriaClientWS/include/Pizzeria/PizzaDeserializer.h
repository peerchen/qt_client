//
// PizzaDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeDeserializer_Pizzeria_Pizza_INCLUDED
#define TypeDeserializer_Pizzeria_Pizza_INCLUDED


#include "Pizzeria/ExtToppingDeserializer.h"
#include "Pizzeria/ExtToppingSerializer.h"
#include "Pizzeria/Pizza.h"
#include "Pizzeria/PizzaDetailsDeserializer.h"
#include "Pizzeria/PizzaDetailsSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Pizzeria::Pizza>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Pizzeria::Pizza& value)
	{
		remoting__staticInitBegin(REMOTING__NAMESPACE);
		static const std::string REMOTING__NAMESPACE("http://www.appinf.com/webservices/PizzaDeliveryService/");
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

	static void deserializeImpl(Deserializer& deser, Pizzeria::Pizza& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"basePrice","details","name","toppings"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		Poco::UInt32 gen_basePrice;
		ret = TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[0], true, deser, gen_basePrice);
		if (ret) value.setBasePrice(gen_basePrice);
		Pizzeria::PizzaDetails gen_details;
		ret = TypeDeserializer<Pizzeria::PizzaDetails >::deserialize(REMOTING__NAMES[1], true, deser, gen_details);
		if (ret) value.setDetails(gen_details);
		std::string gen_name;
		ret = TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, gen_name);
		if (ret) value.setName(gen_name);
		std::vector < Pizzeria::ExtTopping > gen_toppings;
		ret = TypeDeserializer<std::vector < Pizzeria::ExtTopping > >::deserialize(REMOTING__NAMES[3], false, deser, gen_toppings);
		if (ret) value.setToppings(gen_toppings);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Pizzeria_Pizza_INCLUDED

