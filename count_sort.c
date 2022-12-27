#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <sys/time.h>

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

void Count_sort(int a[], int n, int num_threads) { 
    int i, j, count;
    int* temp = malloc(n*sizeof(int));
    #pragma omp parallel for num_threads(num_threads) \
        default(none) private(i, j, count) shared(a, temp, n)
    for (i=0; i<n; i++) { 
        count = 0; 
        for (j=0; j< n;j++) 
            if (a[j] < a[i]) count++; 
        else if (a[j] == a[i] && j < i)
            count++;
        temp[count] = a[i];

    }
    memcpy(a, temp, n*sizeof(int)); 
    free(temp); 
} /* Count sort */

int main()
{
    int n = 100000;
    int *a = malloc(n*sizeof(int));
    struct timeval start, end;
    //printf("%d\n", n);
    int num_threads;
    for(int i = 0; i < n; i++)
        a[i] = rand() % 100000;

    //scanf("%d", &num_threads);
    //omp_set_num_threads(num_threads);
    gettimeofday(&start, NULL);
    qsort(a, n, sizeof(int), cmpfunc);
    Count_sort(a, n, num_threads);
    gettimeofday(&end, NULL);
    //for (int i = 0; i < n; i++)
    //    printf("%d ", a[i]);
    //printf("\n");
    printf("Time: %ld us\n", ((end.tv_sec * 1000000 + end.tv_usec)-
                        (start.tv_sec * 1000000 + start.tv_usec)));
}