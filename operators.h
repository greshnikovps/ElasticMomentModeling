#pragma once
#include "Common.h"
#include "Tensor.h"


/**
 * Скалярное произведение
 */
Vector operator*(const Vector& vect, const Tensor& tens);

/**
 * Векторное произведение.
 */
Tensor operator%(const Vector& vect, const Tensor& tens);




