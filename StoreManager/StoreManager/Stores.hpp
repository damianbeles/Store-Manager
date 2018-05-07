#pragma once
#include "Store.hpp"

#include <memory>
#include <vector>

class Stores {
public:
	Stores();
	Stores& operator+=(std::unique_ptr<Store>);
	Store *operator[](int);
	void showStoresWithMostOrdersSolvedInYear(int);
	void showTheStoresWithMostNonAlimentaryProducts();

private:
	std::vector<std::unique_ptr<Store>> storeList_;
};