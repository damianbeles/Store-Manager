// StoreManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DateTime.hpp"

#include <iostream>
#include <string>


int main()
{
	DateTime boss(13, 20, 11, 1, 1, 1901), boss2(13, 20, 11, 3, 1, 1901);
	std::cout << boss2.ToString() << "\n";

	std::cout << boss2 - boss << "\n"; 

	system("pause");
    return 0;
}

