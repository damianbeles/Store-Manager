#include "stdafx.h"
#include "PerishableProduct.hpp"

PerishableProduct::PerishableProduct(std::string barCode, int amount, double pricePerPiece, DateTime expiration)
	: Product(barCode, amount, pricePerPiece)
	, expiration_(expiration)
{}