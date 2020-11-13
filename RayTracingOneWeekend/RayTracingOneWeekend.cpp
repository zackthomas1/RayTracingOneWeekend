// RayTracingOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

// Consider moving in ray header file/ ray class
color ray_color(const ray& r, const hittable& world, int depth) {

	hit_record rec; 
	
	// If we've exceeded the ray bounce limit, no morelight is gathered. 
	// Prevents infinity recursion.
	if (depth <= 0)
		return color(0, 0, 0);

	// if an object in the scene is hit
	if (world.hit(r, 0.001, infinity, rec)) {

		// Diffuse scatter methods. Change for different diffuse methods. PICK ONE ONLY!!!!
		//point3 target = rec.p + rec.normal + random_in_unit_sphere(); 
		point3 target = rec.p + rec.normal + random_unit_vector(); 
		//point3 target = rec.p + random_in_hemisphere(rec.normal); 

		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1); // absorbs half the energy on each bounce
	}

	// if NO object is hit render default sky background
	vec3 unit_direction = unit_vector(r.direction()); 
	auto t = 0.5 * (unit_direction.y() + 1.0); 
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // linear interpolation
	// blendValue = (1 -t) * startValue + t * endValue
}

int main()
{
	//	Image 
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1920; 
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;  // Sets anti-alaising samples
	const int max_depth = 50;	// sets recussive limt for ray_color function


	// World 
	hittable_list world; 
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5)); 
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera 
	camera cam;

	//	Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; 

	for (int j = image_height - 1; j >= 0; j--) // row
	{
		std::cerr << "\rScalinesRemaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)	// column
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++) { // anti-aliasing subpixel rays 
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v); 
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
	return 0;
}