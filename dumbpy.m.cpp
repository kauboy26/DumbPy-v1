#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <stdexcept>

#include "tokenizer.hpp"
#include "parser.hpp"
#include "instruction.hpp"

static int currSpot = 0;
static std::string line;
void resetSpot() {
	currSpot = 0;
}

std::pair<int, tokenizer::Token> nextToken() {
	auto p = tokenizer::nextToken(currSpot, line);
	currSpot = p.first;
	return p;
}

int main() {
	std::cout << "DumbPy 0.1, on whatever OS you have. Type 'exit' to exit.\n";

	while (1) {
		std::cout << ">" << ">> ";
		std::getline(std::cin, line);
		if (line == "exit")
			break;

		parser::Parser parser = parser::Parser(nextToken);

		try {
			parser.parse();
		} catch (const std::exception& e) {
			std::cout << "There was an error." << '\n';
		}
		
		resetSpot();
	}

	return 0;
}