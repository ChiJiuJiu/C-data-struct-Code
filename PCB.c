#include <stdio.h>
#include <stdlib.h>
typedef struct PCB PCB;
struct PCB {
    int PID;
    int UID;
    PCB* next;
};

PCB* HReady;
PCB* HRun;
PCB* Hblock;

void Insert(PCB* Head, PCB* node) {
    PCB* pointer = Head;
    while(pointer->next){
        pointer = pointer->next;
    }
    pointer->next = node;
    node->next = NULL;
}

int isEmpty(PCB* Head){
    return (Head->next == NULL);
}

PCB* getP(PCB* Head) {
    PCB* pointer = Head->next;
    Head->next = pointer->next;
    return pointer;
}

void delete(PCB* Head,int pid) {
    if(!isEmpty(Head)){
    PCB* pointer = Head->next;
    PCB* pre = Head;
    while(pointer && (pointer->PID != pid)) {
        pre = pointer;
        pointer = pointer->next;
    }
    if(!pointer)
        return;
    pre->next = pointer->next;
    pointer->next = NULL;
    free(pointer);
    }
}

void create() {
    PCB* node = (PCB*)malloc(sizeof(PCB));
    scanf("%d%d",&node->PID,&node->UID);
    Insert(HReady,node);
    if(isEmpty(HRun)){
        Insert(HRun,getP(HReady));
    }
}

void destroy() {
    int pid;
    scanf("%d",&pid);
    delete(HReady,pid);
    delete(HRun,pid);
    delete(Hblock,pid);
    if(isEmpty(HRun)){
        if(!(isEmpty(HReady)))
            Insert(HRun,getP(HReady));
    }
}

void block() {
    int pid;
    scanf("%d",&pid);
    if(!isEmpty(HRun)){
        PCB* pointer = HRun->next;
        PCB* pre = HRun;
        while(pointer && (pointer->PID != pid)){
            pre = pointer;
            pointer = pointer->next;
        }
        if(!pointer){
        	printf("No such programming!\n");
			return;	
		}
        pre->next = pointer->next;
        pointer->next = NULL;
        Insert(Hblock,pointer);
        if(isEmpty(HRun)){
            if(!isEmpty(HReady))
                Insert(HRun,getP(HReady));
        }
    }else{
    	printf("Running List is Empty!\n");
	}
}

void wakeup() {
    int pid;
    scanf("%d",&pid);
    if(!isEmpty(Hblock)){
        PCB* pointer = Hblock->next;
        PCB* pre = Hblock;
        while(pointer && (pointer->PID != pid)) {
            pre = pointer;
            pointer = pointer->next;
        }
        if(!pointer){
        	printf("No such programming!\n");
		    return;
		}
        pre->next = pointer->next;
        pointer->next = NULL;
        Insert(HReady,pointer);
        if(isEmpty(HRun))
            Insert(HRun,getP(HReady));
    }else {
    	printf("Block List is Empty!\n");
	}
}
void show(PCB* Head){
    if(isEmpty(Head)){
        printf("Empty!\n");
        return;
    }
    PCB *pointer = Head->next;
    while(pointer) {
        printf("PID:%d UID:%d ", pointer->PID, pointer->UID);
        pointer = pointer->next;
    }
    printf("\n");
}

void display() {
    printf("Ready List:\n");
    show(HReady);
    printf("Running List:\n");
    show(HRun);
    printf("Block List:\n");
    show(Hblock);
}

int main(){
    Hblock = (PCB *)malloc(sizeof(PCB));
    HReady = (PCB *)malloc(sizeof(PCB));
    HRun = (PCB *)malloc(sizeof(PCB));
    Hblock->next = HReady->next = HRun->next = NULL;
    char x[2];
    while(1){
        printf("1.Create a Programming\n");
        printf("2.Destroy a Programming\n");
        printf("3.Block a Programming\n");
        printf("4.Wake up a Programming\n");
        printf("5.Display\n");
        printf("0.Exit\n");
        printf("Please Select:");
        fflush(stdin);
        scanf("%c", x);
        while(sizeof(x)>2||x[0]<'0'||x[0]>'5'){
        	printf("Input error! Please input again:");
        	fflush(stdin);
        	scanf("%c", x);
		}
        switch(x[0]){
            case '1':
                printf("Please input the programming ID AND User ID:");
                create();
                break;
            case '2':
                printf("Please input the programming ID:");
                destroy();
                break;
            case '3':
                printf("Please input the programming ID:");
                block();
                break;
            case '4':
                printf("Please input the programming ID:");
                wakeup();
                break;
            case '5':
                display();
                break;
            case '0':
                printf("bye\n");
                exit(1);
                break;
        }
    }
}
