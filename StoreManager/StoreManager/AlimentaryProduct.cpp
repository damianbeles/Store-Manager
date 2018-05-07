#include "stdafx.h"
#include "AlimentaryProduct.hpp"
#include <iostream>

AlimentaryProduct::AlimentaryProduct(std::string barCode, int amount, double pricePerPiece, DateTime expiration, double caloriesPerOneHundredGrams, Biological isBiological)
	: PerishableProduct(barCode, amount, pricePerPiece, expiration)
	, caloriesPerOneHundredGrams_(caloriesPerOneHundredGrams)
	, isBiological_(isBiological)
{}

void AlimentaryProduct::showInfoAboutProduct() const{
	std::cout << "#" << barCode_ << " "
		<< pricePerPiece_ << "$\n"
		<< "Expires on: " << expiration_.ToString() << "\n"
		<< "Calories per 100 grams: " << caloriesPerOneHundredGrams_ << "\n";
	isBiological_ == Biological::YES ? std::cout << "Biological: Yes!\n" : std::cout << "Biological: No!\n";
	std::cout << "The product is perishable!\n";
}