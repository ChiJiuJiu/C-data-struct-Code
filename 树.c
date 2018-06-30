#include <stdio.h>
#include <stdlib.h>
typedef struct TNode Tree;
typedef char Elemtype;
struct TNode{
    Elemtype data;
    Tree *Left, *Right;
};
Tree* PreCreateTree(){
    Tree *Root=NULL;
    char x;
    scanf("%c", &x);
    if(x==' ')
        Root = NULL;
    else{
        Root = (Tree *)malloc(sizeof(Tree));
        Root->data = x;
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
    Tree *Root = NULL;
    Root = PreCreateTree();
    //PostOrder(Root);
    int n = 0;
    n = Count(Root);
    printf("%d ", n);
}