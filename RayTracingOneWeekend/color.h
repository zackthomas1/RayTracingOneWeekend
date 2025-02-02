#pragma once
#include <iostream>
#include "vec3.h"

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	// Write the translated [0,255] value of each color component. 
	/*out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';*/

	auto r = pixel_color.x(); 
	auto g = pixel_color.y(); 
	auto b = pixel_color.z(); 

	// Divide the color hy the number of smaples. 
	auto scale = 1.0 / (samples_per_pixel); 
	r = sqrt(scale * r); 
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	// Write the translated [0,255] value of each color component 
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}