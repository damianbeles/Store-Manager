#pragma once
#include <list>
#include <memory>
#include "Order.hpp"
#include "Product.hpp"

struct Coordinates {
	int longitude_, latitude_;
	Coordinates(int longitude, int latitude) {
		longitude_ = longitude;
		latitude_ = latitude;
	}
};

class Store {
public:
	Store(std::list<std::shared_ptr<Product>>, std::string, Coordinates, std::list<std::shared_ptr<Order>>);

	std::list<std::shared_ptr<Product>> getProductList() const;

	std::list<std::shared_ptr<Order>> getOrderList() const;

	std::string getName() const;
	void setName(std::string);

	Coordinates getCoordinates() const;
	void setCoordinates(Coordinates);

private:
	std::list<std::shared_ptr<Product>> productList_;
	std::string name_;
	Coordinates coordinates_;
	std::list<std::shared_ptr<Order>> orderList_;
};