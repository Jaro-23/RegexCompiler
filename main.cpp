#include "dfa.hpp"
#include <cassert>
#include <iostream>
#include <string>

#define END_OF_LINE_CODE 128

class RegexMatcher{
	public:
		RegexMatcher(const std::string &expression) {
			mDfa.addColumn(DFA::emptyRow());
			for (char c : expression) {
				DFA_COLUMN column{};
				column[getSymbolValue(c)] = mDfa.getNumColumns() + 1;
				mDfa.addColumn(column);
			}
			DFA_COLUMN column{};
			int lastColumn = mDfa.getNumColumns() + 1;
			column[END_OF_LINE_CODE] = lastColumn;
			mDfa.addColumn(column);
			column.fill(lastColumn);
			mDfa.addColumn(column);
			mDfa.addEndState(lastColumn);
		}

		bool match(const std::string &word) const { return mDfa.match(string2vec(word)); }

	private:
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
};

void printResult(std::string str, const RegexMatcher &matcher) {
	std::cout << str << ": " << ((matcher.match(str)) ? "true" : "false") << std::endl;
}

int main() {
	RegexMatcher matcher("abc");

	printResult("ab", matcher);
	printResult("c", matcher);
	printResult("abc", matcher);
	printResult("Hello World", matcher);
	printResult("Something else", matcher);

	return 0;
}
