# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "eigenfaces.h"
# include "grey_scale.h"

VectFace* ImageVectors(){

	VectFace *vect = malloc(25*sizeof(VectFace));
	for( int i = 1; i <= 25; i++){

		SDL_Surface *img;
		char path[8];

		sprintf(path, "Faces/f%d", i);
		strcat(path, ".pgm");	
		img = load_image(path);
		vect[i-1].pixelVect = malloc(24*24*sizeof(int));

		int count = 0;
		for(int j = 0; j < 24; j++){
			for(int k = 0; k < 24; k++){

				vect[i-1].pixelVect[count] = getpixel(img,j,k);
				count++;
			}

		}

	}
	return vect;
}

int* AverageFace(VectFace *vect){

	int *averageFace = malloc(25*25*sizeof(int));

	for(int i = 0; i < 24*24; i++){
		for(int j = 0; j < 25; j++){
			averageFace[i] += vect[j].pixelVect[i];
		}
	}

	for(int i = 0; i < 24*24; i++){
		averageFace[i] = averageFace[i] / 25;
	}
	return averageFace;
}

VectFace* Normalize(VectFace *vect, int* avgFace){

	int count = 0;
	for(int i = 0; i < 24*24; i++){
		for(int j = 0; j < 25; j++){

			vect[j].pixelVect[i] = vect[j].pixelVect[i]- avgFace[count];

		}
		count++;
	}
	return vect;
}

void DisplayImage(VectFace* vect){

init_sdl();

SDL_Surface *img = load_image("img.jpg");
int count = 0;

for(int i = 0; i < 24; i++){
		for(int j = 0; j < 24; j++){
			Uint8 val;
			val = vect[20].pixelVect[count];
			putpixel(img,i,j,val);
			count++;
		}
	}

	grey_scale(img);
	display_image(img);
	wait_for_keypressed();
}

VectFace* Trans(VectFace *vect){

	VectFace *trans = malloc(24*24*sizeof(VectFace));

	for(int i = 0; i < 24*24; i++){

		trans[i].pixelVect = malloc(25*sizeof(int));		
		for(int j = 0; j < 25; j++){

			trans[i].pixelVect[j] = vect[j].pixelVect[i];
		}
	}
	return trans;
}

VectFace* Covariance(VectFace *vect, VectFace *trans){

	VectFace *cov = malloc(25*sizeof(VectFace));
	int sum = 0;

	for(int i = 0; i < 25; i++){
		cov[i].pixelVect = malloc(25*sizeof(int));
		for(int j = 0; j < 25; j++){
			for(int k = 0; k < 24*24; k++){
				sum += vect[i].pixelVect[k] * trans[k].pixelVect[j];
			}
			cov[i].pixelVect[j] = sum;
			sum = 0;		
		}
	}
	return cov;
}

float** svdEigen(float** covar){
	printf("test0 \n");	
	float **v = calloc(25, sizeof(float));
	float *w = calloc(25, sizeof(float));
	printf("test1 \n");
	for(int i = 0; i < 25; i++)
		v[i] = calloc(25,sizeof(float));
	printf("test2 \n");
	dsvd(covar,25,25,w,v);
	printf("test3 \n");

        return v;	
}
