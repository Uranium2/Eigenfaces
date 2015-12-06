# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <err.h>

void wait_for_keypressed(void);

void init_sdl(void);

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);
