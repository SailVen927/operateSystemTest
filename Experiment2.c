#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 
#define NULL 0

//定义PCB
      struct pcb{
      char name[10];//进程名
      char state;//进程状态
      int super;//优先级
      int needTime;//进程需要的总运行时间
      int alreadyUseTime;//进程已运行的时间
      struct pcb* link;//指针
      }*ready=NULL,*p; 
      typedef struct pcb  PCB;
   
	  //按优先数降序排序
     void sort(){ 
     PCB *p1, *p2; 
     int insert=0; 
      	if((ready==NULL)||((p->super)>(ready->super))){//优先级最大者，插入队首
     		 p->link=ready; 
     		 ready=p; 
     	 }else{//进程比较优先级,插入适当的位置中
      	p1=ready; 
      	p2=p1->link; 
      	while(p2!=NULL){ 
      		if((p->super)>(p2->super)){
                     p->link=p2; 
      				 p1->link=p; 
     				 p2=NULL; 
     				 insert=1;
     			 }else{
      				p1=p2->link;
      				p2=p2->link;
     			 } 
     		 }
      		if(insert==0) 
				p1->link=p;
      	} 
      } 

      //创建进程控制块PCB
      int createPCB(){
      	int i,num; 
      	printf(" 请输入进程数?"); 
     	scanf("%d",&num); 
		printf("\n");
      	for(i=0;i<num;i++){ 
           printf(" 进程编号%d:\n",i); 
           p=(PCB*)malloc(sizeof(PCB));
      	   printf(" 进程名:");            
		   scanf("%s",p->name); 
   		   printf(" 进程优先数:");        
		   scanf("%d",&p->super); 
  		   printf(" 执行进程所需时间:");      
		   scanf("%d",&p->needTime); 
     	   printf("\n"); 
   		   p->alreadyUseTime=0; 
           p->state='w';
  		   p->link=NULL;
 		   sort();
     	 } 
		return num;
      }

     //显示指定进程的PCB信息
     void disp(PCB * pr){ 
     	 printf("\n 进程名\t状态\t优先级\t运行时间\t已运行时间\n"); 
     	 printf("|%s\t",pr->name); 
     	 printf("|%c\t",pr->state); 
    	 printf("|%d\t",pr->super); 
    	 printf("|%d\t\t",pr->needTime); 
   		 printf("|%d\t",pr->alreadyUseTime); 
   		 printf("\n"); 
      } 

 //查看所有进程
 void check(){ 
       PCB* pr; 
       printf("\n当前正在运行的进程是:%s",p->name);
  	 disp(p); 
       pr=ready; 
   	   printf("\n当前就绪队列状态为:");
       while(pr!=NULL){ 
    	 disp(pr); 
    	 pr=pr->link; 
     	} 
      }

//撤消进程
void destroyPCB(){ 
     	 printf("进程 [%s] 已完成.\n",p->name); 
      	 free(p); 
      }

//当前进程运行时间到，置就绪状态
void running(){
     	 (p->alreadyUseTime)++; 
     	 if(p->alreadyUseTime==p->needTime){ 
      	 	 destroyPCB();
		 }else{ 
     		 (p->super)--;
     		 p->state='w'; 
     		 sort(); 
     	 }
      }

void main(){ 
      	int length=0;
		int cnt=0;
      	char ch; 
      	length=createPCB(); 
      	
     	while(length!=0 && ready!=NULL){
    		  cnt++;
			  printf("\n---------------------------------------------------\n");
    		  printf("当前时间片为:%d \n",cnt);
    		  p=ready;
      		  ready=p->link;
    		  p->link=NULL;
     		  p->state='R';
         	  check();
    	 	  running();
			  printf("\n---------------------------------------------------\n");
   			  printf(" 按任意键继续......"); 
     		  ch=getchar();
        }
      	printf("\n\n 所有进程都已执行完毕。\n"); 
      	ch=getchar(); 
      }