#pragma once

#include <string>
#include <vector>
#include <utility>

#include "instruction.hpp"
#include "tokenizer.hpp"

namespace parser {

class Parser {
private:
	int _prevSpot;
	tokenizer::Token _currToken;

	std::pair<int, tokenizer::Token> (*_nextTokenMethod)();

	void statement(std::vector<instruction::Instruction>&);
	void expression(std::vector<instruction::Instruction>&);
	void term(std::vector<instruction::Instruction>&);
	void factor(std::vector<instruction::Instruction>&);

	void advanceToken();
	void shouldBe(tokenizer::TokenType, const std::string&) const;

public:
	explicit Parser(std::pair<int, tokenizer::Token> (*nextTokenMethod)()) :
	_prevSpot(-1),
	_currToken(tokenizer::ERR, ""),
	_nextTokenMethod(nextTokenMethod) {}

	std::vector<instruction::Instruction> parse();
};

} // namespace parser