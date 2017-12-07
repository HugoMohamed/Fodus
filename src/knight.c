#ifndef KNIGHT_C
#define KNIGHT_C

#include "knight.h"

void knight_attaqueA(map m, int x, int y)
{
	int i;
	i = 1;
	while(i <= 3 && m[y][x+i] != '1')
	{
		if(m[y][x+i] == '0')
		{
			m[y][x+i] = '2';
			MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y][x+i] == '3')
		{
			m[y][x+i] = '4';
		}
		i++;
	}
	i = 1;
	while( i <= 3 && m[y+i][x] != '1')
	{
		if(m[y+i][x] == '0')
		{
			m[y+i][x] ='2';
			MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y+i][x] == '3')
		{
			m[y+i][x] = '4';
		}
		i++;
	}
	i = -1;
	while(i >= -3 && m[y][x+i] != '1')
	{
		if(m[y][x+i] == '0')
		{
			m[y][x+i] = '2';
			MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y][x+i] == '3')
		{
			m[y][x+i] = '4';
		}
		i--;
	}
	i = -1;
	while(i >= -3 && m[y+i][x] != '1')
	{
		if(m[y+i][x] == '0')
		{
			m[y+i][x] = '2';
			MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y+i][x] == '3')
		{
			m[y+i][x] = '4';
		}
		i--;
	}
}

#endif
