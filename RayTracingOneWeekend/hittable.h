#pragma once
#include "ray.h"

struct hit_record {
	point3 p; // consider renaming 'pos', 'position', or 'hitPosition'
	vec3 normal; 
	double t;
	bool front_face; 

	/// <summary>
	/// Determines if ray is inside or outside hittable object.
	/// Then sets normal in opposite direction of inRay
	/// </summary>
	/// <param name="ray"></param>
	/// <param name="outward_normal"></param>
	inline void set_face_normal(const ray& inRay, const vec3& outward_normal) {
		front_face = dot(inRay.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public: 
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};