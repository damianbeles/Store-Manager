#pragma once
#include "Store.hpp"

#include <memory>
#include <vector>

class Stores {
public:
	Stores();
	Stores& operator+=(std::unique_ptr<Store>);
	Stores& operator+=(std::string);
	Store *operator[](int);
	void showStoresWithMostOrdersSolvedInYear(int);
	void showTheStoresWithMostNonAlimentaryProducts();
	void importData(std::string);

private:
	std::vector<std::unique_ptr<Store>> storeList_;
};