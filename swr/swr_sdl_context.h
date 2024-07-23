#ifndef _SWR_SDL_CONTEXT_H_
#define _SWR_SDL_CONTEXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL.h>
#undef main
#include <SDL_render.h>
#include "swr_pixel.h"
#include "swr_rfont.h"

typedef struct _swr_sdl_context
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *screen_texture;
	int screen_texture_pitch;
	int screen_texture_pixels_wide;
	int screen_texture_pixels_high;
	int screen_texture_channels;
	int transparent_alpha_value;
	int opaque_alpha_value;
	swr_color cur_color;
	swr_color clear_color;
	swr_rfont* font;
	unsigned char *screen_texture_pixels; /* frame buffer */
	float *depth_buffer;
	size_t screen_textue_pixels_size_in_bytes;
	void(*display_handler) (struct _swr_sdl_context *);
	int (*input_handler) (SDL_Event *);
	float lastFrameTime;
	float extra;
}swr_sdl_context;

#ifdef __cplusplus
}
#endif

#endif

