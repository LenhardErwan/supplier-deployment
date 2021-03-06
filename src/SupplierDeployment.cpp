#include "SupplierDeployment.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "glpk.h"

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

	while(inFile.good() && (this->suppliers.size() < this->nbSuppliers)) {
		unsigned int id;
		unsigned int openingPrice;
		unsigned int connectionPrice;

		inFile >> id;
		inFile >> openingPrice;

		Supplier s = Supplier(id, openingPrice);

		for (unsigned i = 0; i < this->nbClients; i++) {
			inFile >> connectionPrice;

			s.addConnectionPrice(connectionPrice);
		}

		
		this->suppliers.push_back(s);
	}

	std::cout << this->suppliers.size() << " suppliers and " << this->nbClients << " clients." << std::endl;

}

void SupplierDeployment::writeFile(std::string file, std::string algorithm) {
	//defining the fstream
	std::fstream outFile;

    //opening the file and preventing errors
	outFile.open(file,std::ios::out);
	if (!outFile) {
		std::cerr << "Error could not write: " << file << std::endl;
		exit(1);
	}

	outFile << "FILE: " << file << std::endl;
	outFile << "ALGORITHM: " << algorithm << std::endl;
	outFile << this->nbSuppliers;
	outFile << " " << this->nbClients;
	outFile << " " << this->openSuppliers.size();
	outFile << " " << this->eval(this->openSuppliers) << std::endl;
	
	for(Supplier s : this->openSuppliers) {
		outFile << s.getId();
		outFile << " " << s.getOpeningPrice();
		for(int price : s.getConnectionPrices()) {
			outFile << " " << price;
		}
		outFile << std::endl;
	}

	// closing the file
	outFile.close();

	std::cout << "Writing file to '" << file << "'..." << std::endl;
}

unsigned int SupplierDeployment::eval(std::vector<Supplier> openSuppliers) {
	if (openSuppliers.size() == 0)
		return 0;

	unsigned int total = 0;
	std::vector<int> clientMinPrice = openSuppliers.at(0).getConnectionPrices();

	for (Supplier supplier : openSuppliers) {
		total += supplier.getOpeningPrice();
		
		for (unsigned i = 0; i < this->nbClients; i++) {
			int connectionPrice = supplier.getConnectionPrices().at(i);
			int actualMinPrice = clientMinPrice.at(i);

			if(actualMinPrice > connectionPrice) {
				clientMinPrice.at(i) = connectionPrice;
			}
		}
	}

	for (int minPrice : clientMinPrice)
		total += minPrice;

	return total;
}

void SupplierDeployment::greedy() {
	std::vector<Supplier> suppliers = this->suppliers;	// Copy suppliers to erase used one
	this->openSuppliers.clear();						// Reset solution

	bool improve = true; 							// Is the solution improvable
	int minIndex = 0; 								// Index of the supplier which improve with minimal cost
	int nextId = suppliers.at(minIndex).getId(); 	// Id of supplier at minIndex
	int prevId = 0; 								// Id of previous iteration supplier at minIndex

	// If suppliers is not empty and we can improve the solution
	while (!suppliers.empty() && improve) {
		// Loop on closed suppliers
		for (int i = 0; i < suppliers.size(); i++) {
			std::vector<Supplier> copy = this->openSuppliers;
			copy.push_back(suppliers.at(i));

			// If the current suppliers improve the solution
			if (eval(copy) < eval(this->openSuppliers)) {
				minIndex = i;
				nextId = suppliers.at(minIndex).getId();
			}
		}

		// If no suppliers could improve the solution, stop the algorithm
		if (nextId == prevId) {
			improve = false;
		} else {
			this->openSuppliers.push_back(suppliers.at(minIndex));
			prevId = suppliers.at(minIndex).getId();
			suppliers.erase(suppliers.begin() + minIndex);
		}
	}
}

void SupplierDeployment::greedyLocalSearch() {
	greedy();

	std::vector<Supplier> closeSuppliers;	// List of suppliers which are closed

	/**
	 * Fill the vector of closed suppliers by comparing the suppliers and
	 * openSuppliers vector. Improves performance and reduces algorithm
	 * complexity
	 */
	for (Supplier s : this->suppliers) {
		bool isIn = false;
		for (Supplier t : this->openSuppliers) {
			if (s.getId() == t.getId()) {
				isIn = true;
				break;
			}
		}

		if (!isIn) {
			closeSuppliers.push_back(s);
		}
	}

	// Is the solution improvable
	bool improve = true;

	// If suppliers is not empty and we improved the solution
	while (!closeSuppliers.empty() && improve) {
		int gap = 0;		// Gap between current openSuppliers cost and computed suppliers cost
		int toOpenIndex;	// Index of the Supplier we must open from closeSuppliers
		int toCloseIndex;	// Index of the Supplier we must close from openSuppliers

		// Loop on openSuppliers
		for (int i = 0; i < openSuppliers.size(); i++) {
			// Remove the current open supplier from the list
			std::vector<Supplier> copy = this->openSuppliers;
			copy.erase(copy.begin() + i);

			// Loop on closeSuppliers
			for (int j = 0; i < closeSuppliers.size(); i++) {
				// Add the current close supplier in the list
				copy.push_back(closeSuppliers.at(j));
				int price = eval(this->openSuppliers) - eval(copy);	// Compute the gap between the new list and the old list

				// If the new gap is greater than the old gap
				if (price > gap) {
					gap = price;
					toOpenIndex = j;
					toCloseIndex = i;
				}

				// Remove the current close supplier for the next iteration
				copy.pop_back();
			}
		}

		// If we improved the solution
		if (gap > 0) {
			this->openSuppliers.erase(this->openSuppliers.begin() + toCloseIndex);
			this->openSuppliers.push_back(closeSuppliers.at(toOpenIndex));
			closeSuppliers.erase(closeSuppliers.begin() + toOpenIndex);
		} else {
			improve = false;
		}
	}
}

void SupplierDeployment::linear() {
	this->openSuppliers.clear();
	this->probToDat("instance.dat");
	// Create problem
	glp_prob *prob = glp_create_prob();
	glp_tran *tran = glp_mpl_alloc_wksp();
	int ret = glp_mpl_read_model(tran, "./PLNE.mod", 1);
	if(ret != 0) {
		std::cout << "Error on translating model" << std::endl;
		goto skip;
	}

	ret = glp_mpl_read_data(tran, "instance.dat");
	if(ret != 0) {
		std::cout << "Error on translating data" << std::endl;
		goto skip;
	}

	ret = glp_mpl_generate(tran, NULL);
	if(ret != 0) {
		std::cout << "Error on generating model" << std::endl;
		goto skip;
	}

	glp_mpl_build_prob(tran, prob);
	glp_iocp parm;
	glp_init_iocp(&parm);
	parm.presolve = GLP_ON;
	glp_intopt(prob, &parm);
	ret = glp_mpl_postsolve(tran, prob, GLP_MIP);
	if(ret != 0) {
		std::cout << "Error on postsolving model" << std::endl;
		goto skip;
	}

	for (int i = 0; i < this->suppliers.size(); i++) {
		if (glp_mip_col_val(prob, (glp_get_num_cols(prob) - i)) == 1) {
			this->openSuppliers.push_back(this->suppliers.at((this->suppliers.size() - 1) - i));
		}
	}

	skip: glp_mpl_free_wksp(tran);
				glp_delete_prob(prob);
				return;
}

void SupplierDeployment::linearRandom() {
	this->openSuppliers.clear();
	this->probToDat("instance.dat");
	// Create problem
	glp_prob *prob = glp_create_prob();
	glp_tran *tran = glp_mpl_alloc_wksp();
	int ret = glp_mpl_read_model(tran, "./PLNE.mod", 1);
	if(ret != 0) {
		std::cout << "Error on translating model" << std::endl;
		goto skip;
	}

	ret = glp_mpl_read_data(tran, "instance.dat");
	if(ret != 0) {
		std::cout << "Error on translating data" << std::endl;
		goto skip;
	}

	ret = glp_mpl_generate(tran, NULL);
	if(ret != 0) {
		std::cout << "Error on generating model" << std::endl;
		goto skip;
	}

	glp_mpl_build_prob(tran, prob);
	glp_simplex(prob, NULL);
	ret = glp_mpl_postsolve(tran, prob, GLP_MIP);
	if(ret != 0) {
		std::cout << "Error on postsolving model" << std::endl;
		goto skip;
	}
	
	std::srand(std::time(nullptr));
	for (size_t i = 0; i < 10; i++) {
		std::vector<Supplier> tmpSuppliers;
		for (int j = this->suppliers.size()-1; j >= 0; j--) {
			double activity = glp_get_col_prim(prob, (glp_get_num_cols(prob) - j));
			double proba = ((double) std::rand() / (RAND_MAX));
			if(activity > 0 && activity > proba) {
				tmpSuppliers.push_back(this->suppliers.at((this->suppliers.size() - 1) - j));
			}
		}
		if(this->openSuppliers.size() == 0 || eval(tmpSuppliers) < eval(openSuppliers)) {
			this->openSuppliers = tmpSuppliers;
		}
	}

	skip: glp_mpl_free_wksp(tran);
				glp_delete_prob(prob);
				return;
}

void SupplierDeployment::probToDat(std::string file) {
	std::fstream outFile;

  //opening the file and preventing errors
	outFile.open(file, std::ios::out);
	if (!outFile) {
		std::cerr << "Error could not write: " << file << std::endl;
		exit(1);
	}

	outFile << "data;" << std::endl;
	outFile << "param n := " << this->nbSuppliers << ";" << std::endl;
	outFile << "param m := " << this->nbClients << ";" << std::endl;
	outFile << "param F := " << std::endl;
	for (unsigned i = 0; i < this->nbSuppliers; i++) {
		outFile << i+1 << " " << this->suppliers.at(i).getOpeningPrice() << std::endl;
	}
	outFile << ";" << "param C : ";
	for (unsigned i = 0; i < this->nbClients; i++) {
		outFile << i+1 << " ";
	}
	outFile << ":=" << std::endl;
	for (unsigned i = 0; i < this->nbSuppliers; i++) {
		outFile << i+1 << " ";
		for (unsigned j = 0; j < this->nbClients; j++) {
			outFile << this->suppliers.at(i).getConnectionPrices().at(j) << " ";
		}
		outFile << std::endl;
	}
	outFile  << ";" << "end;" << std::endl;

	// closing the file
	outFile.close();

	std::cout << "Data file has been created at: " << file << std::endl;
}
