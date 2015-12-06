# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "eigenfaces.h"
# include "svd.h"


int main(){

	VectFace *vect, *TransVect, *Cova;
	int *avgFace;
	float **CovaNew = malloc(25*sizeof(float));
	float **eigenVect = malloc(25*sizeof(float));
	float *useless =  malloc(25*sizeof(float));

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

	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){

			printf(" |%f" , eigenVect[i][j]);
	                //printf(" |%f", CovaNew[i][j]);
			//printf(" |%d", vect[i].pixelVect[j]);
			//printf(" |%d", TransVect[i].pixelVect[j]);
		}
	}
		
	//printf("| \n");

//	DisplayImage(vect);
}
