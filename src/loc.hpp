#pragma once

#include <stdint.h>

class Loc {
  public:
	uint8_t row, col;

	Loc(uint8_t x, uint8_t y);
};

bool operator<(const Loc &loc1, const Loc &loc2);
bool operator==(const Loc &loc1, const Loc &loc2);
