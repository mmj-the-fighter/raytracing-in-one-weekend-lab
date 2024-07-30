#include <iostream>
#include <thread>
#include "../swr/swr_sdl_window.h"
#include "../swr/swr_rasterizer.h"
#include "../swr/swr_image.h"
#include "../swr/swr_rfont.h"
#include "../swr/swr_utils.h"
#include "../swr/swr_screenshot.h"
#include "../rt/RayTracer.h"

swr_sdl_context* g_ctx = NULL;
int is_alert_invoked = 0;
int padding = 2;
RayTracer rt(16.0 / 9.0, 800, 1.0, 2.0, point3(0, 0, 0));

/*
todo:
integrate alert with the framework
*/

void process_input_for_alert(int x, int y){
	if (is_alert_invoked && 
		swr_is_pt_inside_rect(x, y, 10 - padding / 2, 40 - padding / 2, 45 + padding / 2, 60 + padding / 2) == 1) {
		write_ppm_raw(NULL, rt.GetPixels(), rt.GetImageWidth(), rt.GetImageHeight());
		write_png_using_stb(NULL, rt.GetPixels(), rt.GetImageWidth(), rt.GetImageHeight());
		is_alert_invoked = 0;
	}
	else if (is_alert_invoked && 
		swr_is_pt_inside_rect(x, y, 50 - padding / 2, 40 - padding / 2, 80 + padding / 2, 60 + padding / 2) == 1) {
			is_alert_invoked = 0;
	}
}

void display_save_file_alert(swr_sdl_context* ctx)
{
	int tw, th;
	rasterizer_set_cur_color(0, 0, 128, g_ctx->opaque_alpha_value);
	rasterizer_fill_rect(0, 0, 220, 70);
	rasterizer_set_cur_color(255, 255, 255, g_ctx->opaque_alpha_value);
	//rasterizer_clear();
	char buffer[256];
	sprintf(buffer, "Do you want to save this?");
	rasterizer_draw_text(10, 10, buffer);

	//get_text_width_height(g_ctx->font, "Do you want to save this?", &tw, &th);
	//rasterizer_draw_rect(10, 10, 10+tw, 10+th);

	sprintf(buffer, "Yes");
	rasterizer_draw_text(10, 40, buffer);
	rasterizer_draw_rect(10 - padding / 2, 40 - padding / 2, 45 + padding / 2, 60 + padding / 2);

	sprintf(buffer, "No");
	rasterizer_draw_text(50, 40, buffer);
	rasterizer_draw_rect(50 - padding / 2, 40 - padding / 2, 80 + padding/2, 60 + padding/2);
}

void display(swr_sdl_context* ctx)
{
	if (nullptr != rt.GetPixels()){
		rasterizer_copy_pixels(0, 0, rt.GetImageWidth(), rt.GetImageHeight(), rt.GetPixels());
	}
	if (is_alert_invoked){
		display_save_file_alert(ctx);
	}
}

int input(SDL_Event* e)
{
	static int flag = 0;
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return 1;
		case SDL_SCANCODE_SPACE:
			is_alert_invoked = is_alert_invoked ? 0 : 1;
			break;
		}
	}
	else {
		if (e->type == SDL_MOUSEBUTTONUP && e->button.button == 1) {
			//printf("%d %d %d down\n", e->button.button, e->button.x, e->button.y);
			process_input_for_alert(e->button.x, e->button.y);
		}
	}
	return 0;
}

void init(int width, int height) {
	swr_sdl_create_context(width, height, "swrres/fonts/glyphs.ppm", "swrres/fonts/glyphs.csv");
	swr_sdl_set_input_handler(input);
	swr_sdl_set_display_handler(display);
	g_ctx = swr_sdl_get_context();
	rasterizer_set_swr_sdl_context(g_ctx);
	rasterizer_set_cur_color(255, 255, 255, g_ctx->opaque_alpha_value);
	rasterizer_set_clear_color(0, 0, 128, g_ctx->transparent_alpha_value);
}

void render_thread(){
	rt.Render();
	is_alert_invoked = 1;
	std::cout << "Rendering completed";
}

void invoke_render_thread(){
	std::thread t{ render_thread };
	t.detach();
}

int main() {
	init(rt.GetImageWidth(), rt.GetImageHeight());
	invoke_render_thread();
	swr_sdl_main_loop();
}

