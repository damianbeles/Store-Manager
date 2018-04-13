#pragma once
#include <list>
#include <memory>
#include "Order.hpp"
#include "Product.hpp"

struct Coordinates {
	double longitude_, latitude_;
	Coordinates(double longitude, double latitude) {
		longitude_ = longitude;
		latitude_ = latitude;
	}
};

class Store {
public:
	Store(std::string, Coordinates);

	std::list<std::shared_ptr<Product>> getProductList() const;

	std::list<std::shared_ptr<Order>> getOrderList() const;

	std::string getName() const;
	void setName(std::string);

	Coordinates getCoordinates() const;
	void setCoordinates(Coordinates);

	void showSolvedOrdersOlderThan(int) const;
	void showProductsWhichAmountIsLessThan(int) const;

	Store& operator+=(const std::shared_ptr<Product> &);
	Store& operator+=(const std::shared_ptr<Order> &);

private:
	std::list<std::shared_ptr<Product>> productList_;
	std::string name_;
	Coordinates coordinates_;
	std::list<std::shared_ptr<Order>> orderList_;
};