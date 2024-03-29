## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= svd.c grey_scale.c sdl_stuff.c pixel_operations.c main.c eigenfaces.c
OBJ= ${SRC:.c=.o}
 
all: main
 
main: ${OBJ}
 
clean:
	rm -f *~ *.o .*.swp
	rm -f main
 

