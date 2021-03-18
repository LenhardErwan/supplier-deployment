#include "Supplier.hpp"

Supplier::Supplier(unsigned int id, int openingPrice)
:id(id), openingPrice(openingPrice) { }

Supplier::~Supplier() { }

void Supplier::addConnectionPrice(int connectionPrice) {
	this->connectionPrices.push_back(connectionPrice);
}
