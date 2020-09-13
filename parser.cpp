#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>

#include "instruction.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

using namespace instruction;
using namespace tokenizer;

namespace parser {
namespace {
/*
 * Helper method to convert a Token to an Operand,
 * with the restriction that the Token must be either
 * a NUM or IDENT.
 */
Operand tokenToOpr(const Token& tok) {
	if (tok.is(NUM))
		return Operand(OPR_NUM, tok._value);
	return Operand(OPR_IDENT, tok._value);
}
} // namespace

void Parser::statement(std::vector<Instruction>& instrs) {
	if (_currToken.is(IDENT) && _peekTokenMethod(1).second.is(ASSEQ)) {
		_operands.push(tokenToOpr(_currToken));
		advanceToken(); // move past variable

		Instruction i(ASSEQ, {_operands.top() });
		_operands.pop();
		advanceToken(); // move past ASSEQ

		expression(instrs);
		i.operands.push_back(_operands.top());
		_operands.pop();
		instrs.push_back(std::move(i));

		shouldBe(EOL, "NO EOL THERE!!");
		advanceToken();
		return;
	}

	expression(instrs);
	instrs.push_back(Instruction(PRINT, { _operands.top() }));
	_operands.pop();

	shouldBe(EOL, "STATEMENT EOL MISSING!");
	advanceToken();
}

void Parser::expression(std::vector<Instruction>& instrs) {
	if (_currToken.is(PLUS) || _currToken.is(MINUS)) {
		Operand tmp = genTemp();
		Instruction i(_currToken._type, { tmp, tokenToOpr(Token(NUM, "0")) });
		advanceToken();
		term(instrs);
		i.operands.push_back(_operands.top());
		_operands.pop();
		_operands.push(std::move(tmp));
		instrs.push_back(std::move(i));
	} else {
		term(instrs);
	}

	while (_currToken.is(PLUS) || _currToken.is(MINUS)) {
		Operand tmp = genTemp();
		Instruction i = Instruction(_currToken._type, { tmp, _operands.top() });
		_operands.pop();

		advanceToken();
		term(instrs);

		i.operands.push_back(_operands.top());
		_operands.pop();
		instrs.push_back(std::move(i));
		_operands.push(std::move(tmp));
	}
}


void Parser::term(std::vector<Instruction>& instrs) {
	factor(instrs);
	while (_currToken.is(MULT) || _currToken.is(DIV)) {
		Operand tmp = genTemp();
		Instruction i(_currToken._type, { tmp, _operands.top() });
		_operands.pop();

		advanceToken();
		factor(instrs);

		i.operands.push_back(_operands.top());
		_operands.pop();
		instrs.push_back(std::move(i));
		_operands.push(std::move(tmp));
	}
}


void Parser::factor(std::vector<Instruction>& instrs) {
	if (_currToken.is(NUM) || _currToken.is(IDENT)) {
		_operands.push(tokenToOpr(_currToken));
		advanceToken();
		return;
	}

	shouldBe(LPAREN, "LPAREN FACTOR ERROR!");
	advanceToken();

	expression(instrs);
	// VKTODO - push operand something here or what?

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
	nextTemp = 0;
	advanceToken();
	statement(instrs);
	return instrs;
}

Operand Parser::genTemp() {
	return Operand(OPR_IDENT, "t_" + std::to_string(nextTemp++));
}

} // namespace parser