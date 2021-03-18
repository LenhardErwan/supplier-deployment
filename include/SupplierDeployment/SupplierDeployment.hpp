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
		void writeFile(std::string file, std::string algorithm);

		unsigned int eval(std::vector<Supplier> openSuppliers);

		void greedy();
		void greedyLocalSearch();
		void linear();
		void linearRandom();

		void probToDat(std::string file);
};

#endif
