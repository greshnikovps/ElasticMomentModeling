#pragma once
#include "Common.h"
#include <functional>

class Solver
{
public:
	Solver();

	~Solver();

	/**
	 * Solve diff equas system by Euler method.
	 *
	 * \param time
	 * \param dt timeframe
	 * \param U potential
	 * \param dU potential derivative
	 * \return solution
	 */
	Solution solveByEulerMethod(const double& time, const double& dt,
		std::function<double(const Vector&)> U, std::function<Vector(const Vector&)> dU);

	/**
	 * Solve diff equas system by Verle method.
	 *
	 * \param time
	 * \param dt timeframe
	 * \param U potential
	 * \param dU potential derivative
	 * \param d2U second potential derivative
	 * \return solution
	 */
	Solution solveByVerleMethod(const double& time, const double& dt,
		std::function<double(const Vector&)> U, 
		std::function<Vector(const Vector&)> dU,
		std::function<double(const Vector&)> d2U);

	/**
	 * Solve diff equas system by Fincham method.
	 *
	 * \param time
	 * \param dt timeframe
	 * \param U potential
	 * \param dU potential derivative
	 * \return solution
	 */
	Solution solveByFinchamMethod(const double& time, const double& dt,
		std::function<double(const Vector&)> U, std::function<Vector(const Vector&)> dU);

	/**
	 * Solve diff equas system by Fincham method.
	 *
	 * \param time
	 * \param dt timeframe
	 * \param U potential
	 * \param dU potential derivative
	 * \return solution
	 */
	Solution solveByRungeKuttaMethod(const double& time, const double& dt,
		std::function<double(const Vector&)> U, std::function<Vector(const Vector&)> dU);

};

