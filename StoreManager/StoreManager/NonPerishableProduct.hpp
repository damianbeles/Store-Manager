#pragma once
#include "Product.hpp"

class NonPerishableProduct : public Product {
public:
	NonPerishableProduct(std::string, int, double);
	void showInfoAboutProduct() const;
};