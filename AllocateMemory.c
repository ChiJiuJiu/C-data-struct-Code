#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
struct Node{
    int loc;
    int size;
    Node* next;
};
Node *Free, *Allocation;
Node* GetTarget(Node* Head,Node *p,int size){
    if(p->size == size){
        Node *pre = Head;
        while(pre->next != p)
            pre = pre->next;
        pre->next = p->next;
        p->next = NULL;
        return p;
    }else{
        p->size = size;
        Node *new = malloc(sizeof(Node));
        new->size = size;
        new->loc = p->loc;
        new->next = NULL;
        return NULL;
    }

}
Node* firstNode(Node* Free,int size){
    Node *p = Free->next;
    Node *judge = Free->next;
    if( !judge ){
        return NULL;
    }
    while(p){
        if(p->size < size){
            p = p->next;
        }
        judge = p->next;
        while (judge)
        {
            if ((judge->size < p->size) && judge->size >= size)
                p = judge;
        }
    }
    return GetTarget(Free, p, size);
}
void Allocate(Node* Head, Node* p){
    Node *pre = NULL;
    Node *target = Head->next;
    if(!target){
        Head->next = p;
        p->next = NULL;
        return;
    }
    while(1){
        if(target->loc < p->loc){
            pre = target;
            target = target->next;
        }
        p->next = target;
        pre->next = p;
        return;
    }
}
void Request(int size){
    Node *p = firstNode(Free, size);
    if(!p)
        return;
    Allocate(Allocation, p);
}
void Merge(Node* pre,Node* target,Node* p){
    if(pre->loc + pre->size == p->loc){
        pre->size += p->size;
        free(p);
        while (pre->next)
        {
            if (pre->loc + pre->size == target->loc)
            {
                pre->size += target->size;
                pre->next = target->next;
                free(target);
                target = pre->next;
            }
        }
    }else if(p->loc+p->size == target->loc){
        target->loc = p->loc;
        target->size += p->size;
        free(p);
        pre = target;
        target = pre->next;
        while(pre->next){
            if (pre->loc + pre->size == target->loc)
            {
                pre->size += target->size;
                pre->next = target->next;
                free(target);
                target = pre->next;
            }
        }
    }else{
        p->next = target;
        pre->next = p;
    }
}
void Insert(Node* Head,Node* p){
    Node *pre = Head;
    Node *target = Head->next;
    if(!target){
        Head->next = p;
        p->next = NULL;
        return;
    }
    while(target){
        if(target->loc <= p->loc){
            pre = target;
            target = target->next;
        }
    }
    Merge(pre, target, p);
}
Node* Findloc(Node* Head,int loc){
    Node *p = Head->next;
    Node *pre = Head;
    if(!p)
        return NULL;
    while(p){
        if(p->loc != loc){
            pre = p;
            p = p->next;
        }
    }
    if(!p){
        return NULL;
    }
    pre->next = p->next;
    p->next = NULL;
    return p;
}
void Free(Node* Head,int loc){
    Node *p = Findloc(Head, loc);
    if(!p)
        return;
    Insert(Free, p);
}