#pragma once
#include <string>

class Product {
public:
	Product(std::string, int, double);

	void setBarCode(std::string);
	std::string getBarCode() const;
	
	void setAmount(int);
	int getAmount() const;
	
	void setPricePerPiece(double);
	double getPricePerPiece() const;


	friend std::ostream &operator<<(std::ostream&, const Product&);

private:
	std::string barCode_;
	int amount_;
	double pricePerPiece_;
};