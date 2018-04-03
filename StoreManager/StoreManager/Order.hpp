#pragma once
#include <list>
#include "Product.hpp"
#include <string>

enum class OrderType { RECEIVING, SHIPPING };

class Order {
public:
	Order(std::string, std::string, std::string, std::list<Product>, OrderType);
private:
	std::string startDate_;
	std::string endDate_;
	std::string customer_;
	std::list<Product> productList_;
	OrderType orderType_;
};