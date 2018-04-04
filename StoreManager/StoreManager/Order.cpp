#include "Order.hpp"

Order::Order(std::string startDate, std::string endDate, std::string customer, std::list<std::shared_ptr<Product>> productList, OrderType orderType)
	: startDate_(startDate)
	, endDate_(endDate)
	, customer_(customer)
	, productList_(productList)
	, orderType_(orderType)
{}

std::string Order::getCustomer() const {
	return customer_;
}

void Order::setCustomer(std::string customer) {
	customer_ = customer;
}

std::string Order::getEndDate() const {
	return endDate_;
}

void Order::setEndDate(std::string endDate) {
	endDate_ = endDate;
}

std::string Order::getStartDate() const {
	return startDate_;
}

void Order::setStartDate(std::string startDate) {
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

