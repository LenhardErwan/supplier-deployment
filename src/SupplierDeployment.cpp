#include "SupplierDeployment.hpp"
#include <string>
#include <fstream>
#include <iostream>

SupplierDeployment::SupplierDeployment() { }

SupplierDeployment::~SupplierDeployment() { }

void SupplierDeployment::readFile(std::string file) {
	//defining the ifstream
	std::ifstream inFile;

	//opening the file and preventing errors
	inFile.open(file);
	if (!inFile) {
		std::cerr << "Error could not read the specified file!" << std::endl;
		exit(1);
	}

	std::string number;

	inFile >> number;
	inFile >> number;
	inFile >> this->nbSuppliers;
	inFile >> this->nbClients;
	inFile >> number;

	while(inFile.good()) {
		unsigned int id;
		unsigned int openingPrice;
		unsigned int connectionPrice;

		inFile >> id;
		inFile >> openingPrice;

		Supplier s = Supplier(id, openingPrice);

		for (int i = 0; i < this->nbClients; i++) {
			inFile >> connectionPrice;

			s.addConnectionPrice(connectionPrice);
		}

		this->suppliers.push_back(s);
	}

	std::cout << this->nbSuppliers << " suppliers and " << this->nbClients << " clients." << std::endl;
}

void SupplierDeployment::writeFile() {
	for(Supplier s : this->openSuppliers)
		std::cout << s.getId() << std::endl;
}

unsigned int SupplierDeployment::eval(std::vector<Supplier> openSuppliers) {
	unsigned int total = 0;
	std::vector<int> clientMinPrice(this->nbClients, NULL);

	for (Supplier &supplier : openSuppliers) {
		total += supplier.getOpeningPrice();
		for (size_t i = 0; i < this->nbClients; i++) {
			int connectionPrice = supplier.getConnectionPrices().at(i);
			int actualMinPrice = clientMinPrice.at(i);
			if(actualMinPrice == NULL || actualMinPrice > connectionPrice) {
				clientMinPrice.at(i) = connectionPrice;
			}
		}
	}
	for (int &minPrice : clientMinPrice) {
		total += minPrice;
	}
	
	return total;
}

void SupplierDeployment::greedy() { }

void SupplierDeployment::greedyLocalSearch() { }

void SupplierDeployment::linear() { }

void SupplierDeployment::linearRandom() { }
