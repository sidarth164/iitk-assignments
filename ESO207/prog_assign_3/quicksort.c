#include <stdio.h>
#include <time.h>

int comparisons=0;
//function to swap two elements
void swap(float *a, float *b){
	float t;
	t=*a;
	*a=*b;
	*b=t;
}

//function to perform partition function in quicksort
int partition(float a[],int lo, int hi){
	int pivot = a[hi];
	int i=lo-1;		//index of smaller element
	for(int j=lo; j<hi; j++){
		comparisons++;
		if(a[j]<=pivot){	//if current element is smaller than or equal to pivot
			i++;
			swap(&a[i],&a[j]);
		}
	}
	swap(&a[i+1],&a[hi]);
	return i+1;
}

void quicksort(float a[], int lo, int hi){
	if(lo<hi){
		//p is the partitioning index, a[p] is now at correct place
		int p = partition(a,lo,hi);

		//separately sort elements before and after partition
		quicksort(a,lo,p-1);
		quicksort(a,p+1,hi);
	}
}

void main()
{
	int n;
	scanf("%d",&n);

	float a[n];

	for(int i=0; i<n; i++){
		scanf("%f",a+i);
	}

	clock_t start, end;
    double cpu_time_used;
    start = clock();

	quicksort(a,0,n-1);
	/*for(int i=0;i<n;i++) printf("%f\t",a[i]);*/

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("%f\n",cpu_time_used);
	printf("%d\n", comparisons);
}