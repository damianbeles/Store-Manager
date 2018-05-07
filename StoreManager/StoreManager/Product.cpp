#include "stdafx.h"
#include "Product.hpp"

Product::Product(std::string barCode, int amount, double pricePerPiece, TypeOfProduct type)
	: barCode_(barCode)
	, amount_(amount)
	, pricePerPiece_(pricePerPiece)
	, type_(type)
{}

void Product::setAmount(int amount) {
	amount_ = amount;
}

int Product::getAmount() const {
	return amount_;
}

void Product::setBarCode(std::string barCode) {
	barCode_ = barCode;
}

std::string Product::getBarCode() const {
	return barCode_;
}

void Product::setPricePerPiece(double pricePerPiece) {
	pricePerPiece_ = pricePerPiece;
}

double Product::getPricePerPiece() const {
	return pricePerPiece_;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
	product.showInfoAboutProduct();
	return os;
}

TypeOfProduct Product::getTypeOfProduct() const {
	return type_;
}