// RayTracingOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

// Consider moving in ray header file/ ray class
color ray_color(const ray& r, const hittable& world, int depth) {

	hit_record rec; 
	
	// If we've exceeded the ray bounce limit, no morelight is gathered. 
	// Prevents infinity recursion.
	if (depth <= 0)
		return color(0, 0, 0);

	// if an object in the scene is hit
	if (world.hit(r, 0.001, infinity, rec)) {

		ray scattered; 
		color attenuation; 

		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);

		return color(0, 0, 0);
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

	auto R = cos(pi / 4);
	hittable_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_centerFront = make_shared<dielectric>(1.5);
	auto material_left = make_shared<metal>(color(0.3, 0.4, 0.5), 0.01);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.8); 

	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
	world.add(make_shared<sphere>(point3(0, 0, -1.0), 0.45, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));
	world.add(make_shared<sphere>(point3(0, 0, -0.25), 0.2, material_centerFront));

	// Camera 
	point3 lookfrom(3, 3, 2);
	point3 lookat(0, 0, -1);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 2.0;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

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