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

	double meanEnergy = omega * omega * (J / 2.0) + U(solution.coords.back());
	double mseEnergy = 0;

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();

		Tensor zhilinTensor = buildZhilinTensor(phi);
		//Tensor rotationTensor = buildRotationTensor(phi);
		
		solution.coords.push_back(phi + zhilinTensor * omega * dt);
		omega = omega + zhilinTensor.transpose() * dU(phi) * (-dt / J);
		Energy energy;
		energy.kinetic = omega * omega * (J / 2.0);
		energy.potential = U(phi);
		energy.total = energy.kinetic + energy.potential;
		solution.energy.push_back(energy);

		mseEnergy += (meanEnergy - energy.total) * (meanEnergy - energy.total);

		t += dt;
	}

	mseEnergy = sqrt(mseEnergy / ((time / dt) * (time / dt - 1)));
	std::cout << "Mean Square Energy Error = " << mseEnergy / meanEnergy << std::endl;

	return solution;
}

Solution Solver::solveByFinchamMethod(const double& time, const double& dt, 
	std::function<double(const Vector&)> U, 
	std::function<Vector(const Vector&)> dU, 
	std::function<Vector( const Vector&, std::function<Vector(const Vector&)>, double)> dotOmega,
	std::function<Vector(const Vector&, const Vector&)> dotPhi)
{
	double J = 0.1;
	Solution solution;

	// TODO: записать сюда разные граничные условия
	solution.coords.push_back({ 0, 0, 0 });
	Vector omega = { 1, 1, 1 };

	double meanEnergy = omega * omega * (J / 2.0) + U(solution.coords.back());
	double mseEnergy = 0;

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();

		// 1 этап
		Vector intermediateOmega = omega + dotOmega(phi, dU, J) * (dt / 2.0);
		Vector intermediatePhi = phi + dotPhi(phi, intermediateOmega) * (dt / 2.0);

		// 2 этап
		omega = omega + dotOmega(phi, dU, J) * dt;
		solution.coords.push_back(phi + dotPhi(intermediatePhi, omega) * dt);

		// Вычисление энергии
		Energy energy;
		energy.potential = U(phi);
		energy.kinetic = omega * omega * (J / 2.0);
		energy.total = energy.kinetic + energy.potential;
		solution.energy.push_back(energy);

		mseEnergy += (meanEnergy - energy.total) * (meanEnergy - energy.total);

		t += dt;
	}

	mseEnergy = sqrt(mseEnergy / ((time / dt) * (time / dt - 1)));
	std::cout << "Mean Square Energy Error = " << mseEnergy / meanEnergy << std::endl;

	return solution;
}


#if 0
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
#endif

Solution Solver::solveByRungeKuttaMethod(const double& time, const double& dt, 
	std::function<double(const Vector&)> U, 
	std::function<Vector(const Vector&)> dU,
	std::function<Vector(const Vector&, std::function<Vector(const Vector&)>, double)> dotOmega,
	std::function<Vector(const Vector&, const Vector&)> dotPhi)
{
	double J = 0.1;
	Solution solution;

	solution.coords.push_back({ 0, 0, 0 });
	Vector omega = { 1, 1, 1 };

	double meanEnergy = omega * omega * (J / 2.0) + U(solution.coords.back());
	double mseEnergy = 0;

	double t = 0;
	while (t < time) {
		Vector phi = solution.coords.back();

		Vector omega_1 = dotOmega(phi, dU, J) * dt;
		Vector phi_1 = dotPhi(phi, omega) * dt;

		Vector omega_2 = dotOmega(phi + phi_1 * 0.5, dU, J) * dt;
		Vector phi_2 = dotPhi(phi + phi_1 * 0.5, omega + omega_1 * 0.5) * dt;

		Vector omega_3 = dotOmega(phi + phi_2 * 0.5, dU, J) * dt;
		Vector phi_3 = dotPhi(phi + phi_2 * 0.5, omega + omega_2 * 0.5) * dt;

		Vector omega_4 = dotOmega(phi + phi_3, dU, J) * dt;
		Vector phi_4 = dotPhi(phi + phi_3, omega + omega_3) * dt;

		omega = omega + (omega_1 + omega_2 * 2.0 + omega_3 * 2.0 + omega_4) * (1.0 / 6.0);
		solution.coords.push_back(phi + 
			(phi_1 + phi_2 * 2.0 + phi_3 * 2.0 + phi_4) * (1.0 / 6.0));

		// Вычисление энергии
		Energy energy;
		energy.potential = U(phi);
		energy.kinetic = omega * omega * (J / 2.0);
		energy.total = energy.kinetic + energy.potential;
		solution.energy.push_back(energy);
		
		mseEnergy += (meanEnergy - energy.total) * (meanEnergy - energy.total);

		t += dt;
	}

	mseEnergy = sqrt(mseEnergy / ((time / dt) * (time / dt - 1)));
	std::cout << "Mean Square Energy Error = " << mseEnergy / meanEnergy << std::endl;

	return solution;
}
