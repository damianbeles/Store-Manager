#pragma once
#include "PerishableProduct.hpp"

class NonAlimentaryProduct : public PerishableProduct {
public:
	NonAlimentaryProduct(std::string, int, double, DateTime, double);

	void showInfoAboutProduct() const;

private:
	double toxicityGrade_;
};