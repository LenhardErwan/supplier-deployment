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
	unsigned int nbSupplier;
	unsigned int nbCustomers;
	inFile >> number;
	inFile >> number;
	inFile >> nbSupplier;
	inFile >> nbCustomers;
	inFile >> number;

	while(inFile.good()) {
		unsigned int id;
		unsigned int openingPrice;
		unsigned int connectionPrice;

		inFile >> id;
		inFile >> openingPrice;

		Supplier s = Supplier(id, openingPrice);

		for (int i = 0; i < nbCustomers; i++) {
			inFile >> connectionPrice;

			s.addConnectionPrice(connectionPrice);
		}

		this->suppliers.push_back(s);
	}

	std::cout << nbSupplier << " suppliers and " << nbCustomers << " clients." << std::endl;
}

void SupplierDeployment::writeFile() {
	for(Supplier s : this->openSuppliers)
		std::cout << s.getId() << std::endl;
}

void SupplierDeployment::greedy() { }

void SupplierDeployment::greedyLocalSearch() { }

void SupplierDeployment::linear() { }

void SupplierDeployment::linearRandom() { }
