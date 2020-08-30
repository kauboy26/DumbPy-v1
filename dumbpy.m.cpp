#include <iostream>
#include <string>
#include <sstream>
#include <utility>

#include "tokenizer.hpp"

using namespace tokenizer;

int main() {
	std::string line;
	std::cout << "DumbPy 0.1, on whatever OS you have.\n";

	while (1) {
		std::cout << ">" << ">> ";
		std::getline(std::cin, line);

		int i = 0;
		for (auto p = nextToken(i, line);
				p.second._type != ERR && p.second._type != EOL;
				p = nextToken(i, line)) {

			Token& t = p.second;
			std::cout << i << ": " << t << '\n';

			i = p.first;
		}

		if (i != int(line.size()))
			std::cout << "BIG ERROR occurred : " << i << '\n';

		break;
	}

	return 0;
}

