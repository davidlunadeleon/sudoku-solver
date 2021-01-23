#include "./loc.hpp"

Loc::Loc(uint8_t x, uint8_t y) {
	this->row = x;
	this->col = y;
}

bool operator<(const Loc &loc1, const Loc &loc2) { return loc1.row * 10 + loc1.col < loc2.row * 10 + loc2.col; }

bool operator==(const Loc &loc1, const Loc &loc2) { return loc1.row == loc2.row && loc1.col == loc2.col; }
