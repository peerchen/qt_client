//
// OrderEndpoint.h
//
// $Id: //poco/1.7/RemotingNG/samples/PizzeriaREST/include/Pizzeria/OrderEndpoint.h#1 $
//
// Definition of the OrderEndpoint class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OrderEndpoint_INCLUDED
#define OrderEndpoint_INCLUDED


#include "Pizzeria/Order.h"


namespace Pizzeria { 


class OrderCollection;


//@ remote
//@ path="/pizzeria/orders/{orderNumber}"
class OrderEndpoint
{
public:
	OrderEndpoint(OrderCollection& orderCollection);
		/// Creates the OrderEndpoint.

	~OrderEndpoint();
		/// Destroys the OrderEndpoint.
	
	//@ $orderNumber={in=path}
	Order get(int orderNumber) const;
		/// Returns the Order with the given orderId.
		
	//@ $orderNumber={in=path}
	Order patch(int orderNumber, const Order& order);
		/// Changes the given order.

	//@ $orderNumber={in=path}
	void delete_(int orderNumber);
		/// Deletes the Order with the given ID.

private:
	OrderCollection& _orderCollection;
};


} // namespace Pizzeria


#endif // OrderEndpoint_INCLUDED
