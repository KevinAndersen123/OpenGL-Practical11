  /// <summary>
/// Vector 3 class
/// Kevin Andersen
/// </summary>
#include "MyVector3.h"
#include <string.h>
#define PI           3.14159265358979323846

/// <summary>
/// Defautl constructor set all 3 values to zero
/// </summary>
MyVector3::MyVector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyVector3::~MyVector3()
{
}

/// <summary>
/// 
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and seperated by commas</returns>
std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return output;	
}

MyVector3::MyVector3(double t_x, double t_y, double t_z)
{
	x = { t_x };
	y = { t_y };
	z = { t_z };

}

MyVector3::MyVector3(sf::Vector3f t_sfVector)
{
	x = static_cast<float>(t_sfVector.x);
	y = static_cast<float>(t_sfVector.y);
	z = static_cast<float>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector3i t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = static_cast<int> (t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector2i t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = static_cast<int> (0.0);

}

MyVector3::MyVector3(sf::Vector2u t_sfVector)
{
	x = static_cast<unsigned>(t_sfVector.x);
	y = static_cast<unsigned>(t_sfVector.y);
	z = static_cast<unsigned> (0.0);
}

MyVector3::MyVector3(sf::Vector2f t_sfVector)
{
	x = static_cast<float>(t_sfVector.x);
	y = static_cast<float>(t_sfVector.y);
	z = static_cast<float> (0.0f);
}
//equals operator
bool MyVector3::operator==(const MyVector3 t_right) const
{
	return bool{ x == t_right.x && y == t_right.y && z == t_right.z };
}
//not equal operator
bool MyVector3::operator!=(const MyVector3 t_right) const
{
	const bool result{ x != t_right.x || y != t_right.y || z != t_right.z };
	return result;
}
//addition
MyVector3 MyVector3::operator+(const MyVector3 t_right) const
{
	return MyVector3{ x + t_right.x, y + t_right.y, z + t_right.z };
}

//subtraction
MyVector3 MyVector3::operator-(const MyVector3 t_right) const
{
	return MyVector3{ x - t_right.x, y - t_right.y, z - t_right.y};
}

//changes numbers to negative
MyVector3 MyVector3::operator-()
{
	double answerX = x * -1;
	double answerY = y * -1;
	double answerZ = z * -1;
	return MyVector3(answerX, answerY, answerZ);
	
}
//getting the length of the vector
double MyVector3::length() const
{
	const double answer = std::sqrt((x*x) + (y*y) + (z*z));
	return answer;
}

//squaring the length of the vector
double MyVector3::lengthSquared() const
{
	const double result = (x*x) + (y*y) + (z*z);
	return result;
}
//getting the dot product of the 3D vectors
double MyVector3::dot(const MyVector3 t_other) const
{
	const double result = (x*t_other.x) + (y *t_other.y) + (z*t_other.z);
	return result;
}
//cross product of the 3D vectors
MyVector3 MyVector3::crossProduct(const MyVector3 t_other) const
{

	return MyVector3( (y * t_other.z - z * t_other.y), (z * t_other.x - x * t_other.z),(x * t_other.y - y * t_other.x) );
}
//Angle between 
double MyVector3::angleBetween(const MyVector3 t_other) const
{
	const double cosine = unit().dot(t_other.unit());
	const double angleInRad = std::acos(cosine);
	const double angleInDeg = angleInRad * (180 / PI);
	return angleInDeg;
}
//unit vector
MyVector3 MyVector3::unit() const
{
	double xReturn{ 0.0 };
	double yReturn{ 0.0 };
	double zReturn{ 0.0 };
	double vectorLength = length();
	if (vectorLength != 0.0)
	{
		xReturn = x / vectorLength;
		yReturn = y / vectorLength;
		zReturn = z / vectorLength;
	}
	return MyVector3{ xReturn, yReturn, zReturn };
}
//normalising the vectors
void MyVector3::normalise()
{
	double vectorLength = this->length();
	if (vectorLength != 0.0)
	{
		x= x / vectorLength;
		y = y / vectorLength;
		z = z / vectorLength;
	}
}
//projection
MyVector3 MyVector3::projection(const MyVector3 t_other) const
{
	double scale = dot(t_other) / lengthSquared();

	return this->operator*(scale);
}
//rejection
MyVector3 MyVector3::rejection(const MyVector3 t_other) const
{
	return MyVector3(MyVector3(t_other) - projection(t_other));
}
//Multiply operator
MyVector3 MyVector3::operator*(const double t_scalar) const
{

	return MyVector3{ x * t_scalar, y * t_scalar, t_scalar};
}
//Divide operator
MyVector3 MyVector3::operator/(const double t_divisor) const
{
	if (t_divisor != 0)
	{
		return MyVector3{ x / t_divisor, y / t_divisor, z / t_divisor };
	}
	return MyVector3{};
}
//plus equals operator
MyVector3 MyVector3::operator+=(const MyVector3 t_right)
{
	x += t_right.x;
	y += t_right.y;
	z += t_right.z;
	return MyVector3(x, y, z);
}
//Minus equals operator
MyVector3 MyVector3::operator-=(const MyVector3 t_right)
{
	x -= t_right.x;
	y -= t_right.y;
	z -= t_right.z;
	return MyVector3(x, y, z);
}
	




