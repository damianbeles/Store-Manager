// StoreManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stores.hpp"

#include <iostream>
#include <vector>


int main()
{
	Stores stores;

	std::string storesPath;
	std::cout << "Hey, welcome! First of all, we need to populate the stores with data.\nPlease insert here the path to the stores directory: ";
	std::cin >> storesPath;
	
	stores.importData(storesPath);
	
	//TODO: Use functions for manageing your store. Check https://github.com/damianbeles/Store-Manager/blob/master/README.md for details

	std::string saveStoresPath;
	std::cout << "For not losing your work, please give me a path where to store the data about the stores: ";
	std::cin >> saveStoresPath;

	stores.saveData(saveStoresPath);

	system("pause");
    return 0;
}

