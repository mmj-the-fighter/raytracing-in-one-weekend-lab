#include <chrono>

#include "RayTracer.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius*radius;
	auto discriminant = b*b - 4 * a*c;
	return (discriminant >= 0);
}

color ray_color(const ray& r) {
	//This double for loop is for testing with large delays
	//for (int i = 0; i < 100; i++)
	//{
	//	for (int i = 0; i < 100; i++){
	//		;
	//	}
	//}
	//////////////////////
	if (hit_sphere(point3(0, 0, -1), 0.5, r))
		return color(1, 0, 0);

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

void RayTracer::Render()
{
	is_rendering_completed = false;
	percent_remaining = 100.0;
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < image_height; ++j) {
		percent_remaining = static_cast<double>((image_height - j) * 100) / static_cast<double>(image_height);
		std::cout << percent_remaining << "% remaining \n";
		for (int i = 0; i < image_width; ++i) {
			vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			vec3 ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);
			color pixel_color = ray_color(r);
			WriteColor(pixel_color, i, j);
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	time_taken_for_rendering = elapsed_time;
	is_rendering_completed = true;
	percent_remaining = 0.0;
	std::cout << percent_remaining << "% remaining \n";
	std::cout << "Elapsed time: " << time_taken_for_rendering/1000 << " seconds" << std::endl;
}
