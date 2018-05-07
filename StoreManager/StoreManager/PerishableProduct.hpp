#pragma once
#include "DateTime.hpp"
#include "Product.hpp"

class PerishableProduct : public Product {
public:
	PerishableProduct(std::string, int, double, DateTime);

	virtual void showInfoAboutProduct() const = 0;

protected:
	DateTime expiration_;
};