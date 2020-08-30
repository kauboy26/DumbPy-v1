#include <iostream>

#include "tokenizer.hpp"

namespace tokenizer {

namespace {
bool isLetter(char c) {
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

bool isNumber(char c) {
	return '0' <= c && c <= '9';
}

bool isPlus(char c) {
	return c == '+';
}

bool isMult(char c) {
	return c == '*';
}

bool isLparen(char c) {
	return c == '(';
}

bool isRparen(char c) {
	return c == ')';
} 

bool isWhite(char c) {
	return c == '\t' || c == ' ';
}

bool isEqual(char c) {
	return c == '=';
}
} // namespace



std::pair<int, Token> nextToken(int startFrom, const std::string& toTokenize) {
	if (startFrom < 0 || startFrom > int(toTokenize.size())) {
		std::cout << "Error! nextToken startFrom invalid, line: '"
				<< toTokenize << "', startFrom: "
				<< startFrom << '\n';
		return std::make_pair(-1, Token(ERR, ""));
	}

	size_t i = startFrom;

	while (isWhite(toTokenize[i]) && i < toTokenize.size())
		i++;

	if (i == toTokenize.size())
		return std::make_pair(-1, Token(EOL, ""));


	size_t start = i;

	if (isLetter(toTokenize[i])) {
		while (i < toTokenize.size() && (isLetter(toTokenize[i]) || isNumber(toTokenize[i])))
			i++;
		// Now we have reached the end of the stream of characters,
		// that should make up an identifier.
		return std::make_pair(i, Token(IDENT, toTokenize.substr(start, i - start)));
	} else if (isNumber(toTokenize[i])) {
		while (i < toTokenize.size() && isNumber(toTokenize[i]))
			i++;

		if (i < toTokenize.size() && isLetter(toTokenize[i])) {
			std::cout << "Malformed number at position " << i << ", character '" << toTokenize[i] << "'.\n";
			return std::make_pair(i, Token(ERR, ""));
		}

		return std::make_pair(i, Token(NUM, toTokenize.substr(start, i - start)));

	} else if (isPlus(toTokenize[i])) {
		i++;
		return std::make_pair(i, Token(PLUS, ""));
	} else if (isMult(toTokenize[i])) {
		i++;
		return std::make_pair(i, Token(MULT, ""));
	} else if (isLparen(toTokenize[i])) {
		i++;
		return std::make_pair(i, Token(LPAREN, ""));
	} else if (isRparen(toTokenize[i])) {
		i++;
		return std::make_pair(i, Token(RPAREN, ""));
	} else if (isEqual(toTokenize[i])) {
		i++;
		return std::make_pair(i, Token(ASSEQ, ""));
	} else {
		std::cout << "Error! Unexpected character '" << toTokenize[i] << "' at position " << i << '.' << '\n';
		return std::make_pair(i, Token(ERR, ""));
	}
}

} // namespace tokenizer