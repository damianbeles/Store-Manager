#include "stdafx.h"
#include "Stores.hpp"

#include <direct.h>
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
	for (auto &store : std::experimental::filesystem::directory_iterator(storesPath))
		*this += store.path().string();
}

void Stores::saveData(std::string storesPath) {
	_mkdir(storesPath.c_str()); 
	std::string pathsToCreate[] = { "\\Products", "\\Orders", "\\Products\\Alimentary", "\\Products\\Non Alimentary", "\\Products\\Non Perishable", "\\Orders\\Shipping", "\\Orders\\Receiving" };

	for (auto &store : storeList_) {
		std::string storePath = storesPath + "\\" + store->getName().c_str();
		_mkdir(storePath.c_str());

		for (auto &path : pathsToCreate) {
			_mkdir((storePath + path).c_str());
		}

		std::ofstream fout(storePath + "\\coordinates.txt");
		fout << store->getCoordinates().longitude_ << " "  << store->getCoordinates().latitude_;
		fout.close();

		std::string productsPath = storePath + "\\Products";
		for (auto &product : store->getProductList()) {
			switch (product->getTypeOfProduct()) {
				case TypeOfProduct::Alimentary: {
					fout.open(productsPath + "\\Alimentary\\" + product->getBarCode() + ".txt");
					AlimentaryProduct *alimentaryProduct = dynamic_cast<AlimentaryProduct *>(product.get());
					fout << alimentaryProduct->getAmount() << "\n";
					fout << alimentaryProduct->getPricePerPiece() << "\n";
					DateTime expirationDate = alimentaryProduct->getExpirationDate();
					fout << expirationDate.getSecond() << " " << expirationDate.getMinute() << " " << expirationDate.getHour() << " " << expirationDate.getDay() << " " << expirationDate.getMonth() << " " << expirationDate.getYear() << "\n";
					fout << alimentaryProduct->getCaloriesPerOneHundredGrams() << "\n";
					alimentaryProduct->isBiological() == Biological::YES ? fout << "1\n" : fout << "0\n";
					break;
				}
				case TypeOfProduct::NonAlimentary: {
					fout.open(productsPath + "\\Non Alimentary\\" + product->getBarCode() + ".txt");
					NonAlimentaryProduct *nonAlimentaryProduct = dynamic_cast<NonAlimentaryProduct *>(product.get());
					fout << nonAlimentaryProduct->getAmount() << "\n";
					fout << nonAlimentaryProduct->getPricePerPiece() << "\n";
					DateTime expirationDate = nonAlimentaryProduct->getExpirationDate();
					fout << expirationDate.getSecond() << " " << expirationDate.getMinute() << " " << expirationDate.getHour() << " " << expirationDate.getDay() << " " << expirationDate.getMonth() << " " << expirationDate.getYear() << "\n";
					fout << nonAlimentaryProduct->getToxicityGrade() << "\n";
					break;
				}
				case TypeOfProduct::NonPerishable: {
					fout.open(productsPath + "\\Non Perishable\\" + product->getBarCode() + ".txt");
					fout << product->getAmount() << "\n" << product->getPricePerPiece() << "\n";
					break;
				}
			}
			fout.close();
		}


		std::string ordersPath = storePath + "\\Orders";
		int receivingOrderIncrement = 1, shippingOrderIncrement = 1;
		for (auto &order : store->getOrderList()) {
			DateTime startDate = order->getStartDate();
			DateTime endDate = order->getEndDate();
			switch (order->getOrderType()) {
				case OrderType::RECEIVING: {
					fout.open(ordersPath + "\\Receiving\\order" + std::to_string(receivingOrderIncrement++) + ".txt");
					break;
				}
				case OrderType::SHIPPING: {
					fout.open(ordersPath + "\\Shipping\\order" + std::to_string(shippingOrderIncrement++) + ".txt");
					break;
				}
			}
			fout << startDate.getSecond() << " " << startDate.getMinute() << " " << startDate.getHour() << " " << startDate.getDay() << " " << startDate.getMonth() << " " << startDate.getYear() << "\n";
			fout << endDate.getSecond() << " " << endDate.getMinute() << " " << endDate.getHour() << " " << endDate.getDay() << " " << endDate.getMonth() << " " << endDate.getYear() << "\n";
			fout << order->getCustomer() << "\n";
			for (auto &product : order->getProductList()) {
				fout << product->getBarCode() << "\n";
			}
			fout.close();
		}
	}
}