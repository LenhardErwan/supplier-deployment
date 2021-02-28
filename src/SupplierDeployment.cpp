#include <SupplierDeployment.hpp>
#include <string>
#include <fstream>
#include <iostream>

int readFile(std::string file) {

	//defining the ifstream
	std::ifstream inFile;

	//opening the file and preventing errors
    inFile.open(file);
    if (!inFile) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier d'entrée." << std::endl;
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

    std::cout << "Nous avons " << nbSupplier << " fournisseurs et " << nbCustomers << " clients." << std::endl;

    // while(inFile.good()) {
    //     inFile >> number;
    //     std::cout << number << std::endl;
    // }
    
    return 0;
}