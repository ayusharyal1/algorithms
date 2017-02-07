/*
    Assignment 1
    Intro To Algorithms
    ara305
    Source:
    http://geeksquiz.com/mergesort
    http://geeksquiz.com/insertion-sort/
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n){
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;

       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
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

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the sub-array
  of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void generateArray(int arr1[],int arr2[],int size){
    int i =0;
    int value=0;
    for (i=0;i<size;i++){
        value = rand()%1000+1;
        arr1[i] = value;
        arr2[i]=value;
    }
}
// Driver program to test above functions
int main()
{
    int *arr1,*arr2;
    int nExperiemnts=1000;
    clock_t tInsert,tMerge;
    double diffInsert=0.0,diffMerge=0.0;
    double avgInsert,avgMerge;
    srand(0);
    FILE *fp;
    fp = fopen("result.csv", "w+");

    for(int i=10;i<=300;i=i+10){
            avgInsert=0.0;
            avgMerge=0.0;
            for(int j=0;j<nExperiemnts;j++){
                arr1= malloc(i * sizeof *arr1);
                arr2= malloc(i * sizeof *arr2);
                generateArray(arr1,arr2,i);

                //printArray(arr1,i);
                tInsert=clock();
                insertionSort(arr1,i);
                tInsert=clock()-tInsert;

                tMerge=clock();
                mergeSort(arr2,0,i-1);
                tMerge=clock()-tMerge;

                diffInsert=((double)tInsert)/CLOCKS_PER_SEC;
                diffMerge=((double)tMerge)/CLOCKS_PER_SEC;

                avgInsert+=diffInsert;
                avgMerge+=diffMerge;

                free(arr1);
                free(arr2);
            }
            printf("%d,%.10f,%.10f\n",i,avgInsert/nExperiemnts,avgMerge/nExperiemnts);
            fprintf(fp,"%d,%.10f,%.10f\n",i,avgInsert/nExperiemnts,avgMerge/nExperiemnts);
            }
    }

