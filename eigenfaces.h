# include "pixel_operations.h"
# include "sdl_stuff.h"
# include <stdio.h>
# include <stdlib.h>
# include "svd.h"

#ifndef VectFace
#define Vectface

typedef struct VectFace VectFace;
struct VectFace 

{
	int *pixelVect;

};

#endif

VectFace* ImageVectors();

int* AverageFace(VectFace *vect);

VectFace* Normalize(VectFace *vect, int* avgFace);

VectFace* Trans(VectFace *vect);

void DisplayImage(VectFace* vect);

VectFace* Covariance(VectFace *vect, VectFace* trans);

float** svdEigen(float** covar);
