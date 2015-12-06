# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "eigenfaces.h"
# include "grey_scale.h"
int main(){

	VectFace *vect, *TransVect;
	int *avgFace;

	init_sdl();

	vect = ImageVectors();
	avgFace = AverageFace(vect);
	vect = Normalize(vect,avgFace);	
	TransVect = Trans(vect);

	SDL_Surface *img = load_image("img.jpg");
	int count = 0;

	for(int i = 0; i < 24*24; i++){
		for(int j = 0; j < 25; j++){

			//printf(" |%d", vect[i].pixelVect[j]);
			printf(" |%d", TransVect[i].pixelVect[j]);
		}
	}

	for(int i = 0; i < 24; i++){

		//printf(" |%03d",vect[0].pixelVect[i]); 
		for(int j = 0; j < 24; j++){
			Uint8 val;
			val = vect[14].pixelVect[count];
			putpixel(img,i,j,val);
			count++;
		}
	}
	printf("| \n");
	//	grey_scale(img);
	//	display_image(img);
	//	wait_for_keypressed();
}
