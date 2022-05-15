#include "Tensor.h"
#include <utility> // std::move

Tensor::Tensor()
{
	Vector x(1, 0, 0);
	Vector y(0, 1, 0);
	Vector z(0, 0, 1);

	m_dyads.push_back({ x, x, 1 });
	m_dyads.push_back({ y, y, 1 });
	m_dyads.push_back({ z, z, 1 });
}

Tensor::Tensor(const std::vector<Dyad>& dyads)
	: m_dyads(dyads)
{

}

Tensor Tensor::operator*(const Tensor& other)
{
	// создаем вектор диад
	std::vector<Dyad> dyads;
	// проходим по всем диадам и считаем произведение
	for (const auto& otherDyad : other.m_dyads)
	{
		for (const auto& dyad : m_dyads)
		{
			Dyad newDyad = {
				dyad.first,
				otherDyad.second,
				dyad.second * otherDyad.first
			};
			if (abs(newDyad.coef) > DOUBLE_THRESHOLD)
				dyads.push_back(newDyad);
			else
				int lineToAddBreakpoint = 1;
		}
	}
	return Tensor(std::move(dyads));
}

Tensor Tensor::operator+(const Tensor& other)
{
	// создаем вектор диад
	std::vector<Dyad> dyads;
	// проходим по всем диадам и считаем произведение
	for (const auto& otherDyad : other.m_dyads)
		dyads.push_back(otherDyad);

	for (const auto& dyad : m_dyads)
		dyads.push_back(dyad);

	return Tensor(std::move(dyads));
}

Tensor Tensor::operator*(const double& number)
{
	// создаем вектор диад
	std::vector<Dyad> dyads;
	// проходим по всем диадам и считаем произведение
	for (Dyad dyad : m_dyads)
	{
		dyad.coef *= number;
		dyads.push_back(dyad);
	}
	return Tensor(std::move(dyads));
}

Vector Tensor::operator*(const Vector& other)
{
	Vector res = {};
	// проходим по всем диадам и считаем произведение
	for (const auto& dyad : m_dyads)
	{
		res = res + dyad.first * (dyad.second * other);
	}

	return res;
}

Tensor Tensor::transpose()
{
	
	// создаем вектор диад
	std::vector<Dyad> dyads;
	// проходим по всем диадам и считаем произведение
	for (const auto& dyad : m_dyads)
	{
		dyads.push_back({ dyad.second, dyad.first, dyad.coef });
	}
	return Tensor(std::move(dyads));
}

Tensor::~Tensor()
{
}


