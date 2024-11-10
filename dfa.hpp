#ifndef DFA_H
#define DFA_H

#include <algorithm>
#include <array>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

#ifndef DFA_NUM_OF_SYMBOLS
	#define DFA_NUM_OF_SYMBOLS 129 //Alphabet + end-of-line character
#endif

#define DFA_COLUMN std::array<int, DFA_NUM_OF_SYMBOLS>
#define DFA_START_STATE 1

class DFA {
	public:
		static DFA_COLUMN emptyRow() {
			DFA_COLUMN column;
			column.fill(0);
			return column;
		}

		DFA() {};
		void addColumn(const DFA_COLUMN &column) { mTable.push_back(column); }
		size_t getNumColumns() const { return mTable.size(); }
		void addEndState(int state) { mEndStates.push_back(state); }
		void removeEndState(int state) { mEndStates.erase(std::remove(mEndStates.begin(), mEndStates.end(), state), mEndStates.end()); }
		bool match(const std::vector<int> &word) const {
			size_t currentState = DFA_START_STATE;
			for(int symbol: word) {
				currentState = mTable.at(currentState).at(symbol);
				if (isTerminalState(currentState))
					return isEndState(currentState);
			}
			return isEndState(currentState);
		};

		void print() const {
			for (int i = 0; i < DFA_NUM_OF_SYMBOLS; i++) {
				std::cout << std::setfill('0') << std::setw((DFA_NUM_OF_SYMBOLS / 10) + 1) << i << ": ";
				for (int j = 0; j < mTable.size(); j++) {
					std::cout << std::setfill('0') << std::setw((mTable.size() / 10) + 1) << mTable.at(j).at(i) << " ";
				}
				std::cout << "\n";
			}
			std::cout << std::endl;
		}
	
	private:
		bool isEndState(int state) const { return std::find(mEndStates.begin(), mEndStates.end(), state) != mEndStates.end(); }
		bool isTerminalState(int state) const { return std::adjacent_find(mTable.at(state).begin(), mTable.at(state).end(), std::not_equal_to<>()) == mTable.at(state).end(); }

		std::vector<DFA_COLUMN> mTable;
		std::vector<int> mEndStates;
};

#endif
