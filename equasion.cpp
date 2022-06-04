#include "equasion.h"
#include "TensorBuildingFunctions.h"

Vector dotOmega(const Vector& phi, std::function<Vector(const Vector&)> dU, double J) {
	return buildZhilinTensor(phi).transpose() * dU(phi) * (-1.0 / J);
}

Vector dotPhi(const Vector& phi, const Vector& omega)
{
	return buildZhilinTensor(phi) * omega;
}

double dUdPhi2(const Vector& phi) {
	return 1;
}

double dUdKphi(const Vector& phi) {
	return 2 * phi.z();
}

Vector dotOmega193(const Vector& phi, std::function<Vector(const Vector&)> dU, double J)
{
	double phi_m = phi.magnitude();
	double phi2 = phi_m * phi_m;
	Tensor P = buildRotationTensor(phi);
	return P * phi * (dUdPhi2(phi) * 2 + dUdKphi(phi) * phi.z() * (2 * (1 - cos(phi_m) - phi_m * sin(phi_m)) / (2 * phi2 * (1 - sin(phi_m))))) +
		(P * Vector(0, 0, 1) * (phi_m * sin(phi_m) / (2 * (1 - cos(phi_m)))) - ((P * phi) % (P * Vector(0, 0, 1)))) * dUdKphi(phi);
}
