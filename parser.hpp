#pragma once

#include <string>
#include <vector>
#include <utility>
#include <stack>

#include "instruction.hpp"
#include "tokenizer.hpp"

namespace parser {

class Parser {
private:
	int _prevSpot;
	tokenizer::Token _currToken;

	std::pair<int, tokenizer::Token> (*_nextTokenMethod)();
	std::pair<int, tokenizer::Token> (*_peekTokenMethod)(int);

	std::stack<instruction::Operand> _operands;
	int nextTemp;

	void statement(std::vector<instruction::Instruction>&);
	void expression(std::vector<instruction::Instruction>&);
	void term(std::vector<instruction::Instruction>&);
	void factor(std::vector<instruction::Instruction>&);

	void advanceToken();
	void shouldBe(tokenizer::TokenType, const std::string&) const;

	instruction::Operand genTemp();

public:
	explicit Parser(
			std::pair<int, tokenizer::Token> (*nextTokenMethod)(),
			std::pair<int, tokenizer::Token> (*peekTokenMethod)(int)) :
		_prevSpot(-1),
		_currToken(tokenizer::ERR, ""),
		_nextTokenMethod(nextTokenMethod),
		_peekTokenMethod(peekTokenMethod) {}

	std::vector<instruction::Instruction> parse();
};

} // namespace parser