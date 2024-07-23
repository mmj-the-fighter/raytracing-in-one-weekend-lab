#ifndef _SWR_PIXEL_H_
#define _SWR_PIXEL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _swr_color
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
}swr_color;

swr_color make_swr_color(unsigned char b, unsigned char g, unsigned char r, unsigned char a);
void set_swr_color(swr_color* psc, unsigned char b, unsigned char g, unsigned char r, unsigned char a);

#ifdef __cplusplus
}
#endif

#endif

