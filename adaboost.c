# include "adaboost.h"
# include "haar.h"
# include <math.h>
double epsilon = 0;
double treshold = 0;
double teta = 0;
double marge = 0;

int compute_marge(struct image *img)
{
	double marge_p = 999999;
	double marge_n = 999999;
	double marge = 0;

	while(img != NULL)
	{
		if(img->pos == 1)
			if(fabs(img->haar->val - treshold) < marge_p)
				marge_p = fabs(img->haar->val - treshold);
		if(img->pos == -1)
			if(fabs(img->haar->val - treshold) < marge_n)
				marge_n = fabs(img->haar->val - treshold);
	}
	marge = marge_p + marge_n;
	return marge;

}

double compute_tresh_min(struct image *img) // liste d'image
{
	double tresh = img->haar->val;
	while(img != NULL)
	{
		if(img->haar->val < tresh)
			tresh = img->haar->val;
		img++;
	}
	return tresh;
}

double compute_tresh_max(struct image *img)
{
	double tresh = img->haar->val;
	while(img != NULL)
	{
		if(img->haar->val > tresh)
			tresh = img->haar->val;
		img++;
	}
	return tresh;
}

void DSES(int nb_img, struct image *image, double treshold, double teta, double	epsilon, double marge)
{
	// INITIALISATION
	treshold = compute_tresh_min(image) - 1;
	marge = 0;
	epsilon = 2;

	//sum pos weights + sum neg weights
	int wpos_tp = 0;
	int wpos_tm = 0;
	int wneg_tp = 0;
	int wneg_tm = 0;
	for(int i = 0; i < nb_img; i++)
	{
		if(image[i].pos == 1)
		{
			if(image[i].haar->val > treshold)
			{	
				image[i].weight = 1;
				wpos_tp++;
			}
			if(image[i].haar->val < treshold)
				image[i].weight = 0;
		}
		else
		{
			if(image[i].haar->val > treshold)
			{
				image[i].weight = -1;
				wneg_tp++;
			}
			if(image[i].haar->val < treshold)
				image[i].weight = 0;
		}
	}

	// set iteartor
	int j = 0;
	int Epsilon;
	int Treshold = treshold;
	int Marge = marge;
	int error_p = 0;
	int error_n = 0;
	int Teta;

	while(1)
	{
		error_p = wpos_tm + wneg_tp;
		error_n = wpos_tp + wneg_tm;

		if(error_p < error_n)
		{
			Epsilon = error_p;
			Teta = 1;
		}
		else
		{
			Epsilon = error_n;
			Teta = -1;
		}

		if((Epsilon < epsilon) || (Epsilon = epsilon && Marge == marge))
		{
			epsilon = Epsilon;
			treshold = Treshold;
			marge = Marge;
			teta = Teta;
		}

		if(j == nb_img)
			break;

		j++;

		while(1)
		{
			if(image[j].pos == -1)
			{
				wneg_tm += image[j].weight;
				wneg_tp -= image[j].weight;
			}
			else
			{
				wpos_tm += image[j].weight;
				wpos_tp -= image[j].weight;
			}

			if((j == nb_img) || ( image[j].haar->val != image[j+1].haar->val))
				break;
			else
				j++;
		}

		if(j == nb_img)
		{
			Treshold = compute_tresh_max(image) + 1; // add i or j ?
			Marge = 0;
		}
		else
		{
			Treshold = image[j].haar->val + image[j+1].haar->val;
			Marge =  image[j-1].haar->val - image[j].haar->val;
		}
	}
}

void BStump(int nb_img,struct image *image,int nb_feat)
{

	epsilon = 2;
	double best_epsilon = 0;
	double best_marge = compute_marge(image);

	for(int i = 0; i < nb_feat; i++)
	{
		DSES(nb_img, image, treshold, teta, epsilon, marge);
		best_marge = compute_marge(image);
		if(best_epsilon > epsilon || best_marge > marge)
		{
			best_epsilon = epsilon;
			if(best_epsilon == epsilon)
			{
				return;
			}
		}
	}
}

void adaboost(int nb_img,struct image *image, int nb_round,int nb_feat)
{
	//init weights of images
	for(int i = 0; i < nb_img; i++) // we assume nb_pos = nb_neg
	{
		image[i].weight = 1/nb_img;
	}

	double alpha = 0;
	for(int t = 1; t < nb_round; t++)
	{
		BStump(nb_img, image, nb_feat);

		if(teta == 0 && t ==1)
			return;
		else
		{
			alpha = (1/2)*log10((1 - epsilon) / epsilon);
			image[t + 1].weight = image[t].weight ;
		}
	}
}
