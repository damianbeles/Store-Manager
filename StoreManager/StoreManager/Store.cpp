#include "stdafx.h"
#include "Store.hpp"

Store::Store(std::list<std::shared_ptr<Product>> productList, std::string name, Coordinates coordinates, std::list<std::shared_ptr<Order>> orderList)
	: productList_(productList)
	, name_(name)
	, coordinates_(coordinates)
	, orderList_(orderList)
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