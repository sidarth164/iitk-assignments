#include <stdio.h>
#include <time.h>

int comparisons=0;
//function to merge two arrays into 1
void merge(float arr[], int lo, int mid , int hi)
{
    int i, j, k;
    int n1 = mid - lo + 1;
    int n2 =  hi - mid;
 
    /* create temp arrays */
    float L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[lo + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = lo; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {	
    	comparisons++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(float a[],int lo, int hi){
	if(lo<hi){
		// Same as (lo+hi)/2, but avoids overflow for large lo and hi
        int mid = (lo+hi)/2;

        //sort first and second halves
        mergesort(a,lo,mid);
        mergesort(a,mid+1,hi);

        merge(a,lo,mid,hi);
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

	mergesort(a,0,n-1);
	//for(int i=0;i<n;i++) printf("%f\t",a[i]);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("%f\n",cpu_time_used);
	printf("%d\n", comparisons);
}