#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 
#define NULL 0

//����PCB
      struct pcb{
      char name[10];//������
      char state;//����״̬
      int super;//���ȼ�
      int needTime;//������Ҫ��������ʱ��
      int alreadyUseTime;//���������е�ʱ��
      struct pcb* link;//ָ��
      }*ready=NULL,*p; 
      typedef struct pcb  PCB;
   
	  //����������������
     void sort(){ 
     PCB *p1, *p2; 
     int insert=0; 
      	if((ready==NULL)||((p->super)>(ready->super))){//���ȼ�����ߣ��������
     		 p->link=ready; 
     		 ready=p; 
     	 }else{//���̱Ƚ����ȼ�,�����ʵ���λ����
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

      //�������̿��ƿ�PCB
      int createPCB(){
      	int i,num; 
      	printf(" �����������?"); 
     	scanf("%d",&num); 
		printf("\n");
      	for(i=0;i<num;i++){ 
           printf(" ���̱��%d:\n",i); 
           p=(PCB*)malloc(sizeof(PCB));
      	   printf(" ������:");            
		   scanf("%s",p->name); 
   		   printf(" ����������:");        
		   scanf("%d",&p->super); 
  		   printf(" ִ�н�������ʱ��:");      
		   scanf("%d",&p->needTime); 
     	   printf("\n"); 
   		   p->alreadyUseTime=0; 
           p->state='w';
  		   p->link=NULL;
 		   sort();
     	 } 
		return num;
      }

     //��ʾָ�����̵�PCB��Ϣ
     void disp(PCB * pr){ 
     	 printf("\n ������\t״̬\t���ȼ�\t����ʱ��\t������ʱ��\n"); 
     	 printf("|%s\t",pr->name); 
     	 printf("|%c\t",pr->state); 
    	 printf("|%d\t",pr->super); 
    	 printf("|%d\t\t",pr->needTime); 
   		 printf("|%d\t",pr->alreadyUseTime); 
   		 printf("\n"); 
      } 

 //�鿴���н���
 void check(){ 
       PCB* pr; 
       printf("\n��ǰ�������еĽ�����:%s",p->name);
  	 disp(p); 
       pr=ready; 
   	   printf("\n��ǰ��������״̬Ϊ:");
       while(pr!=NULL){ 
    	 disp(pr); 
    	 pr=pr->link; 
     	} 
      }

//��������
void destroyPCB(){ 
     	 printf("���� [%s] �����.\n",p->name); 
      	 free(p); 
      }

//��ǰ��������ʱ�䵽���þ���״̬
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
    		  printf("��ǰʱ��ƬΪ:%d \n",cnt);
    		  p=ready;
      		  ready=p->link;
    		  p->link=NULL;
     		  p->state='R';
         	  check();
    	 	  running();
			  printf("\n---------------------------------------------------\n");
   			  printf(" �����������......"); 
     		  ch=getchar();
        }
      	printf("\n\n ���н��̶���ִ����ϡ�\n"); 
      	ch=getchar(); 
      }