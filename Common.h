#pragma once

#include "Vector.h"
#include <vector>

#define DOUBLE_THRESHOLD pow(10, -16)
#define APROXIM_ZERO_THRESHOLD pow(10, -5)

struct Dyad {
	Vector first;
	Vector second;
	double coef;
};

struct Energy {
	double kinetic;
	double potential;
	double total;
};

struct Solution {
	std::vector<Vector> coords;
	std::vector<Energy> energy;
};