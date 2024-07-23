#include <math.h>
#include <time.h>
#include <string.h>
#include "swr_pixel.h"
#include "swr_sdl_window.h"

static swr_sdl_context context;
static int running = 1;
static Uint32 targetMSPF = (Uint32)(1000.0 / 62.0);


int swr_sdl_create_context(
	int resolution_x, 
	int resolution_y,
	const char* font_image_filename, 
	const char* font_properties_csv_filename)
{
	char wt[128];
	time_t tm;
	context.font = create_font(font_image_filename, font_properties_csv_filename);
	/* init context */
	context.screen_texture_pixels = NULL;
	context.depth_buffer = NULL;
	context.renderer = NULL;
	context.window = NULL;
	context.screen_texture_channels = 4;
	context.transparent_alpha_value = SDL_ALPHA_TRANSPARENT;
	context.opaque_alpha_value = SDL_ALPHA_OPAQUE;
	context.lastFrameTime = 0.0f;

	
	/* init SDL */
	SDL_Init(SDL_INIT_EVERYTHING);
	atexit(swr_sdl_destroy_context);

	/* create window with title: current date and time */
	strcpy(wt, "Experiment_");
	tm = time(NULL);
	strcat(wt, ctime(&tm));
	context.window = SDL_CreateWindow(
		wt,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		resolution_x, resolution_y,
		SDL_WINDOW_SHOWN);
	if (context.window == NULL) {
		return 1;
	}


	/* create renderer */
	context.renderer = SDL_CreateRenderer(context.window, 
		-1, 
		SDL_RENDERER_ACCELERATED);
	if (context.renderer == NULL) {
		return 2;
	}

	/* create screen texture */
	context.screen_texture = SDL_CreateTexture(
		context.renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		resolution_x, resolution_y);
	if (context.screen_texture == NULL) {
		return 3;
	}

	/* create screen pixel buffer with four components */
	context.screen_texture_pitch = resolution_x * context.screen_texture_channels;
	context.screen_textue_pixels_size_in_bytes = context.screen_texture_pitch * resolution_y;
	context.screen_texture_pixels = (unsigned char*)malloc(context.screen_textue_pixels_size_in_bytes);
	context.screen_texture_pixels_wide = resolution_x;
	context.screen_texture_pixels_high = resolution_y;	

	
	/* Uncomment this if you want the application in full screen mode */
	/* SDL_SetWindowFullscreen(context.window, SDL_WINDOW_FULLSCREEN); */

	return 0;
}

swr_sdl_context * swr_sdl_get_context(void)
{
	return &context;
}

void swr_sdl_set_display_handler(void(*fptr_display_fn)(struct _swr_sdl_context *))
{
	context.display_handler = fptr_display_fn;
}

void swr_sdl_set_input_handler(int(*fptr_key_fn)(SDL_Event *))
{
	context.input_handler = fptr_key_fn;
}

void swr_sdl_set_frames_per_second(int fps)
{
	targetMSPF = (Uint32)(1000.0 / fps);
}

void swr_sdl_render_screen_texture()
{
	/* update texture with screen pixels and render*/
	SDL_UpdateTexture(context.screen_texture, NULL, context.screen_texture_pixels, context.screen_texture_pitch);
	SDL_RenderCopy(context.renderer, context.screen_texture, NULL, NULL);
	SDL_RenderPresent(context.renderer);
}

void swr_sdl_wait_for_events()
{
	SDL_Event event;
	int loop = 1;
	while (loop)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN || 
			event.type == SDL_QUIT || 
			event.type == SDL_MOUSEBUTTONDOWN)
			loop = 0;
		
	}
}

void swr_sdl_main_loop(void)
{
	SDL_Event event;
	Uint32 frame_start_time, elapsed_time = 0, wait_delay = 0;

	while (running)
	{
		frame_start_time = SDL_GetTicks();

		/* process Input*/
		while ( SDL_PollEvent(&event) )
		{
			if (event.type == SDL_QUIT)
			{
				return;
			}
			else if ((context.input_handler != NULL) && (*context.input_handler)(&event))
			{
				return;
			}
		}

		

		/* accept changes to screen pixels from user*/
		if (context.display_handler != NULL)
			(*context.display_handler)(&context);

		/* update texture with screen pixels and render*/
		/*
		swr_sdl_render_screen_texture();
		*/
		SDL_UpdateTexture(context.screen_texture, NULL, context.screen_texture_pixels, context.screen_texture_pitch);
		SDL_RenderCopy(context.renderer, context.screen_texture, NULL, NULL);
		SDL_RenderPresent(context.renderer);

		/* sleep till next frame time */
		elapsed_time = (SDL_GetTicks() - frame_start_time);
		if (elapsed_time < targetMSPF) {
			wait_delay = targetMSPF - elapsed_time;
			SDL_Delay(wait_delay);
		}
		else{
			wait_delay = 0;
		
		}
		context.lastFrameTime = (float)(elapsed_time + wait_delay);
		context.extra = (float)(elapsed_time);
	}
}

void swr_sdl_terminate_main_loop(void)
{
	running = 0;
}

void swr_sdl_destroy_context(void)
{
	if (context.screen_texture_pixels != NULL) {
		free(context.screen_texture_pixels);
		context.screen_texture_pixels = NULL;
	}

	if (context.depth_buffer != NULL) {
		free(context.depth_buffer);
		context.depth_buffer = NULL;
	}

	if (context.renderer != NULL) {
		SDL_DestroyRenderer(context.renderer);
		context.renderer = NULL;
	}
		
	if (context.window != NULL) {
		SDL_DestroyWindow(context.window);
		context.window = NULL;
	}

	if (context.font != NULL) {
		destroy_font(context.font);
		context.font = NULL;
	}

	
	SDL_Quit();
}
