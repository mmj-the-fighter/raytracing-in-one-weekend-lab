#ifndef _SWR_RASTERIZER_H_
#define _SWR_RASTERIZER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "swr_sdl_context.h"
#include "swr_rfont.h"

/*
Rasterizer 2D coordinate system:
Origin: at top-left coorner of the screen
X: increases from left to right
Y: increases from top to bottom
*/

/* set the context (struct for screen surface pixels, width, height etc) */
void rasterizer_set_swr_sdl_context(swr_sdl_context* ptr_to_swr_sdl_context);

/* set current drawing color */
void rasterizer_set_cur_color(int r, int g, int b, int a);

/* set current clear color */
void rasterizer_set_clear_color(int r, int g, int b, int a);

/* enable or disable alpha blending */
void enable_alpha_blending(int flag);

/* put pixel */
void rasterizer_put_pixel(int x, int y);
void rasterizer_put_pixel2(int x, int y, swr_color *pc);

/* draw line */
void rasterizer_draw_line_dda(int x0, int y0, int x1, int y1);

/* draw rectangle */
void rasterizer_draw_rect(int left, int top, int right, int bottom);

/* fill rectangle */
void rasterizer_fill_rect(int x0, int y0, int x1, int y1);

/* copy pixels to screen */
void rasterizer_copy_pixels(int dst_x_start, 
	int dst_y_start, 
	int src_width, 
	int src_height, 
	unsigned char* src_pixels);

/* copy pixels to screen with chroma keying*/
void rasterizer_copy_pixels_chromakey(int dst_x_start,
	int dst_y_start,
	int src_width,
	int src_height,
	swr_color *chroma_key,
	unsigned char* src_pixels);

/* copy pixels to screen from a part of the src image*/
void rasterizer_copy_pixels_subimage(
	int dst_x_start,
	int dst_y_start,
	int src_x_start,
	int src_y_start,
	int src_width,
	int src_height,
	int src_total_width,
	int src_total_height,
	unsigned char* src_pixels);


/* copy pixels to screen from part of an image with chroma keying */
void rasterizer_copy_pixels_subimage_chromakey(
	int dst_x_start,
	int dst_y_start,
	int src_x_start,
	int src_y_start,
	int src_width,
	int src_height,
	int src_total_width,
	int src_total_height,
	swr_color *chroma_key,
	unsigned char* src_pixels);

/* copy pixels with color replace to screen from part of an image with chroma keying */
void rasterizer_copy_pixels_color_replace_subimage_chromakey(
	int dst_x_start,
	int dst_y_start,
	int src_x_start,
	int src_y_start,
	int src_width,
	int src_height,
	int src_total_width,
	int src_total_height,
	swr_color *chroma_key,
	swr_color *newcolor,
	unsigned char* src_pixels);


/* ouput text */
void rasterizer_draw_text(int x, int y, const char* text);

/* output text with color */
void rasterizer_draw_text_with_color(swr_rfont *f, swr_color *color, int x, int y, const char* text);

/* clear screen */
void rasterizer_clear();





#ifdef __cplusplus
}
#endif

#endif

