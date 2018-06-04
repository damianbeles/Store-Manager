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

	system("pause");
    return 0;
}

