//
// Order.h
//
// $Id: //poco/1.7/RemotingNG/samples/PizzeriaREST/include/Pizzeria/Order.h#1 $
//
// Definition of the Order struct.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef Order_INCLUDED
#define Order_INCLUDED


#include "Pizzeria/Pizza.h"
#include "Pizzeria/DeliveryAddress.h"
#include "Poco/Nullable.h"
#include "Poco/Optional.h"
#include "Poco/DateTime.h"


namespace Pizzeria { 


//@ serialize
struct Order
{
	Poco::Optional<int> orderNumber;
	Pizza pizza;
	DeliveryAddress deliveryAddress;
	Poco::Nullable<Poco::DateTime> deliveryTime;
};


} // namespace Pizzeria


#endif // Order_INCLUDED
