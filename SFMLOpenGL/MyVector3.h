#ifndef MYVECTOR3 
#define MYVECTOR3


/// <summary>
/// Kevin Andersen
/// 

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector3
{
public:
	double x;
	double y;
	double z;

	/// <summary>
	/// default destructor
	/// as we only have native data types used
	/// these will be automatically returned to
	/// system memory so there's nothing to do
	/// </summary>
	MyVector3();
	~MyVector3();
	std::string toString();

	/// <summary>
	/// Takes in two doubles
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	MyVector3(double x, double y, double z);

	/// <summary>
	/// taking a SFML vector3f
	/// float
	/// </summary>
	/// <param name="t_sfVector">existing vector</param>
	MyVector3(sf::Vector3f t_sfVector);

	/// <summary>
	/// taking a SFML vector3i
	/// int
	/// </summary>
	/// <param name="t_sfVector">existing vector</param>
	MyVector3(sf::Vector3i t_sfVector);

	/// <summary>
	/// constructor taking a SFML vector2i
	/// int
	/// </summary>
	/// <param name="t_vector">existing vector</param>
	MyVector3(sf::Vector2i t_sfVector);

	/// <summary>
	/// constructor taking a SFML vector2u
	/// unsigned
	/// </summary>
	/// <param name="t_vector">existing vector</param>
	MyVector3(sf::Vector2u t_sfVector);

	/// <summary>
	/// constructor taking a SFML vector2f
	/// float
	/// </summary>
	/// <param name="t_vector">existing vector</param>
	MyVector3(sf::Vector2f t_sfVector); 
	
	/// <summary>
	/// equality
	/// </summary>
	/// <param name="t_right">2nd vector</param>
	/// <returns>true if same vectors</returns>
	bool operator == (const MyVector3 t_right) const;

	/// <summary>
	/// inequality
	/// </summary>
	/// <param name="t_right">2nd vector</param>
	/// <returns>true if not same vectors</returns>
	bool operator != (const MyVector3 t_right) const;

	/// <summary>
	/// overload for plus operator 
	/// </summary>
	/// <param name="t_right"></param>
	/// <returns>vector sum</returns>
	MyVector3 operator +(const MyVector3 t_right) const;

	/// <summary>
	/// overload for subtraction
	/// </summary>
	/// <param name="t_right"></param>
	/// <returns>difference between vectors</returns>
	MyVector3 operator -(const MyVector3 t_right) const;

	/// <summary>
	/// overload for multiply
	/// </summary>
	/// <param name="t_scalar"></param>
	/// <returns>product of three</returns>
	MyVector3 operator *(const double t_scalar) const;

	/// <summary>
	/// overload of division
	/// </summary>
	/// <param name="t_divisor"></param>
	/// <returns>vector</returns>
	MyVector3 operator /(const double t_divisor) const;

	/// <summary>
	/// plus equals
	/// </summary>
	/// <param name="t_right"></param>
	/// <returns>vector sum</returns>
	MyVector3 operator +=(const MyVector3 t_right);
	
	/// /// <summary>
	/// minus equals
	/// </summary>
	/// <param name="t_right"></param>
	/// <returns>vector difference</returns>
	MyVector3 operator -=(const MyVector3 t_right);

	
	// negative of a vector 
	MyVector3 operator -();
	
	//gets length of vector
	double length()const;
	//calculates the length squared
	double lengthSquared()const;
	//dot product of the three vectors
	double dot(const MyVector3 t_other) const;
	//crossProduct of the vectors
	MyVector3 crossProduct(const MyVector3 t_other)const;

	//angle between the vectors
	double angleBetween(const MyVector3 t_other)const;
	//gets a normal vector for the current vector
	MyVector3 unit() const;
	//changes lenght of this vector to 1
	void normalise();
	// projection of other onto the current vector so answer will parralell to current vector.
	MyVector3 projection(const MyVector3 t_other)const;
	//rejection the remainder after projection or the perpenduicular
	MyVector3 rejection(const MyVector3 t_other)const;


	operator sf::Vector2f() { return sf::Vector2f(static_cast<float>(x), static_cast<float>(y)); };
	operator sf::Vector2i() { return sf::Vector2i(static_cast<int>(x), static_cast<int>(y)); };
	operator sf::Vector2u() { return sf::Vector2u(static_cast<unsigned int>(x), static_cast<unsigned int>(y)); };
	operator sf::Vector3i() { return sf::Vector3i(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)); };
	operator sf::Vector3f() { return sf::Vector3f(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)); };
	
};



#endif // !MYVECTOR3