#include "dfa.hpp"
#include <cassert>
#include <iostream>
#include <string>

#define END_OF_LINE_CODE 128

class RegexMatcher{
	public:
		RegexMatcher(const std::string &expression) {
			mDfa.addColumn(DFA::emptyRow());
			parse(expression);
			DFA_COLUMN column{};
			column.fill(mDfa.getNumColumns());
			mDfa.addColumn(column);

			mDfa.addEndState(mDfa.getNumColumns() - 1);
		}

		bool match(const std::string &word) const { 
			if (mForceStart)
				return mDfa.match(string2vec(word));

			bool matched = false;
			for (size_t i = 0; i < word.length() && !matched; i++) {
				matched = mDfa.match(string2vec(word.substr(i)));
			}
			return matched; 
		}

	private:
		void parse(const std::string &expression) {
			for (size_t i = 0; i < expression.length(); i++) {
				char c = expression.at(i);
				DFA_COLUMN column{};
				if (c == '.' && (i == 0 || expression.at(i-1) != '\\')) {
					for (size_t j = 20; j <= 126; j++)
						column[j] = mDfa.getNumColumns() + 1;
				} else if (c == '$' && i == expression.length() - 1 && expression.at(i-1) != '\\') {
					column[END_OF_LINE_CODE] = mDfa.getNumColumns() + 1;
				} else if (c == '^' && i == 0) {
					mForceStart = true;
					continue;
				} else {
					column[getSymbolValue(c)] = mDfa.getNumColumns() + 1;
				}
				mDfa.addColumn(column);
			}
		}

		int getSymbolValue(char c) const {
			return int(c);
		}

		std::vector<int> string2vec(const std::string &str) const {
			std::vector<int> result;
			for (char c: str)
				result.push_back(getSymbolValue(c));
			result.push_back(END_OF_LINE_CODE);
			return result;
		}

		DFA mDfa;
		bool mForceStart = false;
};

void printResult(std::string str, const RegexMatcher &matcher) {
	std::cout << str << ": " << ((matcher.match(str)) ? "true" : "false") << std::endl;
}

int main() {
	RegexMatcher matcher("^a.c");

	printResult("ac", matcher);
	printResult("adc", matcher);
	printResult("abcdef", matcher);
	printResult("Hello World", matcher);
	printResult("deba*c", matcher);

	return 0;
}
