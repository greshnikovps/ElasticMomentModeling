#pragma once

#include <vector>
#include "Common.h"

class Tensor
{
public:
	/** создает единичный тензор */
	Tensor();

	Tensor(const std::vector<Dyad>& dyads);

	Tensor operator*(const Tensor& other);

	Tensor operator+(const Tensor& other);

	Tensor operator*(const double& number);

	Vector operator*(const Vector& other);

	inline const std::vector<Dyad>& getDyads() const{
		return m_dyads;
	}

	/**
	 * транспонирование тензора.
	 * 
	 * \return транспонированный тензор
	 */
	Tensor transpose();

	~Tensor();
private:
	std::vector<Dyad> m_dyads;
};




