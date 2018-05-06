#include "stdafx.h"
#include "Stores.hpp"
#include <iostream>

Stores::Stores() {}

Stores& Stores::operator+=(std::unique_ptr<Store> store) {
	this->storeList_.emplace_back(std::move(store));
	return *this;
}

Store *Stores::operator[](int index) {
	return storeList_[index].get();
}

void Stores::showStoresWithMostOrdersSolvedInYear(int year) {
	std::vector<std::string> storesWithMostOrdersSolvedInOneYear;
	int maxOrders = 0;
	for (const auto &it : storeList_) {
		if (it->getNumberOfSolvedOrdersInYear(year) > maxOrders) {
			maxOrders = it->getNumberOfSolvedOrdersInYear(year);
			storesWithMostOrdersSolvedInOneYear.clear();
		}
		if (it->getNumberOfSolvedOrdersInYear(year) == maxOrders) {
			storesWithMostOrdersSolvedInOneYear.push_back(it->getName());
		}
	}

	if (maxOrders) {
		std::cout << "Stores with most orders in year " << year << ":\n";
		for (auto it : storesWithMostOrdersSolvedInOneYear) {
			std::cout << it << "\n";
		}
	}
	else std::cout << "There are no stores with orders solved in that year!\n";
}