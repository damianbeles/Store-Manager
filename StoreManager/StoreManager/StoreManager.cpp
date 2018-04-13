// StoreManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Store.hpp"

#include <iostream>
#include <string>


int main()
{
	Store bestOne("S.C. TheBestStore S.R.L", Coordinates(45.579, 23.333));
	std::shared_ptr<Product> product = std::make_shared<Product>("ABC-abc-1234", 25, 7.50);
	std::shared_ptr<Order> order = std::make_shared<Order>(DateTime(0, 0, 0, 1, 4, 1999), DateTime(0, 0, 0, 1, 5, 1999), "Jhon Wick", OrderType::RECEIVING);
	*order += product;
	bestOne += order;

	bestOne.showSolvedOrdersOlderThan(10);


	system("pause");
    return 0;
}

