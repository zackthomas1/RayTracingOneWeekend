#pragma once
#include "rtweekend.h"

class camera {

public: 

	camera() : camera(point3(0, 0, -1), point3(0, 0, 0), vec3(0, 1, 0), 40, 1, 0, 10) {}

	camera(
		point3 lookfrom = point3(0, 0, -1),
		point3 lookat = point3(0, 0, 0),
		vec3 vup = vec3(0, 1, 0),
		double vfov = 40.0, // vertical field-of-view in degrees
		double aspect_ratio = 1,
		double aperture = 0.0,
		double focus_dist = 10 
	) {
		auto theta = degrees_to_radians(vfov); 
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h; 
		auto viewport_width = aspect_ratio * viewport_height;
		
		//
		w = unit_vector(lookfrom - lookat); 
		u = unit_vector(cross(vup, w));
		v = cross(w, u); 

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

		lens_radius = aperture / 2;
	}

	ray get_ray(double s, double t) const {
		
		//
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();

		return ray(origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}

private: 
	point3 origin; 
	point3 lower_left_corner; 
	vec3 horizontal; 
	vec3 vertical;
	vec3 u, v, w; 
	double lens_radius;
};