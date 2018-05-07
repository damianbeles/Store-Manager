#pragma once
#include <string>

enum class TypeOfProduct { NonPerishable, Alimentary, NonAlimentary };

class Product {
public:
	Product(std::string, int, double, TypeOfProduct);

	void setBarCode(std::string);
	std::string getBarCode() const;
	
	void setAmount(int);
	int getAmount() const;
	
	void setPricePerPiece(double);
	double getPricePerPiece() const;

	virtual void showInfoAboutProduct() const = 0;

	TypeOfProduct getTypeOfProduct() const;

	friend std::ostream &operator<<(std::ostream&, const Product&);

protected:
	std::string barCode_;
	int amount_;
	double pricePerPiece_;
	TypeOfProduct type_;
};