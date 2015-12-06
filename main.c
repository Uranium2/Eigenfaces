# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "eigenfaces.h"
# include "svd.h"
# include "grey_scale.h"

int main(){

	VectFace *vect, *TransVect, *Cova;
	int *avgFace;
	float **CovaNew = malloc(25*sizeof(float));
	float **eigenVect = malloc(25*sizeof(float));
	float *useless =  malloc(25*sizeof(float));
	//eigen = malloc(1*sizeof(VectFace));
	//eigen[0].pixelVect = malloc(24*24*sizeof(int));	
	SDL_Surface *imgavg = load_image("img.jpg");

	vect = ImageVectors();
	avgFace = AverageFace(vect);
	vect = Normalize(vect,avgFace);	
	TransVect = Trans(vect);
	Cova = Covariance(vect, TransVect);
	
	for(int i = 0; i < 25; i++){
		CovaNew[i] = malloc(25*sizeof(float));
		eigenVect[i] = malloc(25*sizeof(float));
	}
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			CovaNew[i][j] = (float)Cova[i].pixelVect[j];	
		}
	}
	
        dsvd(CovaNew, 25, 25, useless, eigenVect);	
	//eigFace = eigenFace(vect, eigenVect[1]);
	//eigen[0].pixelVect = eigFace;

	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){

			printf(" |%f" , eigenVect[i][j]);
	                //printf(" |%f", CovaNew[i][j]);
			//printf(" |%d", vect[i].pixelVect[j]);
			//printf(" |%d", TransVect[i].pixelVect[j]);
		}
	}
	
	printf("| \n");
	int count = 0;
	for(int i = 0; i < 24; i++){
		for(int j = 0; j < 24; j++){
			Uint8 val;
			val = avgFace[count];
			putpixel(imgavg,i,j,val);
			count++;
		}
	}
	grey_scale(imgavg);
	display_image(imgavg);
	DisplayImage(vect);

}
