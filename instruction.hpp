#pragma once

#include <utility>
#include <string>
#include <vector>

#include "tokenizer.hpp"

namespace instruction {

namespace {
std::string opPrint[] = {" + ", " - ", " * ", " / ", " = ", "print "};
} // namespace

enum OprType {OPR_NUM, OPR_IDENT};

class Operand {
public:

	OprType _type;
	std::string _value;

	explicit Operand(OprType type, std::string value) :
		_type(type),
		_value(std::move(value)) {}

	friend std::ostream& operator<<(std::ostream& os, const Operand& i) {
		os << i._value;
		return os;
	}
};

class Instruction {
private:
public:
	tokenizer::TokenType op;
	std::vector<Operand> operands;

	explicit Instruction() = default;

	explicit Instruction(tokenizer::TokenType optype, std::vector<Operand> oprs) :
		op(optype),
		operands(std::move(oprs)) {}

	friend std::ostream& operator<<(std::ostream& os, const Instruction& i) {
		if (i.op == tokenizer::ASSEQ) {
			os << i.operands[0] << opPrint[i.op] << i.operands[1];
		} else if (i.op == tokenizer::PRINT) {
			os << opPrint[i.op] << i.operands[0];
		} else {
			os << i.operands[0] << " = " << i.operands[1] << opPrint[i.op] << i.operands[2];
		}

		return os;
	}
};

}