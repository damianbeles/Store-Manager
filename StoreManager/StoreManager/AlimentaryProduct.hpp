#pragma once
#include "PerishableProduct.hpp"

class AlimentaryProduct : public PerishableProduct {
public:
	AlimentaryProduct(std::string, int, double, DateTime, double, bool);

	void showInfoAboutProduct() const;

private:
	double caloriesPerOneHundredGrams_;
	bool isBiological_;
};