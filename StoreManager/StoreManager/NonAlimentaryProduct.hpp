#pragma once
#include "PerishableProduct.hpp"

class NonAlimentaryProduct : public PerishableProduct {
public:
	NonAlimentaryProduct(std::string, int, double, DateTime, double);

	void showInfoAboutProduct() const;
	double getToxicityGrade() const;

private:
	double toxicityGrade_;
};