#include <string>
#include <vector>
#include <iostream>

#include "instruction.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

using namespace instruction;
using namespace tokenizer;

namespace parser {

void Parser::statement(std::vector<Instruction>& instrs) {
	if (_currToken.is(IDENT)) {
		advanceToken();

		if (_currToken.is(ASSEQ)) {
			advanceToken();

			expression(instrs);

			shouldBe(EOL, "NO EOL THER!");
			advanceToken();
			return;
		} else if (_currToken.is(EOL)) {
			advanceToken();
			return;
		}

	}

	expression(instrs);

	shouldBe(EOL, "STATEMENT EOL MISSING!");
	advanceToken();
}

void Parser::expression(std::vector<Instruction>& instrs) {
	if (_currToken.is(PLUS) || _currToken.is(MINUS))
		advanceToken();

	term(instrs);

	while (_currToken.is(PLUS) || _currToken.is(MINUS)) {
		advanceToken();
		term(instrs);
	}
}


void Parser::term(std::vector<Instruction>& instrs) {
	factor(instrs);
	while (_currToken.is(MULT) || _currToken.is(DIV)) {
		advanceToken();
		factor(instrs);
	}
}


void Parser::factor(std::vector<Instruction>& instrs) {
	if (_currToken.is(NUM) || _currToken.is(IDENT)) {
		advanceToken();
		return;
	}

	shouldBe(LPAREN, "LPAREN FACTOR ERROR!");
	advanceToken();

	expression(instrs);

	shouldBe(RPAREN, "RPAREN FACTOR ERROR!");
	advanceToken();
}

void Parser::advanceToken() {
	auto p = _nextTokenMethod();
	_prevSpot = p.first;
	_currToken = p.second;
}

void Parser::shouldBe(TokenType type, const std::string& errmsg) const {
	if (!_currToken.is(type)) {
		std::cout << "Position " << _prevSpot << ": Expected " << type << " but received " << _currToken
			<< ", errmsg: " << errmsg << '\n';
		throw std::runtime_error(errmsg);
	}
}

std::vector<Instruction> Parser::parse() {
	std::vector<Instruction> instrs;
	advanceToken();
	statement(instrs);
	return instrs;
}


} // namespace parser