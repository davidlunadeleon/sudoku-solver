#include "./csp.hpp"
#include <algorithm>
#include <iostream>

/*
 * 	Constants of the specific CSP problem of Sudoku
 */
const uint8_t numRows = 9;
const uint8_t numColumns = 9;
const uint8_t squareSize = 3;
std::set<int> initialDomain = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // possible values of a cell that is initially empty.

/*
 * 	CSP: constructor of the CSP class that iterates through each cell in the 9x9 grid to build its arcs.
 */
CSP::CSP() {
	for (uint8_t i = 0; i < numRows; ++i) {
		for (uint8_t j = 0; j < numColumns; ++j) {
			Loc tempLoc(i, j);
			arcs.insert(std::make_pair(tempLoc, std::vector<Loc>{}));
			buildArcs(tempLoc);
		}
	}
}

/*
 * 	buildArcs: function to build the arcs of the cell in the location `loc` of the 9x9 grid of the sudoku problem.
 * 		The arcs of each cell are the cells in the same row, column and 3x3 subgrid that establish a constraint.
 */
void CSP::buildArcs(const Loc &loc) {
	for (uint8_t i = 0; i < numRows; ++i) {
		if (i != loc.row) {
			arcs.find(loc)->second.push_back(Loc(i, loc.col));
		}
	}
	for (uint8_t j = 0; j < numColumns; ++j) {
		if (j != loc.col) {
			arcs.find(loc)->second.push_back(Loc(loc.row, j));
		}
	}

	// build the arcs with the 3x3 subgrid in which the cell `loc` is located.
	uint8_t squareRow = loc.row / squareSize;
	uint8_t squareCol = loc.col / squareSize;
	for (uint8_t i = squareRow * squareSize; i < (squareRow + 1) * squareSize; ++i) {
		if (i != loc.row) {
			for (uint8_t j = squareCol * squareSize; j < (squareCol + 1) * squareSize; ++j) {
				if (j != loc.col) {
					arcs.find(loc)->second.push_back(Loc(i, j));
				}
			}
		}
	}
}

/*
 * 	isVarConsistent: function to test if the cell at location `loc` meets its constraints. The domain at `loc` is
 * 		supposed to have only one element in it.
 */
bool CSP::isVarConsistent(const Loc &loc) {
	if (domains.find(loc)->second.size() > 1) {
		return false;
	}
	int val = *domains.find(loc)->second.begin();
	for (auto tempLoc : arcs.find(loc)->second) {
		const auto *domain = &domains.find(tempLoc)->second;
		if (domain->empty() || (domain->size() == 1 && domain->count(val))) {
			return false;
		}
	}
	return true;
}

/*
 * 	doBacktracking: function that assigns the sorted list of variables based on the MRV heuristic and calls the
 * 		recursive function solutionHelper to solve the problem using backtracking.
 */
void CSP::doBacktracking() {
	/*
	 * 	locComp: function used to sort the variables based on the Minimum Remaining Values heuristic.
	 */
	auto locComp = [this](const Loc &loc1, const Loc &loc2) {
		return domains.find(loc1)->second.size() < domains.find(loc2)->second.size();
	};

	for (auto loc : domains) {
		sortedVars.push_back(loc.first);
	}
	std::sort(sortedVars.begin(), sortedVars.end(), locComp);
	solutionHelper(0);
}

/*
 * 	solutionHelper: recursive function to solve the sudoku problem trying all possible remaining values in the domains
 * 		of each variable. It tries each variable in the domain of the cell at location `loc`, deleting the chosen
 * 		value from the other cells that have arcs with `loc` to avoid violating constraints.
 */
bool CSP::solutionHelper(unsigned long depth) {
	if (depth >= sortedVars.size()) {
		return true;
	}
	const Loc *loc = &sortedVars.at(depth);
	std::set<int> domain = domains.find(*loc)->second;
	for (int var : domain) { // Try each variable in the domain of `loc` making it the only value in the domain.
		domains.find(*loc)->second = std::set<int>{var};
		std::vector<bool> wasErased;
		// Remove `var` from the domains of cells that have constraints with `loc`.
		for (auto neighbor : arcs.find(*loc)->second) {
			auto *neighborDomain = &domains.find(neighbor)->second;
			if (neighborDomain->count(var)) {
				neighborDomain->erase(var);
				wasErased.push_back(true);
			} else {
				wasErased.push_back(false);
			}
		}
		if (isVarConsistent(*loc) && solutionHelper(depth + 1)) {
			return true;
		}
		// If assigning `var` as the value in the domain of `loc` fails, return `var` to the domains it belonged to.
		int i = 0;
		for (auto neighbor : arcs.find(*loc)->second) {
			if (wasErased.at(i++)) {
				domains.find(neighbor)->second.insert(var);
			}
		}
	}
	domains.find(*loc)->second = domain;
	return false;
}

/*
 * 	printCSP: function to print the sudoku in its current state. If a variable has a domain with more than one possible
 * 		value, then it prints 0 for that cell or the only possible value otherwise.
 * 		prettyPrint: boolean that determines if the result is printed with margins that make it easier to differentiate
 * 			between 3x3 subgrids, rows and columns. If set to false, the result will be printed as 9 lines of 9 numbers
 * 			each (same format as the input).
 */
void CSP::printCSP(bool prettyPrint) {
	if (prettyPrint) {
		std::cout << "-------------------------------\n";
	}
	for (uint8_t i = 0; i < numRows; ++i) {
		if (prettyPrint) {
			std::cout << "|";
		}
		for (uint8_t j = 0; j < numColumns; ++j) {
			const auto *currSet = &domains.find(Loc(i, j))->second;
			if (currSet->size() > 1) {
				std::cout << (prettyPrint ? " 0 " : "0");
			} else {
				if (prettyPrint) {
					std::cout << ' ' << *currSet->begin() << ' ';
				} else {
					std::cout << *currSet->begin();
				}
			}
			if (prettyPrint && (j + 1) % 3 == 0) {
				std::cout << '|';
			}
		}
		if (prettyPrint) {
			if ((i + 1) % 3 == 0) {
				std::cout << '\n' << "-------------------------------\n";
			} else {
				std::cout << '\n' << "-         -         -         -\n";
			}
		} else {
			std::cout << '\n';
		}
	}
}

/*
 * 	readCSP: read the sudoku from stdin in the format of 9 lines of 9 numbers each. If the value of a cell is unknown,
 * 		the number read must be 0.
 */
void CSP::readCSP() {
	for (uint8_t i = 0; i < numRows; ++i) {
		std::string temp;
		std::cin >> temp;
		for (unsigned long int j = 0; j < temp.size(); ++j) {
			uint8_t curr = temp.at(j) - '0';
			if (curr) {
				domains.insert(std::make_pair(Loc(i, j), std::set<int>{curr}));
			} else {
				domains.insert(std::make_pair(Loc(i, j), initialDomain));
			}
		}
	}
}
