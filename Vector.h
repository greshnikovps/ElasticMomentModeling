#pragma once
class Vector
{
public:
	Vector();
	Vector(double x, double y, double z);
	~Vector();
	inline double x() const { return m_x; }
	inline double y() const { return m_y; }
	inline double z() const { return m_z; }
	inline double magnitude() const { return m_magnitude; }
private:
	double m_x;
	double m_y;
	double m_z;
	double m_magnitude;
};

Vector operator+(const Vector& lhs, const Vector& rhs);


Vector operator-(const Vector& lhs, const Vector& rhs);

/**
 * скалярное произведение двух векторов.
 */
double operator*(const Vector& lhs, const Vector& rhs);

/**
 * Произведение вектора на число
 */
Vector operator*(const Vector& vect, const double& number);

/**
 * Векторное произведение.
 */
Vector operator%(const Vector& lhs, const Vector& rhs);




