#include <stdio.h>
#include <stdlib.h>
void SelectSort(int a[], int N){
    int min;
    int temp;
    int i = 0,j = 0;
    for (i = 0; i < N - 1; i++){
        min = i;
        for (j = i + 1; j < N; j++){
            if(a[j] < a[min])
                min = j;
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}
int main(){
    int a[10] = {10, 21983, 9238, 3947, 20193, 21039, 3847, 11, 9, 2};
    int i = 0;
    for (i = 0; i < 10;i++){
        printf("%d ", a[i]);
    }
    SelectSort(a, 10);
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
}