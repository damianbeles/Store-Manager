#include "stdafx.h"
#include "Store.hpp"

#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>

Store::Store(std::string name, Coordinates coordinates)
	: name_(name)
	, coordinates_(coordinates)
{
	numberOfNonAlimentaryProducts_ = 0;
	numberOfNonPerishableProducts_ = 0;
	numberOfPerishableProducts_ = 0;
}

std::list<std::shared_ptr<Product>> Store::getProductList() const {
	return productList_;
}

std::list<std::unique_ptr<Order>> const& Store::getOrderList() const {
	return orderList_;
}

std::string Store::getName() const {
	return name_;
}

void Store::setName(std::string name) {
	name = name_;
}

Coordinates Store::getCoordinates() const {
	return coordinates_;
}

void Store::setCoordinates(Coordinates coordinates) {
	coordinates_ = coordinates;
}

void Store::showSolvedOrdersOlderThan(int days) const {
	DateTime currentDate = DateTime::getCurrentDate();
	
	int exist = 0;
	std::cout << "\nSolved orders which are older than " << days << " days:\n\n";
	for (const auto &it : orderList_) {
		if (it->getEndDate() - currentDate >= days && (exist = 1))
			std::cout << *it;
	}

	if (exist == 0)
		std::cout << "There are no such orders!\n\n";
}

void Store::showProductsWhichAmountIsLessThan(int amount) const {
	int exist = 0;
	std::cout << "Products which amount is less than " << amount << ": \n";
	for (auto it : productList_) {
		if (it->getAmount() < amount && (exist = 1))
			std::cout << *it << "The amount is: " << it->getAmount() << "\n";
	}

	if (exist == 0)
		std::cout << "There are no such products!\n";
	std::cout << "\n";
}

Store& Store::operator+=(const std::shared_ptr<Product> &product) {
	this->productList_.emplace_back(product);
	switch (product->getTypeOfProduct()) {
	case TypeOfProduct::NonPerishable: numberOfNonPerishableProducts_++; break;
	case TypeOfProduct::NonAlimentary: numberOfNonAlimentaryProducts_++;
	case TypeOfProduct::Alimentary: numberOfPerishableProducts_++; break;
	}
	return *this;
}

Store& Store::operator-=(std::string barCode) {
	this->productList_.remove_if([this, barCode](std::shared_ptr<Product> product) {
		if (product->getBarCode() == barCode) {
			switch (product->getTypeOfProduct()) {
			case TypeOfProduct::NonPerishable: numberOfNonPerishableProducts_--; break;
			case TypeOfProduct::NonAlimentary: numberOfNonAlimentaryProducts_--;
			case TypeOfProduct::Alimentary: numberOfPerishableProducts_--; break;
			}
			return true;
		}
		return false;
	});
	return *this;
}


Store& Store::operator+=(std::unique_ptr<Order> order) {
	this->orderList_.emplace_back(std::move(order));
	return *this;
}

bool Store::isProductInStore(std::string barCode) const {
	return std::find_if(productList_.begin(), productList_.end(), [barCode](std::shared_ptr<Product> product) { return product->getBarCode() == barCode; }) != productList_.end();
}

int Store::getNumberOfSolvedOrdersInYear(int year) const {
	int result = 0;
	for (const auto &it : orderList_) {
		if (it->getEndDate().getYear() == year)
			result++;
	}
	return result;
}

int Store::getNumberOfNonAlimentaryProducts() const {
	return numberOfNonAlimentaryProducts_;
}

int Store::getNumberOfNonPerishableProducts() const {
	return numberOfNonPerishableProducts_;
}

int Store::getNumberOfPerishableProducts() const {
	return numberOfPerishableProducts_;
}

void Store::showExpiredProducts() const {
	std::string expiredProducts = "";
	for (auto it : productList_) {
		if (it->getTypeOfProduct() == TypeOfProduct::NonAlimentary || it->getTypeOfProduct() == TypeOfProduct::Alimentary) {
			PerishableProduct *perishableProduct = dynamic_cast<PerishableProduct*>(&*it);
			if (DateTime::getCurrentDate() > perishableProduct->getExpirationDate()) {
				expiredProducts += "#" + perishableProduct->getBarCode() + " ";
			}
		}
	}
	if (expiredProducts == "") std::cout << "There are no expired products in the store!\n";
	else std::cout << "Expired products are: " + expiredProducts + "\n";
}

void Store::sortOrderListBy(SortCriteria sortCriteria) {
	orderList_.sort([sortCriteria](const std::unique_ptr<Order>& first, const std::unique_ptr<Order>& second) {
		switch (sortCriteria) {
			case SortCriteria::StartDate:
				return first->getStartDate() < second->getStartDate();
			case SortCriteria::EndDate:
				return first->getEndDate() < second->getEndDate();
		}
		return false;
	});
}

Store& Store::operator+=(std::string storePath) {
	std::string productsPath = storePath + "\\Products";
	std::string productTypes[] = { "Alimentary", "Non Alimentary", "Non Perishable" };
	for (auto &type : productTypes) {
		for (auto &productFile : std::experimental::filesystem::directory_iterator(productsPath + "\\" + type)) {
			std::ifstream fin(productFile.path().string());

			std::string barCode = productFile.path().string().substr(productFile.path().string().find_last_of("\\") + 1);
			barCode = barCode.substr(0, barCode.find("."));

			int amount;
			double pricePerPiece;
			fin >> amount >> pricePerPiece;

			if (type == "Alimentary") {
				int second, minute, hour, day, month, year;
				fin >> second >> minute >> hour >> day >> month >> year;
				DateTime expiration(second, minute, hour, day, month, year);

				double caloriesPerOneHundredGrams;
				fin >> caloriesPerOneHundredGrams;

				Biological biological;
				bool isBio;
				fin >> isBio;
				if (isBio) biological = Biological::YES;
				else biological = Biological::NO;

				std::shared_ptr<Product> alimentaryProduct = std::make_shared<AlimentaryProduct>(barCode, amount, pricePerPiece, expiration, caloriesPerOneHundredGrams, biological);
				*this += std::move(alimentaryProduct);
			}
			else if (type == "Non Alimentary") {
				int second, minute, hour, day, month, year;
				fin >> second >> minute >> hour >> day >> month >> year;
				DateTime expiration(second, minute, hour, day, month, year);

				double toxicityGrade;
				fin >> toxicityGrade;

				std::shared_ptr<Product> nonAlimentaryProduct = std::make_shared<NonAlimentaryProduct>(barCode, amount, pricePerPiece, expiration, toxicityGrade);
				*this += std::move(nonAlimentaryProduct);
			}
			else {
				std::shared_ptr<Product> nonPerishableProduct = std::make_shared<NonPerishableProduct>(barCode, amount, pricePerPiece);
				*this += std::move(nonPerishableProduct);
			}
		}
	}
	
	std::string ordersPath = storePath + "\\Orders";
	std::string ordersTypes[] = { "Receiving", "Shipping" };
	for (auto &type : ordersTypes) {
		for (auto &orderFile : std::experimental::filesystem::directory_iterator(ordersPath + "\\" + type)) {
			std::ifstream fin(orderFile.path().string());

			int startSecond, endSecond, startMinute, endMinute, startHour, endHour, startDay, endDay, startMonth, endMonth, startYear, endYear;
			std::string customer;

			fin >> startSecond >> startMinute >> startHour >> startDay >> startMonth >> startYear;
			fin >> endSecond >> endMinute >> endHour >> endDay >> endMonth >> endYear;
			std::getline(fin, customer);
			std::getline(fin, customer);

			DateTime startDate(startSecond, startMinute, startHour, startDay, startMonth, startYear);
			DateTime endDate(endSecond, endMinute, endHour, endDay, endMonth, endYear);

			OrderType orderType;
			if (type == "Receiving") orderType = OrderType::RECEIVING;
			else orderType = OrderType::SHIPPING;

			std::unique_ptr<Order> order = std::make_unique<Order>(startDate, endDate, customer, orderType);

			while (!fin.eof()) {
				std::string barCode;
				fin >> barCode;

				*order += this->getProduct(barCode);
			}

			*this += std::move(order);
		}
	}
	return *this;
}

std::shared_ptr<Product> Store::getProduct(std::string barCode) const {
	auto it = std::find_if(productList_.begin(), productList_.end(), [barCode](std::shared_ptr<Product> product) { return product->getBarCode() == barCode; });
	return *it;
}

void Store::showAverageNumberOfOrderedProducts() const {
	double average = std::accumulate(std::next(orderList_.begin()), orderList_.end(), (double)orderList_.front()->getProductList().size(), [](double order, const std::unique_ptr<Order>& nextOrder) {
		return order + nextOrder->getProductList().size();
	});
	average /= orderList_.size();

	std::cout << "The average of ordered products is: " << average << " products per order!\n";
}

void Store::showStatistics() const {
	std::map<int, std::map<std::string, double>> statistics;

	for (auto &order : orderList_) {
		if (order->getOrderType() == OrderType::SHIPPING) {
			for (auto &product : order->getProductList()) {
				statistics[order->getEndDate().getYear()][DateTime::getMonthName(order->getEndDate().getMonth())] += product->getPricePerPiece();
			}
		}
	}

	for (auto &stats : statistics) {
		std::cout << "\nYear " << stats.first << " came with the following values for shipped products:\n";
		double totalPrice = 0.0;
		for (int i = 1; i <= 12; ++i) {
			std::cout << DateTime::getMonthName(i) << ": $" << stats.second[DateTime::getMonthName(i)] << "\n";
			totalPrice += stats.second[DateTime::getMonthName(i)];
		}
		std::cout << "Total price for shipped products this year is: $" << totalPrice << "!\n";
	}
}