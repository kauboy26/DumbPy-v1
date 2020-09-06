#pragma once

#include <utility>
#include <string>
#include <vector>

namespace instruction {

enum OpType {OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_ASSEQ};

class Instruction {
private:
public:
	OpType op;
	std::vector<std::string> operands;

	explicit Instruction(OpType optype, std::vector<std::string> oprs) :
		op(optype),
		operands(std::move(oprs)) {}
};

}