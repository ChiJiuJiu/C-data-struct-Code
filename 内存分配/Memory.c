#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
struct Node{
    int loc;
    int size;
    Node* next;
};
Node *freeList, *allocateList;
void allocatmemory(int size){
Node *p = freeList->next;
    Node *q = freeList->next;
    if( !p ){
        return;
    }
    while(p && (p->size < size)){
        p = p->next;
    }
    	if(!p)
    		return;
        q = p->next;
        while (q)
        {
            if ((q->size < p->size) && q->size >= size)
                p = q;
            else
            	break;
        }
        if(p->size == size){
        Node *pre = freeList;
        while(pre->next != p)
            pre = pre->next;
        pre->next = p->next;
        p->next = NULL;
    }else{
        p->size -= size;
        Node *new = malloc(sizeof(Node));
        new->size = size;
        new->loc = p->loc;
        p->loc += size;
        new->next = NULL;
        p = new; 
    }
	Node* pre = allocateList;
    q = allocateList->next;
    if(!q){
        allocateList->next = p;
        p->next = NULL;
        return;
    }
    while(q && (q->loc < p->loc)){
    	pre = q;
    	q = q->next;
	}
		p->next = q;	
		pre->next = p;
}
void FreeMemory(Node *allocateList, int loc){
    Node *pre = allocateList;
    Node *p = allocateList->next;
    Node *pre2 = freeList;
    Node *p2 = freeList->next;
    if(!p)
        return;
    while(p && (p->loc != loc)){
    	pre = p;
    	p = p->next;
	}
	if(!p)
		return;
	Node* next = p->next;
Node* get;
if(pre->loc == 0 && pre->size == 0){		
		if(!next){
			pre->next = p->next;
		get = p;
		goto flag;
		}else{
			if(next->loc == p->loc + p->size){
				p->size += next->size;
				p->next = next->next;
				next->next = NULL;
				free(next);
				pre->next = p->next;
				p->next = NULL;
			get = p;
			goto flag;
			}else{
				pre->next = next;
				p->next = NULL;
				get = p;
			goto flag;
			}
		}	
	}
    if(!next){
        if(p->loc == pre->loc + pre->size){
            pre->size += p->size;
            Node *ppre = allocateList;
            while(ppre->next != pre)
                ppre = ppre->next;
            ppre->next = p->next;
            pre->next = NULL;
            p->next = NULL;
            free(p);
            get = pre;
			goto flag;
        }else{
            pre->next = NULL;
            get = p;
			goto flag;
        }
    }else{
        if ((p->loc != pre->loc + pre->size) && (p->loc + p->size != next->loc)){
            pre->next = next;
            p->next = NULL;
            get = p;
			goto flag;
        }else if((p->loc == pre->loc + pre->size) && (p->loc + p->size != next->loc)){
            Node *target = allocateList;
            while(target->next != pre){
                target = target->next;
            }
            target->next = next;
            pre->next = NULL;
            p->next = NULL;
            pre->size += p->size;
            get = pre;
			goto flag;
        }else{
            pre->size += p->size + next->size;
            Node* target = allocateList;
            while(target->next != pre){
                target = target->next;
            }
            target->next = next->next;
            pre->next = NULL;
            p->next = NULL;
            next->next = NULL;
            free(p);
            free(next);
            get = pre;
			goto flag;
        }
    }
flag:
    if(!p2){
        pre2->next = get;
        get->next = NULL;
        return;
    }
    while(p2 && (p2->loc < get->loc)){
        pre2 = p2;
        p2 = p2->next;
    }
    get->next = p2;
    pre2->next = get;
    return;
}
void showList(Node* Head){
    Node *p = Head->next;
    while(p){
        printf("地址:%d,大小:%d ", p->loc, p->size);
        p = p->next;
    }
    printf("\n");
}
void initialize(int loc,int size){
    freeList->loc = loc;
    freeList->size = size;
    Node *new = (Node *)malloc(sizeof(Node));
    new->loc = loc;
    new->size = size;
    new->next = NULL;
    freeList->next = new;
}

int main(){
    freeList = (Node *)malloc(sizeof(Node));
    allocateList = (Node *)malloc(sizeof(Node));
    freeList->loc = 0;
    freeList->size = 0;
    allocateList->loc = 0;
    allocateList->size = 0;
    freeList->next = NULL;
    allocateList->next = NULL;
    int x = 0,loc = 0,size = 0;
    while(1){
        printf("1.初始化内存\n");
	    printf("2.申请内存\n");
	    printf("3.释放内存\n");
	    printf("4.显示当前队列\n");
	    printf("0.退出\n");
	    printf("请选择:");
        scanf("%d", &x);
        switch (x){
        case 1 :
            printf("请输入内存首地址和大小:");
            scanf("%d%d", &loc, &size);
            initialize(loc, size);
            break;
        case 2:
            printf("请输入申请内存大小:");
            scanf("%d", &size);
            allocatmemory(size);
            break;
        case 3:
            printf("请输入需要释放内存的首地址:");
            scanf("%d", &loc);
            FreeMemory(allocateList, loc);
            break;
        case 4:
			printf("当前空闲队列:\n");
            showList(freeList);
            printf("当前分配队列:\n");
            showList(allocateList);
            break;
        case 0:
            printf("再见!\n");
            exit(1);
            break;
        }
    }
}
