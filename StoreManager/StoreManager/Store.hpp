#pragma once
#include <list>
#include <memory>
#include "Order.hpp"
#include "AlimentaryProduct.hpp"
#include "NonAlimentaryProduct.hpp"
#include "NonPerishableProduct.hpp"


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

	std::list<std::unique_ptr<Order>> const& getOrderList() const;

	std::string getName() const;
	void setName(std::string);

	Coordinates getCoordinates() const;
	void setCoordinates(Coordinates);

	void showSolvedOrdersOlderThan(int) const;
	void showProductsWhichAmountIsLessThan(int) const;
	bool isProductInStore(std::string) const;
	int getNumberOfSolvedOrdersInYear(int) const;

	int numberOfNonAlimentaryProducts_;
	int numberOfNonPerishableProducts_;
	int numberOfPerishableProducts_;

	int getNumberOfNonAlimentaryProducts() const;
	int getNumberOfNonPerishableProducts() const;
	int getNumberOfPerishableProducts() const;

	void showExpiredProducts() const;

	Store& operator+=(const std::shared_ptr<Product> &);
	Store& operator-=(std::string);
	Store& operator+=(std::unique_ptr<Order>);

private:
	std::list<std::shared_ptr<Product>> productList_;
	std::string name_;
	Coordinates coordinates_;
	std::list<std::unique_ptr<Order>> orderList_;
};