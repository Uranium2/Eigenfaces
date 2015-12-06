# include <stdlib.h>
# include "quick_sort.h"

int part(struct HaarF *listH, int p, int r)
{
	int pivot = listH[p].val, i = p, j =r+1;
	struct HaarF temp;
	while(1)
	{
		printf("j = %d i = %d p = %d \n", j, i, p);
		printf("haar[j] = %d pivot = %d\n", listH[99999].val, pivot);
		do j--; while(listH[j].val > pivot);
		printf("test1 \n");
		do i++; while(listH[i].val < pivot);
		printf("test2 \n");
		if(i < j)
		{
			temp = listH[i];
			listH[i] = listH[j];
			listH[j] = temp;
		}
		else
			return j;
	}
}

void quick_sort(struct HaarF *listH, int p, int r)
{
	int q;
	if(p < r)
	{
		q = part(listH, p, r);
		printf("test1\n");
		quick_sort(listH, p, q);
		quick_sort(listH, q+1, r);
	}
}
