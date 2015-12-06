# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "eigenfaces.h"

int main(){

	VectFace *vect, *TransVect, *Cova;
	int *avgFace;
	float **CovaNew = malloc(25*sizeof(float));
	float **eigenVect;

	vect = ImageVectors();
	avgFace = AverageFace(vect);
	vect = Normalize(vect,avgFace);	
	TransVect = Trans(vect);
	Cova = Covariance(vect, TransVect);
		
	for(int i = 0; i < 25; i++){
		CovaNew[i] = malloc(25*sizeof(float));
		for(int j = 0; j < 25; j++){
			
			CovaNew[i][j] = Cova[i].pixelVect[j];
		}
	}
	printf("fuck this shit \n");
	eigenVect = svdEigen(CovaNew);

	for(int i = 0; i < 25/*(24*24)*/; i++){
		for(int j = 0; j < 25; j++){

//			printf(" |%f" , eigenVect[i][j]);
//		        printf(" |%f", CovaNew[i][j]);
			//printf(" |%d", vect[i].pixelVect[j]);
			//printf(" |%d", TransVect[i].pixelVect[j]);
		}
	}

//	printf("| \n");
//	DisplayImage(vect);
}
