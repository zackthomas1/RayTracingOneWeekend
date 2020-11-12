#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public: 
	sphere() { center = point3(0, 0, 0); radius = 1.0; }
	sphere(point3 cen, double r) : center(cen), radius(r) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override; 


// Consider making attributes private
// and moving above constructor
public:
	point3 center; 
	double radius;

};

bool::sphere::hit(const ray& inRay, double t_min, double t_max, hit_record& hitRecord) const
{
	vec3 oc = inRay.origin() - center;
	auto a = inRay.direction().length_squared();
	auto half_b = dot(oc, inRay.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) 
		return false;

	auto sqrtDiscriminant = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtDiscriminant) / a; 
	if (root < t_min || root > t_max) {
		root = (-half_b + sqrtDiscriminant) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	// return hit information through out paramenter hitRecord
	hitRecord.t = root;	// t-value at hit position
	hitRecord.p = inRay.at(hitRecord.t); // Hit position as type point3
	vec3 outward_normal = (hitRecord.p - center) / radius ; // normal pointing to out from sphere center in direction of ray
	hitRecord.set_face_normal(inRay, outward_normal); // sets normal in opposite directon of incoming ray

	return true;
}