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
        p->size -= size;
        Node *new = malloc(sizeof(Node));
        new->size = size;
        new->loc = p->loc;
        p->loc += size;
        new->next = NULL;
        return new;
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
        else break;
    }
    	if(!p)
    		return NULL;
        judge = p->next;
        while (judge)
        {
            if ((judge->size < p->size) && judge->size >= size)
                p = judge;
            else
            	break;
        }
    return GetTarget(Free, p, size);
}
void Adjust(Node* pre,Node* next){
    if(pre->loc == next->loc)
        next->loc += pre->size;
}
void Allocate(Node* Head, Node* p){
    Node *pre = Head;
    Node *target = Head->next;
    if(!target){
        Head->next = p;
        p->next = NULL;
        return;
    }
    while(target && (target->loc < p->loc)){
    	pre = target;
    	target = target->next;
	}
		p->next = target;	// even though !target is ok
		pre->next = p;
}
void Request(int size){
    Node *p = firstNode(Free, size);
    if(!p){
    	printf("Request Memory Fail!\n");
    	return;	
	}
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
    }else if(target && p->loc+p->size == target->loc){
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
        }else
        {
            break;
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
        }else
        	break;
    }
    if(!p){
        return NULL;
    }
    pre->next = p->next;
    p->next = NULL;
    return p;
}
void FreeMemory(Node* Head,int loc){
    Node *p = Findloc(Head, loc);
    if(!p){
    	printf("Free Memory Fail!\n");
    	return;	
	}
    Insert(Free, p);
}
void Display(Node* Head){
    Node *p = Head->next;
    while(p){
        printf("loc:%d,size:%d ", p->loc, p->size);
        p = p->next;
    }
    printf("\n");
}
void InitMemory(Node* Free,int loc,int size){
    Free->loc = loc;
    Free->size = size;
    Node *new = (Node *)malloc(sizeof(Node));
    new->loc = loc;
    new->size = size;
    new->next = NULL;
    Free->next = new;
}
void Menu(){
    printf("1.Initialize Memory\n");
    printf("2.Request Memory\n");
    printf("3.Free Memory\n");
    printf("0.exit\n");
    printf("Please select:");
}
int main(){
    Free = (Node *)malloc(sizeof(Node));
    Allocation = (Node *)malloc(sizeof(Node));
    Free->next = NULL;
    Allocation->next = NULL;
    int x = 0,loc = 0,size = 0;
    while(1){
        Menu();
        scanf("%d", &x);
        switch (x){
        case 1 :
            printf("Please input the loc and size of Memory:");
            scanf("%d%d", &loc, &size);
            InitMemory(Free, loc, size);
            printf("Below is the current FreeList:\n");
            Display(Free);
            break;
        case 2:
            printf("Please input the size you request:");
            scanf("%d", &size);
            Request(size);
            printf("Below is the current FreeList:\n");
            Display(Free);
            printf("Below is the current AllocationList:\n");
            Display(Allocation);
            break;
        case 3:
            printf("Please input the loc you want to free:");
            scanf("%d", &loc);
            FreeMemory(Allocation, loc);
            printf("Below is the current FreeList:\n");
            Display(Free);
            printf("Below is the current AllocationList:\n");
            Display(Allocation);
            break;
        case 0:
            printf("Thanks to use!\n");
            exit(1);
            break;
        }
    }
}
