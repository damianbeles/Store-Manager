#pragma once
#include "DateTime.hpp"
#include "Product.hpp"

class PerishableProduct : public Product {
public:
	PerishableProduct(std::string, int, double, DateTime, TypeOfProduct);

	virtual void showInfoAboutProduct() const = 0;

protected:
	DateTime expiration_;
};