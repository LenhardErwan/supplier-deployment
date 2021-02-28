#ifndef SUPPLIER_DEPLOYMENT_HPP
#define SUPPLIER_DEPLOYMENT_HPP

#include <string>

class SupplierDeployment {
    // selectedAlgo
    // suppliers
    // openSuppliers

    public:
        SupplierDeployment();
        ~SupplierDeployment();

        // setSelectedAlgo
        // getSelectedAlgo

        // addSupplier
        // getSuppliers
        // removeSupplier

        // addOpenSupplier
        // getOpenSuppliers
        // removeOpenSupplier

        void readFile(std::string file);
        void writeFile();

        void greedy();
        void greedyLocalSearch();
        void linear();
        void linearRandom();
};

#endif
