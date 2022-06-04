#pragma once

#include "Vector.h"
#include "Tensor.h"
#include <functional>

Vector dotOmega(const Vector& phi, std::function<Vector(const Vector&)> dU, double J);


Vector dotPhi(const Vector& phi, const Vector& omega);

Vector dotOmega193(const Vector& phi, std::function<Vector(const Vector&)> dU, double J);