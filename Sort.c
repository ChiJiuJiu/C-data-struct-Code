#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define cuttoff 3
typedef int Elemtype;
void InsertSort(Elemtype A[],int N){
    int i=0,j=0;
    Elemtype temp=0;
    for(i=1;i<N;i++){
        temp=A[i];
        for(j=i;temp<A[j-1]&&j>0;j--){
            A[j]=A[j-1];
        }
        A[j]=temp;
    }
}
void ShellSort(Elemtype A[],int N){
    int D=0;
    int i=0,j=0;
    Elemtype temp=0;
    for(D=N;D>0;D/=2){
        for(i=D;i<N;i++){
            temp=A[i];
            for(j=i;j>=D&&A[j-D]>temp;j-=D){
                A[j]=A[j-D];
            }
            A[j]=temp;
        }
    }
}
void Bubble(Elemtype A[],int N){
    int i=0,j=0;
    Elemtype temp=0;
    for(i=0;i<N;i++){
        for(j=1;j<N-i;j++){
            if(A[j]<A[j-1]){
                temp=A[j];
                A[j]=A[j-1];
                A[j-1]=temp;
            }
        }
    }
}
void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
Elemtype Medium(Elemtype A[], int left, int right)
{
    int center = (left + right) / 2;
    if (A[left] > A[center])
        swap(&A[left], &A[center]);
    if (A[left] > A[right])
        swap(&A[left], &A[right]);
    if (A[center] > A[right])
        swap(&A[center], &A[right]);
    swap(&A[center], &A[right - 1]); //center in right-1
    return A[right - 1];             //consider 1~right-1
}
void Qsort(Elemtype A[],int left,int right){
    int pivot, low, high;
    if(cuttoff<=right-left){                    //large enough
        pivot = Medium(A, left, right);
        low = left;
        high = right - 1;
        while (1)
        {
            while(A[++low]<pivot)
                ;
            while(A[--high]>pivot)
                ;
            if(low<high)
                swap(&A[low], &A[high]);
            else
                break;
        }
        swap(&A[low], &A[right - 1]);
        Qsort(A, left, low - 1);
        Qsort(A, low + 1, right);
    }else{
        InsertSort(A + left, right - left + 1);
    }
}
void QuickSort(Elemtype A[],int N){
    Qsort(A, 0, N - 1);
}

int main(){
    int i=0;
    srand(time(NULL));
    Elemtype A[10];
    Elemtype B[10];
    Elemtype C[10];
    Elemtype D[10];
    for(i=0;i<10;i++){
        A[i]=rand()%100+1;
        B[i]=rand()%100+1;
        C[i]=rand()%100+1;
        D[i]=rand()%100+1;
        printf("%d ",A[i]);
    }
    InsertSort(A,10);
    printf("\n");
    for(i=0;i<10;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    ShellSort(B,10);
    for(i=0;i<10;i++){
        printf("%d ",B[i]);
    }
    printf("\n");
    Bubble(C,10);
    for(i=0;i<10;i++){
        printf("%d ",C[i]);
    }
    printf("\n");
    QuickSort(D, 10);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", D[i]);
    }
}
