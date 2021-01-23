#pragma once

#include "./loc.hpp"
#include <map>
#include <set>
#include <stdint.h>
#include <vector>

using VarType = Loc;
using VarValType = int;

class CSP {
  public:
	std::map<VarType, std::set<VarValType>> domains;
	std::map<VarType, std::vector<VarType>> arcs;

	CSP();
	void printCSP(bool prettyPrint);
	void doBacktracking();
	void readCSP();

  private:
	std::vector<VarType> sortedVars; // For use in the backtracking solution

	bool isVarConsistent(const VarType &var);
	void buildArcs(const VarType &var);
	bool solutionHelper(unsigned long depth);
};
