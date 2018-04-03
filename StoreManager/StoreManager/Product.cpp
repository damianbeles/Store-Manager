#include "Product.hpp"

Product::Product(std::string barCode, int amount, int pricePerPiece)
	: barCode_(barCode)
	, amount_(amount)
	, pricePerPiece_(pricePerPiece)
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

void Product::setPricePerPiece(int pricePerPiece) {
	pricePerPiece_ = pricePerPiece;
}

int Product::getPricePerPiece() const {
	return pricePerPiece_;
}