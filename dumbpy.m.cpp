#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <stdexcept>
#include <deque>

#include "tokenizer.hpp"
#include "parser.hpp"
#include "instruction.hpp"
#include "runner.hpp"

using namespace instruction;

static int currSpot = 0;
static std::string line;

static std::deque<std::pair<int, tokenizer::Token>> tq;

namespace {

void resetSpot() {
	currSpot = 0;
}

std::pair<int, tokenizer::Token> nextToken() {
	auto p = tq.empty() ? tokenizer::nextToken(currSpot, line) : tq.front();
	if (!tq.empty())
		tq.pop_front();

	currSpot = p.first;
	return p;
}

std::pair<int, tokenizer::Token> peekToken(int i) {
	i = i - 1;
	while ((size_t)i >= tq.size()) {
		tq.push_back(tokenizer::nextToken(currSpot, line));
	}
	return tq[i];
}

} // namespace


int main() {
	std::cout << "DumbPy 0.1, on whatever OS you have. Type 'exit' to exit.\n";
	auto runner = runner::Runner();

	while (1) {
		std::cout << ">" << ">> ";
		std::getline(std::cin, line);
		if (line == "exit")
			break;

		auto parser = parser::Parser(nextToken, peekToken);

		try {
			auto instrs = parser.parse();
			runner.run(instrs, std::cout);
		} catch (const std::exception& e) {
			std::cout << "There was an error." << '\n';
		}
		
		resetSpot();
	}

	return 0;
}