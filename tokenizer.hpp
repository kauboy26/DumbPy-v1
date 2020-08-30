#pragma once

#include <utility>
#include <string>
#include <memory>
#include <sstream>

namespace tokenizer {

enum TokenType {PLUS, MULT, LPAREN, RPAREN, ASSEQ, NUM, IDENT, EOL, ERR};
namespace {
std::string tokenPrint[] = {"Plus", "Mult", "Lparen", "Rparen", "AssEq", "Num", "Ident", "EOL", "Err"};
} // namespace

class Token {
private:
public:
	TokenType _type;
	std::string _value;

	explicit Token(TokenType type, std::string value)
	 :	_type(type),
	 	_value(std::move(value)) {}

	friend std::ostream& operator<<(std::ostream& os, const Token& t) {
		os << '(' << tokenPrint[t._type] << ", " << t._value << ')';
		return os;
	} 
};

/*
 * Returns an integer that points to the point in the string where
 * the tokenizer must continue. Call with startFrom = 0 to begin
 * tokenizing from the start of the string.
 *
 * toTokenize - the string to be parsed.
 * startFrom - where the tokenizer should start from. 
 */
std::pair<int, Token> nextToken(int startFrom, const std::string& toTokenize);

}