# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "eigenfaces.h"
# include "grey_scale.h"
# include "svd.h"

int main(){

	VectFace *vect, *TransVect, *Cova;
	int *avgFace;
	float **CovaNew = malloc(25*sizeof(float));
	float **EigenVect = malloc(25*sizeof(float));
//	float *w = malloc(25*sizeof(float));

	init_sdl();

	vect = ImageVectors();
	avgFace = AverageFace(vect);
	vect = Normalize(vect,avgFace);	
	TransVect = Trans(vect);
	Cova = Covariance(vect, TransVect);

	for(int i = 0; i < 25; i++){
		CovaNew[i] = malloc(25*sizeof(float));
		EigenVect[i] = malloc(25*sizeof(float));
		for(int j = 0; j < 25; j++){
			CovaNew[i][j] = Cova[i].pixelVect[j];
		}
	}

//	dsvd(CovaNew,25,25,w,EigenVect);		

	SDL_Surface *img = load_image("img.jpg");
	int count = 0;

	/*	for(int i = 0; i < 24*24; i++){
		for(int j = 0; j < 25; j++){

		printf(" |%d", vect[i].pixelVect[j]);
		printf(" |%d", TransVect[i].pixelVect[j]);
		}
		}*/

	for(int i = 0; i < 24; i++){

		//printf(" |%03d",vect[0].pixelVect[i]); 
		for(int j = 0; j < 24; j++){
			Uint8 val;
			val = vect[20].pixelVect[count];
			putpixel(img,i,j,val);
			count++;
		}
	}
	//	printf("| \n");
	grey_scale(img);
	display_image(img);
	wait_for_keypressed();
}
