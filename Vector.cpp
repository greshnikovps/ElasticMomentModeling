#include "Vector.h"
#include <math.h>

Vector::Vector()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_magnitude = 0;
}

Vector::Vector(double x, double y, double z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{
	m_magnitude = sqrt(x * x + y * y + z * z);
}

Vector::~Vector()
{
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	return Vector(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

double operator*(const Vector& lhs, const Vector& rhs)
{
	return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}


Vector operator*(const Vector& vect, const double& number)
{
	return Vector(vect.x() * number, vect.y() * number, vect.z() * number);
}

Vector operator%(const Vector& lhs, const Vector& rhs)
{
	return Vector({ 
		lhs.y() * rhs.z() - lhs.z() * rhs.y(),
		lhs.z() * rhs.x() - lhs.x() * rhs.z(),
		lhs.x() * rhs.y() - lhs.y() * rhs.x()
		});
}

