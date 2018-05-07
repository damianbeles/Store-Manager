#include "stdafx.h"
#include "NonAlimentaryProduct.hpp"
#include <iostream>

NonAlimentaryProduct::NonAlimentaryProduct(std::string barCode, int amount, double pricePerPiece, DateTime expiration, double toxicityGrade)
	: PerishableProduct(barCode, amount, pricePerPiece, expiration)
	, toxicityGrade_(toxicityGrade)
{}

void NonAlimentaryProduct::showInfoAboutProduct() const {
	std::cout << "#" << barCode_ << " "
		<< pricePerPiece_ << "$\n"
		<< "Expires on: " << expiration_.ToString() << "\n"
		<< "Toxicity Grade: " << toxicityGrade_ << "\n";
}