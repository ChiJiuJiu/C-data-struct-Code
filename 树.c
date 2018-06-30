#include <stdio.h>
#include <stdlib.h>
typedef struct TNode Tree;
typedef char Elemtype;
#define Maxsize 100
struct TNode{
    Elemtype data;
    Tree *Left, *Right;
    int flag;
};
typedef struct{
    Tree *Data[Maxsize];
    int top;
} Stack;
typedef struct{
    Tree *Data[Maxsize];
    int front, rear;
} Queue;
int StackIsEmpty(Stack* S){
    return (S->top == -1);
}
int StackIsFull(Stack* S){
    return (S->top == Maxsize - 1);
}
int Push(Stack* S,Tree *Root){
    if(StackIsFull(S)){
        printf("Stack is Full!\n");
        return 0;
    }
    S->Data[++S->top] = Root;
    return 1;
}
Tree* Pop(Stack* S){
    if(StackIsEmpty(S)){
        printf("Stack is empty!\n");
        return NULL;
    }
    return S->Data[S->top--];
}
Stack* InitializeStack(){
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->top = -1;
    return S;
}
Queue* InitializeQueue(){
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}
int QueueIsEmpty(Queue *Q){
    return (Q->front == Q->rear);
}
int QueueIsFull(Queue* Q){
    return ((Q->rear + 1) % Maxsize == Q->front);
}
int InsertElement(Queue* Q,Tree* Root){
    if(QueueIsFull(Q)){
        printf("Queue is Full!\n");
        return 0;
    }
    Q->Data[Q->rear] = Root;
    Q->rear = (Q->rear + 1) % Maxsize;
    return 1;
}
Tree* DeleteElement(Queue* Q){
    if(QueueIsEmpty(Q)){
        printf("Queue is Empty!\n");
        return NULL;
    }
    Tree *temp;
    temp = Q->Data[Q->front];
    Q->front = (Q->front + 1) % Maxsize;
    return temp;
}
void InOrderTree(Tree* Root){
    Stack *S = InitializeStack();
    Tree *T = Root;
    while (T||!StackIsEmpty(S))
    {
        while (T)
        {
            Push(S, T);
            T = T->Left;
        }
        if (!StackIsEmpty(S)){
            T = Pop(S);
            printf("%c", T->data);
        }
        T = T->Right;
    }
}
void PreOrderTree(Tree* Root){
    Stack *S = InitializeStack();
    Tree *T = Root;
    while (T || !StackIsEmpty(S))
    {
        while (T)
        {
            Push(S, T);
            printf("%c", T->data);
            T = T->Left;
        }
        if (!StackIsEmpty(S))
        {
            T = Pop(S);
        }
        T = T->Right;
    }
}
void PostOrderTree(Tree *Root){
    Stack *S= InitializeStack();
    Tree *T = Root;
    while (T||!StackIsEmpty(S))
    {
        while (T&&T->flag==0)
        {
            Push(S, T);
            T->flag++;
            T = T->Left;
        }
        if(!StackIsEmpty(S)){
            T = Pop(S);
            if(T->Right&&T->Right->flag==0)
                Push(S, T);
            else
            {
                printf("%c", T->data);
            }
            T = T->Right;
        }else
        {
            return;
        }
    }
}
void LineOrderTree(Tree *Root){
    Queue *Q = InitializeQueue();
    Tree *T = Root;
    if(!T)
        return;
    InsertElement(Q, T);
    while (!QueueIsEmpty(Q))
    {
        T = DeleteElement(Q);
        printf("%c", T->data);
        if(T->Left)
            InsertElement(Q, T->Left);
        if(T->Right)
            InsertElement(Q, T->Right);
    }
}
Tree* PreCreateTree(){
    Tree *Root=NULL;
    char x;
    scanf("%c", &x);
    if(x==' ')
        Root = NULL;
    else{
        Root = (Tree *)malloc(sizeof(Tree));
        Root->data = x;
        Root->flag = 0;
        Root->Left = PreCreateTree();
        Root->Right = PreCreateTree();
    }
    return Root;
}
void PreOrder(Tree* Root){
    if(Root){
        printf("%c", Root->data);
        PreOrder(Root->Left);
        PreOrder(Root->Right);
    }
}
void InOrder(Tree* Root){
    if(Root){
        InOrder(Root->Left);
        printf("%c", Root->data);
        InOrder(Root->Right);
    }
}
void PostOrder(Tree* Root){
    if(Root){
        PostOrder(Root->Left);
        PostOrder(Root->Right);
        printf("%c", Root->data);
    }
}
int Count(Tree* Root){
    int n=0;
    if(Root){
        if(!(Root->Left)&&!(Root->Right))
            n++;
        n += Count(Root->Left);
        n += Count(Root->Right);
    }
    return n;
}
int main(){
    //int n = 0;
    Tree *Root = NULL;
    Root = PreCreateTree();
    LineOrderTree(Root);
    //PostOrder(Root);
    // n = Count(Root);
    // printf("%d ", n);
}