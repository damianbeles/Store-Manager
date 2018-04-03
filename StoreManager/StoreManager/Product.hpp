#pragma once
#include <string>

class Product {
public:
	Product(std::string, int, int);

	void setBarCode(std::string);
	std::string getBarCode() const;
	
	void setAmount(int);
	int getAmount() const;
	
	void setPricePerPiece(int);
	int getPricePerPiece() const;

private:
	std::string barCode_;
	int amount_;
	int pricePerPiece_;
};