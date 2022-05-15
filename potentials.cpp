#include "potentials.h"

Vector dU(const Vector& phi) {
	return phi;
}

double U(const Vector& phi) {
	return phi * phi / 2;
}

double d2U(const Vector& phi)
{
	return 1;
}
