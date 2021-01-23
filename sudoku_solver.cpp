#include "./src/csp.hpp"
#include <iostream>
#include <queue>

bool removeInconsistencies(CSP &sudo, Loc loc1, Loc loc2) {
	std::set<int> *currSet = &sudo.domains.find(loc2)->second;
	for (auto curr : sudo.domains.find(loc1)->second) {
		if (currSet->size() == 1 && currSet->count(curr)) {
			sudo.domains.find(loc1)->second.erase(curr);
			return true;
		}
	}
	return false;
}

void ac3Algorithm(CSP &csp) {
	std::queue<std::pair<Loc, Loc>> arcQueue;
	for (auto cell : csp.arcs) {
		auto loc = cell.first;
		if (csp.domains.find(loc)->second.size() > 1) {
			for (auto neighbor : cell.second) {
				arcQueue.push(std::make_pair(loc, neighbor));
			}
		}
	}

	while (!arcQueue.empty()) {
		std::pair<Loc, Loc> curr = arcQueue.front();
		arcQueue.pop();
		if (removeInconsistencies(csp, curr.first, curr.second)) {
			for (auto neighbor : csp.arcs.find(curr.first)->second) {
				arcQueue.push(std::make_pair(neighbor, curr.first));
			}
		}
	}
}

int main() {
	CSP csp;

	csp.readCSP();
	ac3Algorithm(csp);
	csp.doBacktracking();
	std::cout << "Output:\n";
	csp.printCSP(true);

	return 0;
}
