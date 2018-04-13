#include "stdafx.h"
#pragma warning(disable : 4996)
#include "Store.hpp"

#include <ctime>
#include <iostream>

Store::Store(std::string name, Coordinates coordinates)
	: name_(name)
	, coordinates_(coordinates)
{}

std::list<std::shared_ptr<Product>> Store::getProductList() const {
	return productList_;
}

std::list<std::shared_ptr<Order>> Store::getOrderList() const {
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

void Store::showSolvedOrdersOlderThan(unsigned int days) const {
	std::time_t tm = std::time(0);
	std::tm *now = std::localtime(&tm);

	DateTime currentDate(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	
	std::cout << "Solved orders which are older than " << days << " days:\n\n";
	for (auto it : orderList_) {
		if (it->getEndDate() - currentDate >= (int)days)
			std::cout << *it << days;
		std::cout << "\n";
	}
}

Store& Store::operator+=(const std::shared_ptr<Product> &product) {
	this->productList_.emplace_back(product);
	return *this;
}

Store& Store::operator+=(const std::shared_ptr<Order> &order) {
	this->orderList_.emplace_back(order);
	return *this;
}