#include <string>
#include <iostream>
#include "SupplierDeployment.hpp"

int main(int argc, char const *argv[]) {
	if (argc >= 3) {
		const std::string algorithm = argv[1];
		const std::string input = argv[2];
		const std::string output = (argc >= 4) ? argv[3] : "./output.txt";

		SupplierDeployment test = SupplierDeployment();
		test.readFile(argv[2]);

		if (argv[1] == "greedy") {
			test.greedy();
		}

		test.writeFile(output);

		return 0;
	}
	else {
		std::cout << "Error during program initialization!" << std::endl;
		std::cout << "Please respect the following syntax: " << std::endl << std::endl;
		std::cout << "\tSupplierDeployment.exe <algorithm> <input> <?output>" << std::endl << std::endl;
		std::cout << "- algorithm: greedy | greedyLocalSearch | linear | linearRandom" << std::endl;
		std::cout << "- input: Path (relative or absolute) to the input file" << std::endl;
		std::cout << "- output (optional): Path (relative or absolute) to the output file" << std::endl;
		return 1;
	}

	return 0;
}
