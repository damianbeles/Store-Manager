// StoreManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stores.hpp"

#include <iostream>
#include <vector>

int main()
{
	Stores stores;
	std::unique_ptr<Store> store1 = std::make_unique<Store>("S.C. TheBestStore S.R.L", Coordinates(45.579, 23.333));
	stores += std::move(store1);
	
	std::shared_ptr<Product> product1 = std::make_shared<Product>("ABC-abc-1234", 25, 7.50);
	std::shared_ptr<Order> order1 = std::make_shared<Order>(DateTime(0, 0, 0, 1, 4, 1999), DateTime(0, 45, 15, 3, 4, 2013), "Jhon Wick", OrderType::RECEIVING);
	*order1 += product1;
	*stores[0] += order1;
	*stores[0] += product1;

	stores[0]->showSolvedOrdersOlderThan(10);
	stores[0]->showProductsWhichAmountIsLessThan(26);
	
	stores[0]->isProductInStore("ABC-abc-1234") ? std::cout << "Product is in store" : std::cout << "Product is not in store";
	std::cout << "\n\n";
	
	stores += std::move(std::make_unique<Store>("S.C. New Store S.R.L", Coordinates(44.137, 21.675)));
	std::shared_ptr<Product> product2 = std::make_shared<Product>("ACS-ACS-7765", 19, 6.49);
	std::shared_ptr<Product> product3 = std::make_shared<Product>("SCS-SDA-2133", 15, 7.49);
	*stores[1] += product2;
	*stores[1] += product3;
	std::shared_ptr<Order> order2 = std::make_shared<Order>(DateTime(5, 19, 23, 10, 02, 2013), DateTime(12, 20, 14, 10, 03, 2013), "James McCarty", OrderType::SHIPPING);
	*order2 += product2;
	*order2 += product3;
	std::shared_ptr<Order> order3 = std::make_shared<Order>(DateTime(6, 19, 12, 15, 04, 2013), DateTime(20, 20, 20, 20, 12, 2013), "McGregor", OrderType::SHIPPING);
	*order3 += product2;
	*stores[1] += order2;
	*stores[1] += order3;

	int year;
	std::cout << "Insert a year: "; std::cin >> year;
	stores.showStoresWithMostOrdersSolvedInYear(year);
	
	system("pause");
    return 0;
}

