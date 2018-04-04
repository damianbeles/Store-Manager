#pragma once
#include <list>
#include <memory>
#include "Product.hpp"
#include <string>

enum class OrderType { RECEIVING, SHIPPING };

class Order {
public:
	Order(std::string, std::string, std::string, std::list<std::shared_ptr<Product>>, OrderType);

	void setStartDate(std::string);
	std::string getStartDate() const;

	void setEndDate(std::string);
	std::string getEndDate() const;
	
	void setCustomer(std::string);
	std::string getCustomer() const;
	
	std::list<std::shared_ptr<Product>> getProductList();

	void setOrderType(OrderType);
	OrderType getOrderType() const;
private:
	std::string startDate_;
	std::string endDate_;
	std::string customer_;
	std::list<std::shared_ptr<Product>> productList_;
	OrderType orderType_;
};