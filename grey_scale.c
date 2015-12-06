# include <stdlib.h>
# include <stdio.h>
# include <SDL.h>
# include <SDL_image.h>
# include "pixel_operations.h"

void grey_scale(SDL_Surface *img)
{
	for(int i = 0 ; i < img->w; i++)
	{
		for(int j = 0 ; j < img->h; j++)
		{
			Uint8 r,g,b;
			SDL_GetRGB(getpixel(img,i,j), img->format, &r, &g, &b);
			float luminance = (0.3 * r) + (0.59 * g) + (0.11 * b);
			r = g = b = luminance;
			putpixel(img,i,j, SDL_MapRGB(img->format, r, g, b));
		}
	}
}
