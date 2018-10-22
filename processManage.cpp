#include<stdio.h>
#include<stdlib.h>
typedef struct PCB
{
   int pid;
   int uid;
   struct PCB *next;
}PCB;

PCB *Run,*Ready,*Wait;
void display(PCB *H)
{	if(H->next == NULL){
	printf("该队列为空!\n");
	return;
}


   PCB *p;
   p=H;
   while(p->next!=NULL)
   { 
	   p=p->next;
       printf("PID=%d  UID=%d \n",p->pid,p->uid);
   }

}


void create()
{
   PCB *p,*s;
   s=(PCB*)malloc(sizeof(PCB));
   printf("input pid & uid:");
   scanf("%d%d",&s->pid,&s->uid);
   s->next=NULL;
   //把新建的节点插入到就绪队列；
   p=Ready;
   while(p->next!=NULL)
   {
      p=p->next;
   }
   p->next=s;
  
  //判断run队列是否为空，如果为空，从ready对列中选择一个节点插入到run队列中
	if(Run->next == NULL){
	PCB* node = Ready->next;
	Ready->next = node->next;
	node->next = NULL;
	Run->next = node;
	}
	}		

void Insert(PCB* Head, PCB* node) {
    PCB* pointer = Head;
    while(pointer->next){
        pointer = pointer->next;
    }
    pointer->next = node;
    node->next = NULL;
}
void block(){
	int id;
	printf("请输入PID:");
	scanf("%d",&id);
	if(Run->next == NULL){
		printf("队列空!\n");
		return;
	}else {
		PCB*p = Run->next;
		PCB*q = Run;
		 while(p && (p->pid != id)){
            q = p;
            p = p->next;
        }
        if(!p){
        	printf("无此进程!\n");
			return;	
		}
		q->next = p->next;
        p->next = NULL;
        PCB* pp = Wait;
        while(pp->next){
        	pp=pp->next;
		}
		pp->next=p;
		p->next=NULL;
        if(Run->next==NULL){
            if(Ready->next!=NULL){
                q=Ready->next;
                p=q->next;
                Ready->next=p;
                q->next=NULL;
                pp = Run;
                while(pp->next){
        		pp=pp->next;
		}
		pp->next=q;
		}
            }
	}
}
void wakeup(){
	int id;
	printf("请输入PID:");
	scanf("%d",&id);
	if(Wait->next==NULL){
		printf("队列空!\n");
		return;
	}else{
		PCB*p = Wait->next;
		PCB*q = Wait;
		 while(p && (p->pid != id)){
            q = p;
            p = p->next;
        }
        if(!p){
        	printf("无此进程!\n");
			return;	
		}
		q->next = p->next;
        p->next = NULL;
        PCB* pp = Ready;
        while(pp->next){
        	pp=pp->next;
		}
		pp->next=p;
		p->next=NULL;
		if(Run->next==NULL){
				q=Ready->next;
                p=q->next;
                Ready->next=p;
                q->next=NULL;
                pp = Run;
                while(pp->next){
        		pp=pp->next;
		}
		pp->next=q;
		}
	}
}
void destroy(PCB* head,int pid) {
    if(head->next!=NULL){
    PCB* p = head->next;
    PCB* q = head;
    while(p && (p->pid != pid)) {
        q = p;
        p = p->next;
    }
    if(p==NULL)
        return;
    q->next = p->next;
    p->next = NULL;
    free(p);
    }
}
void kill(){
	int id;
	PCB* p;
	PCB* pp;
    PCB* q;
	printf("请输入PID:");
	scanf("%d",&id);
	destroy(Run,id);
	destroy(Ready,id);
	destroy(Wait,id);
	if(Run->next==NULL){
		if(Ready->next!=NULL){
			q=Ready->next;
                p=q->next;
                Ready->next=p;
                q->next=NULL;
                pp = Run;
                while(pp->next){
        		pp=pp->next;
		}
		pp->next=q;
		}
	}
}
void menu()
{
   int selectItem;
   while(1)
   {
	   printf("*******************\n");
	   printf("1-----创建进程\n");
	   printf("2-----阻塞进程\n");
	   printf("3-----唤醒进程\n");
	   printf("4-----撤销进程\n");
	   printf("5-----显示效果\n");
	   printf("6-----退出系统\n");
	   printf("*******************\n");
	   printf("请选择一个菜单项：(1-6)");
	   scanf("%d",&selectItem);
       if(selectItem>=1 && selectItem<=6)
	   {

		   switch(selectItem)
		   {
			 case 1:
					   create();
					   break;
			 case 2:
					   block();
					   break;
			 case 3:
					  wakeup();
					  break;
			 case 4: 
					  kill();
					  break;
			 case 5:  
					  printf("Ready队列:\n");
					  display(Ready);
					  printf("Run队列:\n");
					  display(Run);
					  printf("Wait队列:\n");
					  display(Wait);
					  break;
			 case 6:
					 exit(0);

		   }
	   }
	    
   }
}
int  main()
{
   
   Run=(PCB*)malloc(sizeof(PCB));
   Run->next=NULL;
   Ready=(PCB*)malloc(sizeof(PCB));
   Ready->next=NULL;
   Wait=(PCB*)malloc(sizeof(PCB));
   Wait->next=NULL;
   menu();
}
