#pragma once
#include <cmath> 
#include <iostream> 
using std::sqrt; 

class vec3
{
public: 
	// Constructors
	vec3() : e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {} 

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[] (int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }
	
	vec3& operator += (const vec3 &inVec) {
		e[0] += inVec.e[0];
		e[1] += inVec.e[1];
		e[2] += inVec.e[2];
		return *this;
	}

	vec3& operator -= (const vec3& inVec) {
		e[0] -= inVec.e[0];
		e[1] -= inVec.e[1];
		e[2] -= inVec.e[2];
		return *this;
	}

	vec3& operator *= (const double scalar) {
		e[0] *= scalar;
		e[1] *= scalar;
		e[2] *= scalar;
		return *this;
	}

	vec3& operator /= (const double scalar) {
		return *this *= 1 / scalar;
	}

	bool operator ==(const vec3& inVec) const
	{
		if (e[0] == inVec.e[0] &&
			e[1] == inVec.e[1] &&
			e[2] == inVec.e[2])
			return true;
		else
			return false;
	}

	bool operator !=(const vec3& inVec) const
	{
		if (*this == inVec)
			return false;
		else
			return true;
	}

	/// <summary>
	/// Length of a vector.
	/// aka. magnitude  
	/// </summary>
	/// <returns></returns>
	double length() const {
		return sqrt(length_squared()); // Is this really the best way to get the length of vector instance?
	}

	/// <summary>
	/// Length of a vector squared
	/// </summary>
	/// <returns></returns>
	double length_squared() const {
		return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
	}

// Consider putting above previous public section
// Also, give variable 'e' a more descriptive name
// Or even consider not have it as an array, just be three double variables x,y,z
public: 
	double e[3]; // declares instance variable which contains vector coordinates
};

// Type aliases for vec3 
using point3 = vec3;	// 3D point 
using color = vec3;		// RGB color


// vec 3 Utility Functions 
//------------------------------------------------------------------------

inline std::ostream& operator << (std::ostream& out, const vec3& inVec) {
	return out << inVec.e[0] << ' ' << inVec.e[1] << ' ' << inVec.e[2];
}

inline vec3 operator +(const vec3& inVec01, const vec3& inVec02) {
	return vec3(inVec01[0] + inVec02[0], inVec01[1] + inVec02[1], inVec01[2] + inVec02[2]);
}

inline vec3 operator -(const vec3& inVec01, const vec3& inVec02){
	return vec3(inVec01[0] - inVec02[0], inVec01[1] - inVec02[1], inVec01[2] - inVec02[2]);
}

inline vec3 operator *(const vec3& inVec01, const vec3& inVec02) {
	return vec3(inVec01[0] * inVec02[0], inVec01[1] * inVec02[1], inVec01[2] * inVec02[2]);
}

inline vec3 operator *(double scalar, const vec3& inVec) {
	return vec3(scalar * inVec[0], scalar * inVec[1], scalar * inVec[2]);
}

inline vec3 operator *(const vec3& inVec, double scalar) {
	return scalar * inVec;
}

inline vec3 operator /(const vec3& inVec, double scalar) {
	return (1 / scalar) * inVec;
}

// consider moving dot, cross, unit_vector methods into vec3 class
// and making dot and cross methods static
/// <summary>
/// Calculate dot product. 
/// Smaller value larger the angle between vectors
/// </summary>
/// <param name="inVec01"></param>
/// <param name="inVec02"></param>
/// <returns></returns>
inline double dot(const vec3& inVec01, const vec3& inVec02 ) {
	return inVec01.e[0] * inVec02.e[0]
		 + inVec01.e[1] * inVec02.e[1]
		 + inVec01.e[2] * inVec02.e[2];
}

/// <summary>
/// Calculate cross product.
/// Returns vector that is perpendicular to two input vectors
/// </summary>
/// <param name="inVec01"></param>
/// <param name="inVec02"></param>
/// <returns></returns>
inline vec3 cross(const vec3& inVec01, const vec3& inVec02) {
	return vec3(inVec01.e[1] * inVec02.e[2] - inVec01.e[2] * inVec02.e[1],
				inVec01.e[2] * inVec02.e[0] - inVec01.e[0] * inVec02.e[2],
				inVec01.e[0] * inVec02.e[1] - inVec01.e[1] * inVec02.e[0]);
}

/// <summary>
/// Converts vector to unit vector.
/// Meaning vector magnitude is equal to 1.
/// </summary>
/// <param name="inVec"></param>
/// <returns></returns>
inline vec3 unit_vector(vec3 inVec) {
	return inVec / inVec.length();
}
