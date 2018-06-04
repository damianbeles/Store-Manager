#include "stdafx.h"
#include "Stores.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>

Stores::Stores() {}

Stores& Stores::operator+=(std::unique_ptr<Store> store) {
	this->storeList_.emplace_back(std::move(store));
	return *this;
}

Stores& Stores::operator+=(std::string storePath) {
	std::string name = storePath.substr(storePath.find_last_of("\\") + 1);

	std::ifstream fin(storePath + "\\coordinates.txt");

	double longitude, latitude;
	fin >> longitude >> latitude;
	Coordinates coordinates(longitude, latitude);

	std::unique_ptr<Store> store = std::make_unique<Store>(name, coordinates);
	*store += storePath;

	*this += std::move(store);

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

void Stores::showTheStoresWithMostNonAlimentaryProducts() {
	std::vector<std::string> storesWithMostNonAlimentaryProducts;
	int maxNonAlimentaryProducts = 0;
	for (const auto &it : storeList_) {
		if (it->getNumberOfNonAlimentaryProducts() > maxNonAlimentaryProducts) {
			maxNonAlimentaryProducts = it->getNumberOfNonAlimentaryProducts();
			storesWithMostNonAlimentaryProducts.clear();
		}
		if (it->getNumberOfNonAlimentaryProducts() == maxNonAlimentaryProducts) {
			storesWithMostNonAlimentaryProducts.push_back(it->getName());
		}
	}

	if (maxNonAlimentaryProducts) {
		std::cout << "Stores with a number of " << maxNonAlimentaryProducts << " nonalimentary products are:\n";
		for (auto it : storesWithMostNonAlimentaryProducts) {
			std::cout << it << "\n";
		}
	}
	else std::cout << "There are no nonalimentary products in any store!\n";
}

void Stores::importData(std::string storesPath) {
	for (auto & store : std::experimental::filesystem::directory_iterator(storesPath))
		*this += store.path().string();
}