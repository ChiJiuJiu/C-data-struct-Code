#include <stdio.h>
#include <stdlib.h>
typedef struct LNode List;
struct LNode{
    int Data;
    List *next;
};
List* Initilize(){
    List *L = (List *)malloc(sizeof(List));
    L->next = NULL;
    return L;
}
void InsertNode(List* Head,int x){
    List *NewNode = (List *)malloc(sizeof(List));
    NewNode->Data = x;
    NewNode->next = Head->next;
    Head->next = NewNode;
}
void show(List* Head){
    List *p = Head->next;
    if(!p)
        return;
    while (p)
    {
        printf("%d ", p->Data);
        p = p->next;
    }
}
void Revers(List* Head){
    List *p,*q, *PH = Head;
    p = q = Head->next;
    if(!p)
        return;
    for (; PH->next->next;PH=PH->next){
        for (; p->next;p=p->next)
            q = p;
        q->next = p->next;
        p->next = PH->next;
        PH->next = p;
    }
}
int main(){
    List *Head = (List *)malloc(sizeof(List));
    Head = Initilize();
    int i = 0;
    for (i = 0; i < 10;i++){
        InsertNode(Head, i);
    }
    Revers(Head);
    show(Head);
}