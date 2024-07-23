#include "swr_pixel.h"

swr_color make_swr_color(unsigned char b, unsigned char g, unsigned char r, unsigned char a)
{
	swr_color color;
	color.b = b;
	color.g = g;
	color.r = r;
	color.a = a;
	return color;
}

void set_swr_color(swr_color* psc, unsigned char b, unsigned char g, unsigned char r, unsigned char a)
{
	psc->b = b;
	psc->g = g;
	psc->r = r;
	psc->a = a;
}
