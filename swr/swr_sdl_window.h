#ifndef _SWR_WINDOW_H_
#define _SWR_WINDOW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "swr_sdl_context.h"


/* create context */
int swr_sdl_create_context(
		int resolution_x,
		int resolution_y,
		const char* fontimagefilename,
		const char* fontpropertiescsvfilename);

/* option to lock frame rate */
void swr_sdl_set_frames_per_second(int fps);

/* get context */
swr_sdl_context * swr_sdl_get_context(void);

/* set display function pointer */
void swr_sdl_set_display_handler(void(*fptr_display_fn)(struct _swr_sdl_context *));

/* set input function pointer */
void swr_sdl_set_input_handler(int(*fptr_input_fn)(SDL_Event *));

/* render pixels */
void swr_sdl_render_screen_texture();

/* wait till user makes an event*/
void swr_sdl_wait_for_events();

/* main loop: will call display function at 60 frames per second */
void swr_sdl_main_loop(void);

/* terminate main loop */
void swr_sdl_terminate_main_loop(void);

/* destroy context */
void swr_sdl_destroy_context(void);

#ifdef __cplusplus
}
#endif

#endif

