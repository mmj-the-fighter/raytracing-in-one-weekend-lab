#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "swr_screenshot.h"
#include "swr_image.h"

void swr_save_screenshot(swr_sdl_context* ctx)
{
	unsigned char rgb[3];
	unsigned char *loc;
	char fn[128];
	FILE *fp;
	int i, num_of_pixels;

	/* Make file name from time stamp and open file */
	time_t tm;
	tm = time(NULL);
	strftime(fn, sizeof(fn), "SCRN_%Y_%m_%d_%H_%M_%S.ppm", localtime(&tm));
	fp = fopen(fn, "wb");
	if (fp == NULL)
		return;

	/* Write ppm header */
	fprintf(fp, "P6\n%d %d\n255\n", 
		ctx->screen_texture_pixels_wide, 
		ctx->screen_texture_pixels_high);

	/* Dump r,g,b values */
	loc = ctx->screen_texture_pixels;
	num_of_pixels = ctx->screen_texture_pixels_wide *
		ctx->screen_texture_pixels_high;
	for (i = 0; i < num_of_pixels; ++i)
	{
		rgb[2] = *loc++;
		rgb[1] = *loc++;
		rgb[0] = *loc++;
		loc++;
		fwrite(rgb, sizeof(unsigned char), sizeof(rgb), fp);
	}
	fclose(fp);
}
