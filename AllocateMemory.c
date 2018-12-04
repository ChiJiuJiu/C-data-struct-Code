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
Node* Adjust(Node* Head,Node* pre,Node* p,Node* next){
	if(pre->loc == 0 && pre->size == 0){		//fist node
		if(!next){
			pre->next = p->next;
			return p;
		}else{
			if(next->loc == p->loc + p->size){
				p->size += next->size;
				p->next = next->next;
				next->next = NULL;
				free(next);
				pre->next = p->next;
				p->next = NULL;
				return p;
			}else{
				pre->next = next;
				p->next = NULL;
				return p;
			}
		}	
	}
    if(!next){
        if(p->loc == pre->loc + pre->size){
            pre->size += p->size;
            Node *ppre = Head;
            while(ppre->next != pre)
                ppre = ppre->next;
            ppre->next = p->next;
            pre->next = NULL;
            p->next = NULL;
            free(p);
            return pre;
        }else{
            pre->next = NULL;
            return p;
        }
    }else{
        if ((p->loc != pre->loc + pre->size) && (p->loc + p->size != next->loc)){
            pre->next = next;
            p->next = NULL;
            return p;
        }else if((p->loc == pre->loc + pre->size) && (p->loc + p->size != next->loc)){
            Node *target = Head;
            while(target->next != pre){
                target = target->next;
            }
            target->next = next;
            pre->next = NULL;
            p->next = NULL;
            pre->size += p->size;
            return pre;
        }else{
            pre->size += p->size + next->size;
            Node *target = Head;
            while(target->next != pre){
                target = target->next;
            }
            target->next = next->next;
            pre->next = NULL;
            p->next = NULL;
            next->next = NULL;
            free(p);
            free(next);
            return pre;
        }
    }
}
void Insert(Node* Head,Node* node){
    Node *pre = Head;
    Node *p = Head->next;
    if(!p){
        pre->next = node;
        node->next = NULL;
        return;
    }
    while(p && (p->loc < node->loc)){
        pre = p;
        p = p->next;
    }
    node->next = p;
    pre->next = node;
    return;
}
int Merge(Node* pre,Node *next){
    if(next->loc == pre->loc + pre->size){
        pre->size += next->size;
        pre->next = next->next;
        next->next = NULL;
        free(next);
        return 1;
    }
    return 0;
}
void FreeMemory(Node *Allocation, int loc){
    Node *pre = Allocation;
    Node *p = Allocation->next;
    if(!p)
        return;
    while(p && (p->loc != loc)){
    	pre = p;
    	p = p->next;
	}
	if(!p)
		return;
    Node *target = Adjust(Allocation,pre, p, p->next);
    Insert(Free, target);
    pre = Free->next;
    if(!pre)
        return;
    p = pre->next;
    while(p){
        if(Merge(pre,p))
            p = pre->next;
        else{
            pre = p;
            p = pre->next;
        }
    }
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
    Free->loc = 0;
    Free->size = 0;
    Allocation->loc = 0;
    Allocation->size = 0;
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
