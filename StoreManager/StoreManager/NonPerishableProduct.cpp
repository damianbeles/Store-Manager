#include "stdafx.h"
#include "NonPerishableProduct.hpp"
#include <iostream>

NonPerishableProduct::NonPerishableProduct(std::string barCode, int amount, double pricePerPiece)
	: Product(barCode, amount, pricePerPiece)
{}

void NonPerishableProduct::showInfoAboutProduct() const{
	std::cout << "#" << barCode_ << " "
		<< pricePerPiece_ << "$\n"
		<< "The product is nonperishable!\n";
}