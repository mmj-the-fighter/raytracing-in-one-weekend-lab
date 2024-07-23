#ifndef _RAY_TRACER_H_
#define _RAY_TRACER_H_

#include <iostream>


#include "../InOneWeekend/rtweekend.h"
#include "../InOneWeekend/ray.h"
#include "../InOneWeekend/color.h"
#include "../InOneWeekend/vec3.h"


class RayTracer
{
private:
	double aspect_ratio;
	int image_width;
	int image_height;
	double focal_length;
	double viewport_height;
	double viewport_width;
	vec3 camera_center;

	//vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u;
	vec3 viewport_v;

	//horizontal and vertical delta vectors from pixel to pixel.
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;

	//location of the upper left pixel.
	vec3 viewport_upper_left;
	vec3 pixel00_loc;

	//
	unsigned char* pixels;
	double percent_remaining;
	bool is_rendering_completed;
	long long time_taken_for_rendering;

private:
	inline void AllocatePixels(int width, int height) {
		//pixels = (unsigned char *)malloc(width * height * 4 * sizeof(unsigned char));
		pixels = new unsigned char[width * height * 4];
	}

	inline void DeAllocatePixels() {
		if (pixels != nullptr){
			delete[] pixels;
			pixels = nullptr;
		}
	}

	inline void WriteColor(const color& c, int x, int y){
		unsigned char* loc = pixels + image_width * 4 * y + 4 * x;
		*loc++ = 255.0 * c.e[2];
		*loc++ = 255.0 * c.e[1];
		*loc++ = 255.0 * c.e[0];
		*loc = 255;
	}

	inline void ClearPixels(){
		memset(pixels, 0, image_width * image_height * sizeof(unsigned char) * 4);
	}

	color RayColor(const ray& r);

	inline void Init(double aspectRatio, int imageWidth, double focalLength, double viewPortHeight, vec3 cameraCenter)
	{
		aspect_ratio = aspectRatio;
		image_width = imageWidth;

		// Calculate the image height, and ensure that it's at least 1.
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		// Camera
		focal_length = 1.0;
		viewport_height = 2.0;
		viewport_width = viewport_height * (double(image_width) / image_height);
		camera_center = cameraCenter;

		// Calculate the vectors across the horizontal and down the vertical viewport edges.
		viewport_u = vec3(viewport_width, 0, 0);
		viewport_v = vec3(0, -viewport_height, 0);

		// Calculate the horizontal and vertical delta vectors from pixel to pixel.
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate the location of the upper left pixel.
		viewport_upper_left = camera_center
			- vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
		//extra
		AllocatePixels(imageWidth, image_height);
		ClearPixels();
		is_rendering_completed = false;
		percent_remaining = 100.0;
		time_taken_for_rendering = 0;
	}

	

public:
	RayTracer(double aspectRatio, int imageWidth, double focalLength, double viewPortHeight, vec3 cameraCenter){
		Init(aspectRatio, imageWidth, focalLength, viewPortHeight, cameraCenter);
	}
	~RayTracer(){ 
		DeAllocatePixels(); 
	}
	inline bool IsRenderingCompleted(){ return is_rendering_completed; }
	inline int GetImageWidth(){ return image_width; }
	inline int GetImageHeight(){ return image_height; }
	inline unsigned char* GetPixels() { return pixels; }
	inline long long GetTimeTaken() { return time_taken_for_rendering; }

	void Render();
};


bool hit_sphere(const point3& center, double radius, const ray& r);
color ray_color(const ray& r);
#endif

