#include "Solver.h"
#include "operators.h"
#include "TensorBuildingFunctions.h"

#include <iostream> // debug

Solver::Solver()
{
}

Solver::~Solver()
{
}

Solution Solver::solveByEulerMethod(const double& time, const double& dt,
	std::function<double(const Vector&)> U, std::function<Vector(const Vector&)> dU)
{
	double J = 0.1;
	Solution solution;

	// TODO: записать сюда разные граничные условия
	solution.coords.push_back({ 0, 0, 0 });
	Vector omega = { 1, 1, 1 };

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();

		Tensor zhilinTensor = buildZhilinTensor(phi);
		//Tensor rotationTensor = buildRotationTensor(phi);
		omega = omega + zhilinTensor.transpose() * dU(phi) * (-dt / J);
		solution.coords.push_back(phi + zhilinTensor * omega * dt);

		Energy energy;
		energy.kinetic = omega * omega * (J / 2.0);
		energy.potential = U(phi);
		energy.total = energy.kinetic + energy.potential;
		solution.energy.push_back(energy);

		

		t += dt;
	}

	return solution;
}

Solution Solver::solveByVerleMethod(const double& time, const double& dt,
	std::function<double(const Vector&)> U,
	std::function<Vector(const Vector&)> dU,
	std::function<double(const Vector&)> d2U)
{
	double J = 0.1;
	Solution solution;

	// TODO: записать сюда разные граничные условия
	solution.coords.push_back({ 0, 0, 0 });
	Vector omegaPrev = { 1, 1, 1 };
	solution.coords.push_back({ omegaPrev * dt });
	Vector omega = omegaPrev;
	{
		Tensor zhilinTensor = buildZhilinTensor(solution.coords.back());
		omega = omega - zhilinTensor * dU(solution.coords.back()) * (dt / J);
	}

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();

		Tensor zhilinTensor = buildZhilinTensor(phi);
		Tensor transpZhilinTensor = zhilinTensor.transpose();
		Tensor dotZhilinTensor = buildDotZhilinTensor(phi, omega);

		Vector dotPhi = zhilinTensor * omega;
		Vector tmpOmega = omega;

		//omega = omega * 2 - omegaPrev 
		// -( dotPhi * zhilinTensor * d2U(phi) + dU(phi) * dotZhilinTensor) * (dt * dt / J);

		//solution.coords.push_back(phi //* 2 - solution.coords[solution.coords.size() - 2]
		//   + (dotZhilinTensor * omega - zhilinTensor * transpZhilinTensor * dU(phi) * ( 1.0 / J)) * (dt * dt));

		omega = omega + (omega - omegaPrev - transpZhilinTensor * dU(phi) * (dt / J)) * 0.5
			- (dotPhi * zhilinTensor * d2U(phi) + dU(phi) * dotZhilinTensor) * (dt * dt / J);

		solution.coords.push_back(phi + (zhilinTensor * omega * dt + phi - solution.coords[solution.coords.size() - 2]) * 0.5
			+ (dotZhilinTensor * omega - zhilinTensor * transpZhilinTensor * dU(phi) * (1.0 / J)) * (dt * dt));
		
		omegaPrev = tmpOmega;

		Energy energy;
		energy.kinetic = omega * omega * (J / 2.0);
		energy.potential = U(phi);
		energy.total = energy.kinetic + energy.potential;
		solution.energy.push_back(energy);

		t += dt;
	}

	return solution;
}

Solution Solver::solveByFinchamMethod(const double& time, const double& dt,
	std::function<double(const Vector&)> U, std::function<Vector(const Vector&)> dU)
{
	double J = 0.1;
	Solution solution;

	// TODO: записать сюда разные граничные условия
	solution.coords.push_back({ 0, 0, 0 });
	Vector omega = { 1, 1, 1 };

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();
		
		// 1 этап
		Tensor zhilinTensor = buildZhilinTensor(phi);

		Vector intermediateOmega = omega + zhilinTensor.transpose() * dU(phi) * (-dt / (J * 2.0));
		Vector intermediatePhi = phi + zhilinTensor * intermediateOmega * (dt / 2.0);
	
		// 2 этап
		Tensor interZhilinTensor = buildZhilinTensor(intermediatePhi);

		omega = omega + zhilinTensor.transpose() * dU(phi) * (-dt / J);
		solution.coords.push_back(phi + interZhilinTensor * omega * dt);
		
		Energy energy;
		energy.potential = U(phi);
		energy.kinetic = omega * omega * (J / 2.0);
		energy.total = energy.kinetic + energy.potential;
		solution.energy.push_back(energy);

		t += dt;
	}

	return solution;
}

Solution Solver::solveByRungeKuttaMethod(const double& time, const double& dt, std::function<double(const Vector&)> U, std::function<Vector(const Vector&)> dU)
{
	double J = 0.1;
	Solution solution;

	// TODO: записать сюда разные граничные условия
	solution.coords.push_back({ 0, 0, 0 });
	Vector omega = { 1, 1, 1 };

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();


		
		t += dt;
	}

	return solution;
}
