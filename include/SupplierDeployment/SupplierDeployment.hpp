#ifndef SUPPLIER_DEPLOYMENT_HPP
#define SUPPLIER_DEPLOYMENT_HPP

#include "Supplier.hpp"
#include <string>
#include <vector>

class SupplierDeployment {
	unsigned int nbSuppliers;
	unsigned int nbClients;
	std::vector<Supplier> suppliers;
	std::vector<Supplier> openSuppliers;

	public:
		SupplierDeployment();
		~SupplierDeployment();

		void readFile(std::string file);
		void writeFile();

		void greedy();
		void greedyLocalSearch();
		void linear();
		void linearRandom();
};

#endif
