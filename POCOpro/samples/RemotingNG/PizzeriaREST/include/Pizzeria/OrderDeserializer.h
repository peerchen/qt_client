//
// OrderDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeDeserializer_Pizzeria_Order_INCLUDED
#define TypeDeserializer_Pizzeria_Order_INCLUDED


#include "Pizzeria/DeliveryAddressDeserializer.h"
#include "Pizzeria/DeliveryAddressSerializer.h"
#include "Pizzeria/Order.h"
#include "Pizzeria/PizzaDeserializer.h"
#include "Pizzeria/PizzaSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Pizzeria::Order>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Pizzeria::Order& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Pizzeria::Order& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"deliveryAddress","deliveryTime","orderNumber","pizza"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<Pizzeria::DeliveryAddress >::deserialize(REMOTING__NAMES[0], true, deser, value.deliveryAddress);
		TypeDeserializer<Poco::Nullable < Poco::DateTime > >::deserialize(REMOTING__NAMES[1], true, deser, value.deliveryTime);
		TypeDeserializer<Poco::Optional < int > >::deserialize(REMOTING__NAMES[2], true, deser, value.orderNumber);
		TypeDeserializer<Pizzeria::Pizza >::deserialize(REMOTING__NAMES[3], true, deser, value.pizza);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Pizzeria_Order_INCLUDED

