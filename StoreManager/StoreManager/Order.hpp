#pragma once
#include "DateTime.hpp"
#include <list>
#include <memory>
#include "Product.hpp"

enum class OrderType { RECEIVING, SHIPPING };

class Order {
public:
	Order(DateTime, DateTime, std::string, OrderType);

	void setStartDate(DateTime);
	DateTime getStartDate() const;

	void setEndDate(DateTime);
	DateTime getEndDate() const;
	
	void setCustomer(std::string);
	std::string getCustomer() const;
	
	std::list<std::shared_ptr<Product>> getProductList();

	void setOrderType(OrderType);
	OrderType getOrderType() const;

	Order& operator+=(const std::shared_ptr<Product> &);
	friend std::ostream &operator<<(std::ostream&, const Order&);
	
private:
	DateTime startDate_;
	DateTime endDate_;
	std::string customer_;
	std::list<std::shared_ptr<Product>> productList_;
	OrderType orderType_;
};