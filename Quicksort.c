#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int cutoff=3;
typedef int Elemtype;
void swap(Elemtype* a,Elemtype* b){
    Elemtype temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
int  Medium3(Elemtype A[],int left,int right){
    int center=(left+right)/2;
    if(A[left]>A[center])
        swap(&A[left],&A[center]);
    if(A[left]>A[right])
        swap(&A[left],&A[right]);
    if(A[center]>A[right])
        swap(&A[center],&A[right]);
    swap(&A[center],&A[right-1]);
    return right-1;
}
void InsertSort(Elemtype A[],int N){
    int i=0,j=0;
    Elemtype temp=0;
    for(i=1;i<N;i++){
        temp=A[i];
        for(j=i;j>0&&temp<A[j-1];j--){
            A[j]=A[j-1];
        }
        A[j]=temp;
    }
}
void Qsort(Elemtype A[],int left,int right){
    int low,high,pivot;
    if(cutoff<=right-left){
        low=left;
        high=right-1;
        pivot=Medium3(A,left,right);
        while(1){
            while(A[++low]<A[pivot]);
            while(A[--high]>A[pivot]);
            if(low<high)
                swap(&A[low],&A[high]);
            else break;
        }
        swap(&A[pivot],&A[low]);
        Qsort(A,left,low-1);
        Qsort(A,low+1,right);
    }else{
        InsertSort(A+left,right-left+1);
    }
}
void QuickSort(Elemtype A[],int N){
    Qsort(A,0,N-1);
}
int main(){
    srand(time(NULL));
    Elemtype A[10];
    int i=0;
    for(i=0;i<10;i++){
        A[i]=rand()%100+1;
        printf("%d ",A[i]);
    }
    printf("\n");
    QuickSort(A,10);
    for(i=0;i<10;i++){
        printf("%d ",A[i]);
    }
}
