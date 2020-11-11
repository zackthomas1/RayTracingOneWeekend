#pragma once
#include "vec3.h"

class ray {
public:
	// Constructors
	ray() {
		orig = point3(0, 0, 0); 
		dir = vec3(1, 0, 0);
	}
	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

	point3 origin() const { return orig; }
	vec3 direction() const {return dir; }

	/// <summary>
	/// Returns a 3d point cooridinate of a ray given a time value (t)
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	point3 at(double t) const {
		return orig + t * dir;
	}

// Consider making instance variables private 
// since origin() and direction() methods return variables
public:
	point3 orig; 
	vec3 dir;
};