#pragma once

#include "Tensor.h"
#include "Common.h"

/**
 * .
 */
Tensor buildZhilinTensor(const Vector& phi);

/**
 * .
 */
Tensor buildRotationTensor(const Vector& phi);

/**
 * .
 */
Tensor buildDotZhilinTensor(const Vector& phi, const Vector& omega);

/**
 * .
 */
Tensor buildTransposeZhilinTensor(Vector phi);
