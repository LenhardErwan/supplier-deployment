#include <string>
#include <iostream>
#include "SupplierDeployment.hpp"

int main(int argc, char const *argv[]) {
	if (argc >= 3 &&
		(argv[1] == std::string("greedy") ||
		argv[1] == std::string("greedyLocalSearch") ||
		argv[1] == std::string("linear") ||
		argv[1] == std::string("linearRandom"))
	) {
		const std::string algorithm = argv[1];
		const std::string input = argv[2];
		const std::string output = (argc >= 4) ? argv[3] : "./output.txt";

		SupplierDeployment test = SupplierDeployment();
		test.readFile(argv[2]);

		if (argv[1] == std::string("greedy")) {
			test.greedy();
		} else if (argv[1] == std::string("greedyLocalSearch")) {
			test.greedyLocalSearch();
		} else if (argv[1] == std::string("linear")) {
			test.linear();
		} else if (argv[1] == std::string("linearRandom")) {
			test.linearRandom();
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
