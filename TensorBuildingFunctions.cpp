#include "TensorBuildingFunctions.h"
#include "operators.h"

Tensor buildZhilinTensor(const Vector& phi)
{
	double firstMagn = 0;
	double secondMagn = 0;
	if (phi.magnitude() < APROXIM_ZERO_THRESHOLD)
	{
		firstMagn = 1.0 - phi.magnitude() * phi.magnitude() / 12;
		secondMagn = 1.0 / 12.0 + phi.magnitude() * phi.magnitude() / 720.0;
	}
	else
	{
		firstMagn = phi.magnitude() * sin(phi.magnitude()) / (2 * (1 - cos(phi.magnitude())));
		secondMagn = 1.0 / (phi.magnitude() * phi.magnitude()) +
			sin(phi.magnitude()) / (2 * phi.magnitude() * (1 - cos(phi.magnitude())));
	}

	std::vector<Dyad> dyads;
	dyads.push_back({ phi, phi, secondMagn });

	return Tensor() * firstMagn +
		phi % Tensor() * (-0.5) +
		Tensor(dyads);
}

Tensor buildRotationTensor(const Vector& phi)
{
	double firstMagn = 0;
	double secondMagn = 0;
	if (phi.magnitude() < APROXIM_ZERO_THRESHOLD)
	{
		firstMagn = 1.0 / 2.0 - phi.magnitude() * phi.magnitude() / 24;
		secondMagn = 1.0 - phi.magnitude() * phi.magnitude() / 6.0;
	}
	else
	{
		firstMagn = (1 - cos(phi.magnitude())) / (phi.magnitude() * phi.magnitude());
		secondMagn = sin(phi.magnitude()) / phi.magnitude();
	}

	std::vector<Dyad> dyads;
	dyads.push_back({ phi, phi, firstMagn });

	return Tensor(dyads) +
		Tensor() * cos(phi.magnitude()) +
		phi % Tensor() * secondMagn;
}

Tensor buildDotZhilinTensor(const Vector& phi, const Vector& omega)
{
	Vector dotPhi = buildZhilinTensor(phi) * omega;
	double firstCoef = 0;
	double secondCoef = 0;
	double thirdCoef = 0;
	const double& phiM = phi.magnitude();
	if (phi.magnitude() < APROXIM_ZERO_THRESHOLD){
		firstCoef = -1.0 / 6.0 - phiM * phiM / 180.0;
		secondCoef = 1.0 / 360.0 + phiM * phiM / 7560.0;
		thirdCoef = 1.0 / 12.0 + phiM * phiM / 720.0;
	}
	else {
		firstCoef = (phiM - sin(phiM)) / (2 * phiM * (cos(phiM) - 1)) * (phi * dotPhi);
		secondCoef = (phiM * phiM + phiM * sin(phiM) + 4 * cos(phiM) - 4) /
			(4 * phiM * phiM * phiM * phiM * sin(phiM / 2) * sin(phiM / 2)) * (phi * dotPhi);
		thirdCoef = 1 / (phiM * phiM) - sin(phiM) / (2 * phiM * (1 - cos(phiM)));
	}
	std::vector<Dyad> secondDiads;
	secondDiads.push_back({ phi, phi, secondCoef });

	std::vector<Dyad> thirdDiads;
	secondDiads.push_back({ dotPhi, phi, thirdCoef });
	secondDiads.push_back({ phi, dotPhi, thirdCoef });

	return Tensor() * firstCoef + dotPhi % Tensor() * (-0.5) + Tensor(secondDiads) + Tensor(thirdDiads);
}

Tensor buildTransposeZhilinTensor(Vector phi)
{
	return Tensor();
}