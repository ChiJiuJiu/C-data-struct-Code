#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int Elemtype;
void PerDown(Elemtype A[],int root,int N){
    int Parent,Child;
    Elemtype x=A[root];
    for(Parent=root;(Parent*2+1)<N;Parent=Child){
        Child=2*Parent+1;
        if((Child+1<N)&&(A[Child]<A[Child+1]))
            Child++;
        if(x>=A[Child])
            break;
        else
            A[Parent]=A[Child];
    }
    A[Parent]=x;
}
void swap(Elemtype* a,Elemtype* b){
    Elemtype temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void HeapSort(Elemtype A[],int N){
    int i=0;
    for(i=N/2-1;i>=0;i--){
        PerDown(A,i,N);
    }
    for(i=N-1;i>0;i--){
        swap(&A[i],&A[0]);
        PerDown(A,0,i);
    }
}
int main(){
    srand(time(NULL));
    Elemtype A[10];
    int i=0;
    for(i=0;i<10;i++){
        A[i]=rand()%100+1;
        printf("%d ",A[i]); 
    }
    HeapSort(A,10);
    printf("\n");
    for(i=0;i<10;i++){
        printf("%d ",A[i]);
    }
}
