#include <stdio.h>
#include <stdlib.h>
#define Maxsize 20
typedef struct{
    int Data[Maxsize];
    int last;
} List;
void Reverse(List* L){
    int i = 0, j = 0;
    int temp = 0;
    for (i = 0; i <= L->last;i++){
        temp = L->Data[L->last];
        for (j = L->last; j > i;j--)
            L->Data[j] = L->Data[j - 1];
        L->Data[j] = temp;
    }
}
void Insert(List* L,int x){
    L->Data[++L->last] = x;
}
List* Initialize(){
    List *L = (List *)malloc(sizeof(List));
    L->last = -1;
    return L;
}
void show(List* L){
    int i = 0;
    for (i = 0; i <= L->last;i++)
        printf("%d ", L->Data[i]);
}
int main(){
    int i = 0;
    List *L = Initialize();
    for (i = 0; i < 20;i++){
        Insert(L, i);
    }
    Reverse(L);
    show(L);
}
