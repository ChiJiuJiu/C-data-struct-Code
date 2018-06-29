#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int Elemtype;
#define MaxDigit 4
#define Radix 10
typedef struct node Node;
struct node{
    int key;
    Node *next;
};
struct HeadNode{
    Node *head, *tail;
};
typedef struct HeadNode Bucket[Radix];
int GetDigit(int x,int D){
    int d, i;
    for (i = 1; i <= D;i++){
        d = x % Radix;
        x /= Radix;
    }
    return d;
}
void LSD(Elemtype A[],int N){
    int D, Di, i;
    Bucket B;
    Node *temp, *p, *List = NULL;
    for (i = 0; i < N;i++){
        B[i].head = B[i].tail = NULL;               //initialize
    }
    for (i = 0; i < N;i++){
        temp = (Node *)malloc(sizeof(Node));
        temp->key = A[i];
        temp->next = List;
        List = temp;
    }
    for (D = 1; D <= MaxDigit;D++){                 //eact digit
        p = List;
        while (p)
        {
            Di = GetDigit(p->key, D);
            temp = p;
            p = p->next;
            temp->next = NULL;
            if(B[Di].head==NULL){
                B[Di].head = B[Di].tail = temp;
            }else{
                B[Di].tail->next = temp;
                B[Di].tail = temp;
            }
        }
        List = NULL;
        for (Di = Radix - 1; Di >= 0; Di--)
        {
            if (B[Di].head)
            {
                B[Di].tail->next = List;
                List = B[Di].head;
                B[Di].head = B[Di].tail = NULL;
            }
    }
}
for (i = 0; i < N;i++){
    temp = List;
    List = List->next;
    A[i] = temp->key;
    free(temp);
}
}
int  main()
{
    srand(time(NULL));
    int i = 0;
    Elemtype A[10];
    for (i = 0; i < 10;i++){
        A[i] = rand() % 100 + 1;
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", A[i]);
    }
    LSD(A, 10);
    printf("\n");
    for (i = 0; i < 10;i++){
        printf("%d ", A[i]);
    }
}