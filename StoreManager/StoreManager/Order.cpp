#include "stdafx.h"
#include "Order.hpp"

#include <iostream>
#include <windows.h>

Order::Order(DateTime startDate, DateTime endDate, std::string customer, OrderType orderType)
	: startDate_(startDate)
	, endDate_(endDate)
	, customer_(customer)
	, orderType_(orderType)
{}

std::string Order::getCustomer() const {
	return customer_;
}

void Order::setCustomer(std::string customer) {
	customer_ = customer;
}

DateTime Order::getEndDate() const {
	return endDate_;
}

void Order::setEndDate(DateTime endDate) {
	endDate_ = endDate;
}

DateTime Order::getStartDate() const {
	return startDate_;
}

void Order::setStartDate(DateTime startDate) {
	startDate_ = startDate;
}

std::list<std::shared_ptr<Product>> Order::getProductList() {
	return productList_;
}

OrderType Order::getOrderType() const {
	return orderType_;
}

void Order::setOrderType(OrderType orderType) {
	orderType_ = orderType;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	os << "Customer: " << order.customer_ << "\n";
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	os << "Launch date: " << order.startDate_.ToString() << " \n";
	os << "Solve date: " << order.endDate_.ToString() << " \n";
	os << "Order Type: ";  (order.orderType_ == OrderType::RECEIVING) ? os << "Receiving\n" : os << "Shipping\n";
	os << "Product List:\n\n";
	for (auto it : order.productList_)
		os << *it << "\n";
	return os;
}

Order& Order::operator+=(const std::shared_ptr<Product> &product) {
	this->productList_.emplace_back(product);
	return *this;
}