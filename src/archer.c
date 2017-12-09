#ifndef ARCHER_C
#define KNIGHT_C

#include "archer.h"

void archer_attaqueA(map m, int x, int y)
{
	int i = 6,j;
	for(j=0;j<=i;j++)
	{
		if(m[y-j][x+i-j] == '0')
		{
			m[y-j][x+i-j] = '2';
			MLV_draw_filled_rectangle((x+i-j)*40,(y-j)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y-j][x+i-j] == '3')
		{
			m[y-j][x+i-j] = '4';
		}
		if(m[y-j][x-i+j] == '0')
		{
			m[y-j][x-i+j] = '2';
			MLV_draw_filled_rectangle((x-i+j)*40,(y-j)*40,40,40,MLV_rgba(0,255,0,100));

		}
		if(m[y-j][x-i+j] == '3')
		{
			m[y-j][x-i+j] = '4';
		}

		if(m[y+j][x+i-j] == '0')
		{
			m[y+j][x+i-j] = '2';
			MLV_draw_filled_rectangle((x+i-j)*40,(y+j)*40,40,40,MLV_rgba(0,255,0,100));
		}

		if(m[y+j][x+i-j] == '3')
		{
			m[y+j][x+i-j] = '4';
		}

		if(m[y+j][x-i+j] == '0')
		{
			m[y+j][x-i+j] = '2';
			MLV_draw_filled_rectangle((x-i+j)*40,(y+j)*40,40,40,MLV_rgba(0,255,0,100));
		}

		if(m[y+j][x-i+j] == '3')
		{
			m[y+j][x-i+j] = '4';
		}
	}
}

#endif
