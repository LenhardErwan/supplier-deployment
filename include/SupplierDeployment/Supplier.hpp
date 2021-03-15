#ifndef SUPPLIER_HPP
#define SUPPLIER_HPP

#include <vector>

/**
 * A supplier is idientified by it's id, contains an opening price and a list
 * of connection prices.
 */
class Supplier {
    unsigned int id;
    int openingPrice;
    std::vector<int> connectionPrices;

    public:
        Supplier(unsigned int id, int openingPrice);
        ~Supplier();

        inline void setId(unsigned int id) { this->id = id; }
        inline unsigned int getId() { return this->id; }

        inline void setOpeningPrice(int openingPrice) { this->openingPrice = openingPrice; }
        inline int getOpeningPrice() { return this->openingPrice; }

        void addConnectionPrice(int connectionPrice);
        int sumConnectionPrices();
};

#endif