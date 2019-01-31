/// <summary>
/// Matrix 3 class
/// @author Kevin Andersen
/// </summary>
#include "InitialMyMatrix3.h"

/// <summary>
/// default constuctor setting values
/// </summary>
MyMatrix3::MyMatrix3()
{
	m_11 = 1, m_12 = 1, m_13 = 1,
	m_21 = 1, m_22 = 1, m_23 = 1,
	m_31 = 1, m_32 = 1, m_33 = 1;
}

/// <summary>
///  assigns the created matrix numbers to new variables for the matrix
/// </summary>
MyMatrix3::MyMatrix3(double t_a11, double t_a12, double t_a13, double t_a21, double t_a22, double t_a23, double t_a31, double t_a32, double t_a33)
{
	m_11 = t_a11; m_12 = t_a12; m_13 = t_a13;
	m_21 = t_a21; m_22 = t_a22; m_23 = t_a23;
	m_31 = t_a31; m_32 = t_a32; m_33 = t_a33;

}

/// <summary>
/// assigns the passed vector rows to the rows of the matrix(row 1: m_11-> m_13 etc.)
/// </summary>
MyMatrix3::MyMatrix3(MyVector3 t_row1, MyVector3 t_row2, MyVector3 t_row3)
{
	m_11 = t_row1.x; m_12 = t_row1.y; m_13 = t_row1.z;
	m_21 = t_row2.x; m_22 = t_row2.y; m_23 = t_row2.z;
	m_31 = t_row3.x; m_32 = t_row3.y; m_33 = t_row3.z;

}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyMatrix3::~MyMatrix3()
{
}

/// <summary>
/// outputs data to a string
/// </summary>
/// <returns></returns>
std::string MyMatrix3::toString() const
{
	const std::string output = "[" + std::to_string(m_11) + "," + std::to_string(m_12) + "," + std::to_string(m_13) + "]\n[" + std::to_string(m_21) + "," + std::to_string(m_22) + ","
		+ std::to_string(m_23) + "]\n[" + std::to_string(m_31) + "," + std::to_string(m_32) + "," + std::to_string(m_33) + "]";
	return output;
}

//equals operator, returns a bool if true
bool MyMatrix3::operator==(const MyMatrix3 t_other) const
{
	return bool{ m_11 == t_other.m_11 && m_12 == t_other.m_12 && m_13 == t_other.m_13 && //row 1
				m_21 == t_other.m_21 && m_22 == t_other.m_22 && m_23 == t_other.m_23 && //row 2
				m_31 == t_other.m_31 && m_32 == t_other.m_32 && m_33 == t_other.m_33 }; //row 3
}
//notequal operator
bool MyMatrix3::operator!=(const MyMatrix3 t_other) const
{
	const bool result{ m_11 != t_other.m_11 || m_12 != t_other.m_12 || m_13 != t_other.m_13 || //row 1
					   m_21 != t_other.m_21 || m_22 != t_other.m_22 || m_23 != t_other.m_23 || //row 2
					   m_31 != t_other.m_31 || m_32 != t_other.m_32 || m_33 != t_other.m_33 }; //row 3
	return result;
}

//addition opperator
MyMatrix3 MyMatrix3::operator+(const MyMatrix3 t_other) const
{
	return MyMatrix3{m_11 + t_other.m_11,  m_12 + t_other.m_12 , m_13 + t_other.m_13 , //row 1
					 m_21 + t_other.m_21 , m_22 + t_other.m_22 , m_23 + t_other.m_23 , //row 2
					 m_31 + t_other.m_31 , m_32 + t_other.m_32 , m_33 + t_other.m_33 }; //row 3
}

//subtraction operator
MyMatrix3 MyMatrix3::operator-(const MyMatrix3 t_other) const
{
	return MyMatrix3{ m_11 - t_other.m_11,  m_12 - t_other.m_12 , m_13 - t_other.m_13 , //row 1
		m_21 - t_other.m_21 , m_22 - t_other.m_22 , m_23 - t_other.m_23 , //row 2
		m_31 - t_other.m_31 , m_32 - t_other.m_32 , m_33 - t_other.m_33 }; //row 3
}
// multipling two matrices together
MyMatrix3 MyMatrix3::operator*(const MyMatrix3 t_other) const
{
	return MyMatrix3{ m_11 * t_other.m_11 + m_12 * t_other.m_21 + m_13 * t_other.m_31, m_11 * t_other.m_12 + m_12 * t_other.m_22 + m_13 * t_other.m_32, m_11 * t_other.m_13 + m_12 * t_other.m_23 + m_13 * t_other.m_33, //row 1
					  m_21 * t_other.m_11 + m_22 * t_other.m_21 + m_23 * t_other.m_31, m_21 * t_other.m_12 + m_22 * t_other.m_22 + m_23 * t_other.m_32, m_21 * t_other.m_13 + m_22 * t_other.m_23 + m_23 * t_other.m_33, //row 2
					  m_31 * t_other.m_11 + m_32 * t_other.m_21 + m_33 * t_other.m_31, m_31 * t_other.m_12 + m_32 * t_other.m_22 + m_33 * t_other.m_32, m_31 * t_other.m_13 + m_32 * t_other.m_23 + m_33 * t_other.m_33 }; //row 3
		
}
//multipling a vector to matrix, vector is passed in
MyVector3 MyMatrix3::operator*(const MyVector3 t_vector) const
{
	return MyVector3{m_11 * t_vector.x + m_12 * t_vector.y + m_13 * t_vector.z, //row 1
					 m_21 * t_vector.x + m_22 * t_vector.y + m_23 * t_vector.z,  //row 2
					 m_31 * t_vector.x + m_32 * t_vector.y + m_33 * t_vector.z}; //row 3
}

//scaling a matrix by a passed in number
MyMatrix3 MyMatrix3::operator*(const double t_scale) const
{
	return MyMatrix3 {	m_11 * t_scale , m_12 * t_scale , m_13 * t_scale, //row 1
						m_21 * t_scale , m_22 * t_scale , m_23 * t_scale, //row 2
						m_31 * t_scale , m_32 * t_scale , m_33 * t_scale }; //row 3

}
//transpose of a matrix, swapping values to new location
MyMatrix3 MyMatrix3::transpose() const
{
	//assigning the positions of the matrix numbers to the transpose of them
	double t_11;
	double t_12;
	double t_13;
	double t_21;
	double t_22;
	double t_23;
	double t_31;
	double t_32;
	double t_33;

	//first row transpose
	t_11 = m_11;
	t_21 = m_12; 
	t_31 = m_13;
	//second row transpose
	t_22 = m_22;
	t_12 = m_21;
	t_32 = m_23;
	//third row transpose
	t_33 = m_33;
	t_13 = m_31;
	t_23 = m_32;

	MyMatrix3 newMatrix = { t_11, t_12, t_13, t_21,t_22, t_23, t_31, t_32, t_33 };

	return newMatrix;
}

// determinant of the matrix
double MyMatrix3::determinant() const
{
	double det = m_11*(m_22*m_33 - m_32*m_23) - m_21*(m_33*m_12 - m_32*m_13) + m_31*(m_23*m_12 - m_22*m_13);

	return det; 

}

//finds inverse of a matrix
MyMatrix3 MyMatrix3::inverse() const
{
	MyMatrix3 inverse;

	//finds determinant of the matrix first
	double detA = (m_11*(m_22*m_33 - m_32*m_23)) - (m_21*(m_33*m_12 - m_32*m_13)) + (m_31*(m_23*m_12 - m_22*m_13));
	
	//inner workings of the inverse
	MyMatrix3 innerworks = {(m_33*m_22 - m_32*m_23), (m_32*m_13 - m_33*m_12), (m_23*m_12 - m_22*m_13), 
	(m_31*m_23 - m_33*m_21), (m_33*m_11 - m_31*m_13), (m_21*m_13 - m_23*m_11),
	(m_32*m_21 - m_31*m_22), (m_31*m_12 - m_32*m_11), (m_22*m_11 - m_21*m_12)};

	if (detA != 0) //inverse of matrix only exists if determinant of the matrix is not zero
	{
		inverse = innerworks * (1 / detA);
	}
	else
		inverse = { 0,0,0,0,0,0,0,0,0}; //returns 0 to indicate inverse doesn't exist
	return inverse;
}

/// <summary>
/// returns the column the user wishes to see; row 1 = 0, row 2 = 1, row 3 = 2
/// </summary>
/// <param name="t_column">the row number wished to return(0, 1, 2)</param>
/// <returns>the passed in row numbers</returns>
MyVector3 MyMatrix3::row(const int t_row) const
{
	MyVector3 rowVec; //new 3d vector to store numbers and return those numbers

	if (t_row == 0)
	{
		rowVec = { m_11, m_12, m_13 };
	}
	else if (t_row == 1)
	{
		rowVec = { m_21, m_22, m_23 };
	}
	else if (t_row == 2)
	{
		rowVec = { m_31, m_32, m_33 };
	}

	return rowVec;
}

/// <summary>
/// returns the column the user wishes to see; column 1 = 0, column 2 = 1, column 3 = 2
/// </summary>
/// <param name="t_column">the column number wished to return(0, 1, 2)</param>
/// <returns>the passed in columns numbers</returns>
MyVector3 MyMatrix3::column(const int t_column) const
{
	MyVector3 colVec; //new 3d vector to store numbers and return those numbers

	if (t_column == 0)
	{
		colVec = { m_11, m_21, m_31 }; //assigned to the first column of numbers
	}
	else if (t_column == 1)
	{
		colVec = { m_12, m_22, m_32 }; // assigned to the second column of numbers
	}
	else if (t_column == 2)
	{
		colVec = { m_13, m_23, m_33 }; //assigned to the third column of numbers
	}

	return colVec;
}

/// <summary>
/// rotates matrix from the Z plane
/// </summary>
/// <param name="t_angleRadians">an angle is passed in radians to rotate matrix anti clockwise</param>
/// <returns>new matrix</returns>
MyMatrix3 MyMatrix3::rotationZ(const double t_angleRadians)
{
	double t_11 = cos(t_angleRadians);
	double t_12 = -(sin(t_angleRadians));
	double t_13 = 0;
	double t_21 = sin(t_angleRadians);
	double t_22 = cos(t_angleRadians);
	double t_23 = 0;
	double t_31 = 0;
	double t_32 = 0;
	double t_33 = 1;


	return MyMatrix3 { t_11, t_12, t_13, t_21,t_22, t_23, t_31, t_32, t_33 };
}

/// <summary>
/// rotates matrix from the Y plane
/// </summary>
/// <param name="t_angleRadians">an angle is passed in radians to rotate matrix anti clockwise</param>
/// <returns>a new rotated matrix</returns>
MyMatrix3 MyMatrix3::rotationY(const double t_angleRadians)
{
	double t_11 = cos(t_angleRadians);
	double t_12 = 0;
	double t_13 = sin(t_angleRadians);

	double t_21 = 0;
	double t_22 = 1;
	double t_23 = 0;

	double t_31 = -(sin(t_angleRadians));
	double t_32 = 0;
	double t_33 = cos(t_angleRadians);

	return MyMatrix3{ t_11, t_12, t_13, t_21,t_22, t_23, t_31, t_32, t_33 };
}

/// <summary>
/// rotates matrix from the x plane
/// </summary>
/// <param name="t_angleRadians">an angle is passed in radians to rotate matrix anti clockwise </param>
/// <returns>new rotated matrix</returns>
MyMatrix3 MyMatrix3::rotationX(const double t_angleRadians)
{
	//row 1
	double t_11 = 1; 
	double t_12 = 0; 
	double t_13 = 0;
	//row 2
	double t_21 = 0; 
	double t_22 = cos(t_angleRadians);
	double t_23 = -(sin(t_angleRadians));
	//row 3
	double t_31 = 0;
	double t_32 = sin(t_angleRadians);
	double t_33 = cos(t_angleRadians);

	return MyMatrix3{ t_11, t_12, t_13, t_21,t_22, t_23, t_31, t_32, t_33 };
}

/// <summary>
/// 
/// </summary>
/// <param name="t_displacement">a 3d vector is passed in</param>
/// <returns></returns>
MyMatrix3 MyMatrix3::translation(const MyVector3 t_displacement)
{
	//row 1
	double t_11 = 1;
	double t_12 = 0;
	double t_13 = t_displacement.x;
	//row 2
	double t_21 = 0;
	double t_22 = 1;
	double t_23 = t_displacement.y;
	//row 3
	double t_31 = 0;
	double t_32 = 0;
	double t_33 = t_displacement.z;

	return MyMatrix3{ t_11, t_12, t_13, t_21,t_22, t_23, t_31, t_32, t_33 };
}

/// <summary>
/// creates a new matrix with a scaling factor which is passed into the matrix
/// </summary>
/// <param name="t_scalingfactor">passing in a number to scale matrix by</param>
/// <returns>returns the new matrix</returns>
MyMatrix3 MyMatrix3::scale(const double t_scalingfactor)
{
	//row 1
	double t_11 = t_scalingfactor;
	double t_12 = 0;
	double t_13 = 0;
	//row 2
	double t_21 = 0;
	double t_22 = t_scalingfactor;
	double t_23 = 0;
	//row 3
	double t_31 = 0;
	double t_32 = 0;
	double t_33 = t_scalingfactor;

	return MyMatrix3{ t_11, t_12, t_13, t_21,t_22, t_23, t_31, t_32, t_33 };
}











