#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <map>

#include "instruction.hpp"

namespace runner {

class Runner {
private:
	std::map<std::string, int> _variables;
public:
	explicit Runner() = default;
	void run(const std::vector<instruction::Instruction>&, std::ostream&);
};

} // runner