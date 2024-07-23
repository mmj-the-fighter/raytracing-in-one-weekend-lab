#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "swr_utils.h"

void swr_intersect_rect_rect(const swr_rect *r1, const swr_rect* r2, swr_rect* ir)
{
	/*compute intersection*/
	//1st rectangle
	int p1x = r1->left;
	int p1y = r1->top;
	int p2x = p1x + r1->width;
	int p2y = p1y + r1->height;

	//second rectangle
	int p3x = r2->left;
	int p3y = r2->top;
	int p4x = p3x + r2->width;
	int p4y = p3y + r2->height;

	//intersected rectangle
	int p5x = MAX(p1x, p3x);
	int p5y = MAX(p1y, p3y);
	int p6x = MIN(p2x, p4x);
	int p6y = MIN(p2y, p4y);
	
	ir->left = p5x;
	ir->top = p5y;
	ir->width = abs(p5x - p6x);
	ir->height = abs(p5y - p6y);
}

int swr_is_pt_inside_rect(int x, int y, int left, int top, int right, int bottom)
{
	if (x >= left && x <= right && y >= top && y <= bottom){
		return 1;
	}
	else{
		return 0;
	}
}