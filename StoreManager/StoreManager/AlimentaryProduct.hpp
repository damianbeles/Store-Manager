#pragma once
#include "PerishableProduct.hpp"

enum class Biological { NO, YES };

class AlimentaryProduct : public PerishableProduct {
public:
	AlimentaryProduct(std::string, int, double, DateTime, double, Biological);

	void showInfoAboutProduct() const;

	double getCaloriesPerOneHundredGrams() const;
	Biological isBiological() const;

private:
	double caloriesPerOneHundredGrams_;
	Biological isBiological_;
};