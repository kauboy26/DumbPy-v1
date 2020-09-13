#include <vector>
#include <string>
#include <ostream>
#include <map>
#include <stdexcept>

#include "runner.hpp"
#include "instruction.hpp"

using namespace instruction;
using namespace tokenizer;

namespace runner {

namespace {
int fetchValue(
		const std::map<std::string, int>& map,
		const Operand& opr,
		std::ostream& os) {

	if (opr._type == OPR_NUM) {
		return std::stoi(opr._value);
	}

	if (map.find(opr._value) == map.end()) {
		os << "The variable '" << opr._value << "' has not been defined.\n";
		throw std::runtime_error("UNDEFINED VARIABLE!");
	}
	return map.at(opr._value);	
}
} // namespace

void Runner::run(const std::vector<Instruction>& instrs, std::ostream& os) {
	for (auto& i: instrs) {
		if (i.op == PRINT) {
			os << fetchValue(_variables, i.operands[0], os) << '\n';
			continue;
		} else if (i.op == ASSEQ) {
			_variables[i.operands[0]._value] = fetchValue(_variables, i.operands[1], os);
			continue;
		}

		int val1 = fetchValue(_variables, i.operands[1], os);
		int val2 = fetchValue(_variables, i.operands[2], os);
		int result = 0;
		
		switch (i.op) {
			case PLUS:
				result = val1 + val2;
				break;
			case MINUS:
				result = val1 - val2;
				break;
			case MULT:
				result = val1 * val2;
				break;
			case DIV:
				result = val1 / val2;
				break;
			default:
				throw std::runtime_error("UNEXPECTED OPERATION!");
		}
		_variables[i.operands[0]._value] = result;
	}
}

}