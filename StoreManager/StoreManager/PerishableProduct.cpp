#include "stdafx.h"
#include "PerishableProduct.hpp"

PerishableProduct::PerishableProduct(std::string barCode, int amount, double pricePerPiece, DateTime expiration, TypeOfProduct type)
	: Product(barCode, amount, pricePerPiece, type)
	, expiration_(expiration)
{}

DateTime PerishableProduct::getExpirationDate() const {
	return expiration_;
}