/*
    Assignment 2
    ara305
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* A recursive function to calculate binomial coefficient */
int recursiveC(int n, int k){
    if (k==0 || k==n)
        return 1;
    else
        return recursiveC(n-1,k)+ recursiveC(n-1,k-1);
}
/* A function to calculate minimum of two numbers.*/
int  min(int a, int b){
    if(a>b)return b;
    else return a;
}

/* A function implementing dynamic programming to calculate binomial coefficient. */
int dynamicC(int n, int k){
    int i,j;
    int C[n+1][k+1]; // Array to store the computed values.

    for(i=0;i<=n;i++){
          for(j=0;j<=min(i,k);j++){
            if(j==0||j==i){
                C[i][j]=1;
            }
            else
                C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    return C[n][k];
}
// Pointer of pointers defined to be used for memonised version.
int **CC;

/* Functions for memonised version.*/
int getBinomial(int n, int k){
    if(CC[n][k]==-1){
        CC[n][k]=getBinomial(n-1,k-1)+getBinomial(n-1,k);
    }
    return CC[n][k];
}
int memonisedC(int n, int k){
    int i,j;
    // Initialisation of globally defined array CC.
    for(i=0;i<=n;i++){
        for(j=0;j<=k;j++){
                if (j==0 || i==j){
                    CC[i][j]=1;
                }
                else{
                    CC[i][j]=-1;
                }
        }
    }
    return getBinomial(n,k);
}

int main(){
    int i,j;
    int n, k = 5;
    clock_t tRecursive, tDynamic,tMemonised;
    double tR=0.0,tD=0.0,tM=0.0;
    int nExperiments=20;
    FILE *fp;
    fp = fopen("result.csv", "w+");

    for(n=10;n<=100;n=n+10){
        for(j=0;j<nExperiments;j++){
            tRecursive=clock();
            recursiveC(n, k);
            tRecursive=clock()-tRecursive;

            tDynamic=clock();
            dynamicC(n, k);
            tDynamic=clock()-tDynamic;

            // Creating an array using pointer of pointers to pass through a function.
            CC = (int **)malloc((n+1) * sizeof (int *));
            for(i=0; i<=n; i++)
            {
                CC[i] = (int *)malloc((k+1) * sizeof (int));
              }

            tMemonised=clock();
            memonisedC(n, k);
            tMemonised=clock()-tMemonised;

            tR+=(((double)tRecursive)/CLOCKS_PER_SEC)*1000000;
            tD+=(((double)tDynamic)/CLOCKS_PER_SEC)*1000000;
            tM+=(((double)tMemonised)/CLOCKS_PER_SEC)*1000000;
        }
        printf("%d %.2f %.2f %.2f\n",n,tR/nExperiments,tD/nExperiments,tM/nExperiments);
        fprintf(fp,"%d,%.2f,%.2f,%.2f\n",n,tR/nExperiments,tD/nExperiments,tM/nExperiments);
    }
    fclose(fp);
    return 0;
}
