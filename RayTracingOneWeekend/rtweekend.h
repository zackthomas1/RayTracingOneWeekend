#pragma once

#include <cmath>
#include <limits>
#include <limits> 
#include <memory>

#include "ray.h"
#include "vec3.h"

// Using 

using std::shared_ptr; 
using std::make_shared; 
using std::sqrt; 

// Constants 

const double infinity = std::numeric_limits<double>::infinity(); 
const double pi = 3.1415926535897932385; 

// Utility Functions 

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline bool DoubleEquality(double v01, double v02){
	const double EPSILON = 0.0001;
	if (abs(v01 - v02) < EPSILON)
		return true;
	else
		return false;
}