//
// ToppingCollectionEndpoint.cpp
//
// $Id: //poco/1.7/RemotingNG/samples/PizzeriaREST/src/ToppingCollectionEndpoint.cpp#1 $
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Pizzeria/ToppingCollectionEndpoint.h"


namespace Pizzeria { 


ToppingCollectionEndpoint::ToppingCollectionEndpoint(const std::vector<ExtTopping>& toppings):
	_toppings(toppings)
{
}


std::vector<ExtTopping> ToppingCollectionEndpoint::get() const
{
	return _toppings;
}


} // namespace Pizzeria
