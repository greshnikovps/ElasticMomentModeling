#include "operators.h"
#include <utility> // std::move

Vector operator*(const Vector& vect, const Tensor& tens)
{
	Vector res = {};

	// проходим по всем диадам и считаем произведение
	for (const auto& dyad : tens.getDyads())
	{
		res = res + dyad.second * (dyad.first * vect);
	}

	return res;
	return Vector();
}

Tensor operator%(const Vector& vect, const Tensor& tens)
{
	std::vector<Dyad> dyads;

	// проходим по всем диадам и считаем произведение
	for (auto dyad : tens.getDyads())
	{
		dyad.first = vect % dyad.first;
		dyads.push_back(dyad);
	}

	return Tensor(std::move(dyads));
}
