#ifndef _SWR_UTILS_H_
#define _SWR_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
	typedef struct _swr_rect{
		int left;
		int top;
		int width;
		int height;
	}swr_rect;
	void swr_intersect_rect_rect(const swr_rect *r1, const swr_rect* r2, swr_rect* ir);
	int swr_is_pt_inside_rect(int x, int y, int left, int top, int right, int bottom);
#ifdef __cplusplus
}
#endif

#endif

