#include "stdafx.h"
#include "Store.hpp"

#include <ctime>
#include <iostream>
#include <algorithm>

Store::Store(std::string name, Coordinates coordinates)
	: name_(name)
	, coordinates_(coordinates)
{
	numberOfNonAlimentaryProducts_ = 0;
	numberOfNonPerishableProducts_ = 0;
	numberOfPerishableProducts_ = 0;
}

std::list<std::shared_ptr<Product>> Store::getProductList() const {
	return productList_;
}

std::list<std::unique_ptr<Order>> const& Store::getOrderList() const {
	return orderList_;
}

std::string Store::getName() const {
	return name_;
}

void Store::setName(std::string name) {
	name = name_;
}

Coordinates Store::getCoordinates() const {
	return coordinates_;
}

void Store::setCoordinates(Coordinates coordinates) {
	coordinates_ = coordinates;
}

void Store::showSolvedOrdersOlderThan(int days) const {
	DateTime currentDate = DateTime::getCurrentDate();
	
	int exist = 0;
	std::cout << "Solved orders which are older than " << days << " days:\n";
	for (const auto &it : orderList_) {
		if (it->getEndDate() - currentDate >= days && (exist = 1))
			std::cout << *it;
	}

	if (exist == 0)
		std::cout << "There are no such orders!\n\n";
}

void Store::showProductsWhichAmountIsLessThan(int amount) const {
	int exist = 0;
	std::cout << "Products which amount is less than " << amount << ": \n";
	for (auto it : productList_) {
		if (it->getAmount() < amount && (exist = 1))
			std::cout << *it << "The amount is: " << it->getAmount() << "\n";
	}

	if (exist == 0)
		std::cout << "There are no such products!\n";
	std::cout << "\n";
}

Store& Store::operator+=(const std::shared_ptr<Product> &product) {
	this->productList_.emplace_back(product);
	switch (product->getTypeOfProduct())
	{
	case TypeOfProduct::NonPerishable: numberOfNonPerishableProducts_++; break;
	case TypeOfProduct::NonAlimentary: numberOfNonAlimentaryProducts_++; numberOfPerishableProducts_++; break;
	case TypeOfProduct::Alimentary: numberOfPerishableProducts_++; break;
	}
	return *this;
}

Store& Store::operator-=(std::string barCode) {
	this->productList_.remove_if([barCode](std::shared_ptr<Product> product) { return product->getBarCode() == barCode; });
	return *this;
}


Store& Store::operator+=(std::unique_ptr<Order> order) {
	this->orderList_.emplace_back(std::move(order));
	return *this;
}

bool Store::isProductInStore(std::string barCode) const {
	return std::find_if(productList_.begin(), productList_.end(), [barCode](std::shared_ptr<Product> product) { return product->getBarCode() == barCode; }) != productList_.end();
}

int Store::getNumberOfSolvedOrdersInYear(int year) const {
	int result = 0;
	for (const auto &it : orderList_) {
		if (it->getEndDate().getYear() == year)
			result++;
	}
	return result;
}

int Store::getNumberOfNonAlimentaryProducts() const {
	return numberOfNonAlimentaryProducts_;
}

int Store::getNumberOfNonPerishableProducts() const {
	return numberOfNonPerishableProducts_;
}

int Store::getNumberOfPerishableProducts() const {
	return numberOfPerishableProducts_;
}

void Store::showExpiredProducts() const {
	std::string expiredProducts = "";
	for (auto it : productList_) {
		if (it->getTypeOfProduct() == TypeOfProduct::NonAlimentary || it->getTypeOfProduct() == TypeOfProduct::Alimentary) {
			PerishableProduct *perishableProduct = dynamic_cast<PerishableProduct*>(&*it);
			if (DateTime::getCurrentDate() > perishableProduct->getExpirationDate()) {
				expiredProducts += "#" + perishableProduct->getBarCode() + " ";
			}
		}
	}
	if (expiredProducts == "") std::cout << "There are no expired products in the store!\n";
	else std::cout << "Expired products are: " + expiredProducts + "\n";
}