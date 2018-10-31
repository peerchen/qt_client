//
// ExtToppingDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeDeserializer_Pizzeria_ExtTopping_INCLUDED
#define TypeDeserializer_Pizzeria_ExtTopping_INCLUDED


#include "Pizzeria/Topping.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Pizzeria::ExtTopping>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Pizzeria::ExtTopping& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Pizzeria::ExtTopping& value)
	{
		// Pizzeria::Topping
		{
		remoting__staticInitBegin(REMOTING__NAMES__PIZZERIA__TOPPING);
		static const std::string REMOTING__NAMES__PIZZERIA__TOPPING[] = {"name","price"};
		remoting__staticInitEnd(REMOTING__NAMES__PIZZERIA__TOPPING);
		bool ret = false;
		std::string gen_name;
		ret = TypeDeserializer<std::string >::deserialize(REMOTING__NAMES__PIZZERIA__TOPPING[0], true, deser, gen_name);
		if (ret) value.setName(gen_name);
		Poco::UInt32 gen_price;
		ret = TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES__PIZZERIA__TOPPING[1], true, deser, gen_price);
		if (ret) value.setPrice(gen_price);
		}
		
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"addInfo"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		std::string gen_addInfo;
		ret = TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, gen_addInfo);
		if (ret) value.setAddInfo(gen_addInfo);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Pizzeria_ExtTopping_INCLUDED

