#include<stdio.h>
#include<stdlib.h>
struct nodespace{
int teskid;   //����� 
int begin;    //��ʼ��ַ 
int size;     //��С 
int status;   //״̬ 0����ռ�ã�1������� 
struct nodespace *next;  //ָ�� 
};
 
void initNode(struct nodespace *p){//��ʼ��
if(p == NULL){	//���Ϊ�����´���һ�� 
p = (struct nodespace*)malloc(sizeof(struct nodespace));
}
p->teskid = -1;
p->begin = 0;
p->size = 1024;
p->status = 1;
p->next =NULL; 
}
 
/*
* �����Ӧ�㷨 
*/
void myMalloc2(int teskid,int size,struct nodespace *node){
//��ѿ�ָ�� 
struct nodespace *q = NULL;
struct nodespace *p = NULL;
//�����ҵ���һ�����������Ŀ��п� 
while(node != NULL){
if(node->status == 1 && node->size >= size){
q = node;
break;
}
//�����һ��Ϊ����˵��û�п��������Է��� 
if(node->next == NULL){
printf("����ʧ�ܣ�û���㹻�Ŀռ䣡\n");
break;	
} else{			
node = node->next;		
}	
} 
	
//����Ѱ����ѵĿ��п� 	
while(node != NULL){		
if(node->status == 1 && node->size >= size && node->size < q->size){  //���еĿռ�	
q = node;	
}
	
node = node->next;
}
if(q->size > size){  			//��ѿ��п�Ĵ�С���������С 
		//�����ʣ��Ŀռ� 
p = (struct nodespace*)malloc(sizeof(struct nodespace));
p->begin = q->begin + size;	
p->size = q->size - size;	
p->status = 1;	
p->teskid = -1;//����Ŀռ�	
q->teskid = teskid; 
q->size = size;
q->status = 0;
//�ı�ڵ������ 
p->next = q->next; 
q->next = p;
}else if(q->size == size){  	//��ѿ��п�ռ��С���������
q->teskid = teskid; 
q->size = size;
q->status = 0;
}		
}
 
void myFree(int teskid,struct nodespace *node){
struct nodespace *q;
if(node->next == NULL && node->teskid == -1){
printf("��û�з����κ�����\n");
}
	
while(node != NULL){
if(node->status == 1 && node->next->status ==0 && node->next->teskid == teskid){  //�ͷſռ����һ��ռ����ʱ 
node->size = node->size + node->next->size;
q = node->next;
node->next = node->next->next;
free(&q);
if(node->next->status == 1){ //��һ���ռ��ǿ��пռ�ʱ 
node->size = node->size + node->next->size;
q = node->next;
node->next = node->next->next;
free(&q);
}
break;
}else if(node->status == 0 && node->teskid == teskid){  //�ͷſռ�Ϳ��пռ䲻����ʱ 
node->status = 1;
node->teskid = -1;
if(node->next != NULL && node->next->status == 1){ //��һ���ռ��ǿ��пռ�ʱ 
node->size = node->size + node->next->size;
q = node->next;
node->next = node->next->next;
free(&q);
}
break;
}else if(node->next == NULL){  //����id��ƥ��ʱ 
printf("û�д�����\n");
break;
}
node = node->next;
}
	
	 
}
 
void printNode(struct nodespace *node){
printf("                        �ڴ����                        \n"); 
printf(" -------------------------------------------------------\n");
printf("| ��ʼ��ַ\t������ַ\t��С\t״̬\t����id\t|\n");
while(node != NULL){
if(node->status==1){
printf("| %d\t\t%d\t\t%dKB\tfree\t ��\t|\n", node->begin + 1, node->begin+node->size, node->size);
}else{
printf("| %d\t\t%d\t\t%dKB\tbusy\t %d\t|\n", node->begin + 1, node->begin+node->size, node->size, node->teskid);
		}
node = node->next;
	}
printf(" -------------------------------------------------------\n");
}
 
void destory(struct nodespace *node){
struct nodespace *q = node;
while(node != NULL){
node = node->next;
free(q);
q = node;
	}
}
 
void menu(){
printf("1.�����ڴ�\n");
printf("2.�����ڴ�\n");
printf("3.�鿴�ڴ����\n");
printf("4.�˳�\n");
printf("������ѡ��:");
}
 
int main(){
	// nodeΪ�����ռ� 
struct nodespace *init = (struct nodespace*)malloc(sizeof(struct nodespace));
struct nodespace *node = NULL;
int option=0;
int teskid;
int size;
int n=0;

initNode(init);			//��ʼ������ 
node = init; 			//ָ������ͷ 
while(1){//����ѭ�������Ӧ		
while(1){//ѭ������
menu();//��ʾ����ѡ��
scanf("%d",&option);
if(option == 1){	//�����ڴ� 
printf("����������id�Լ�����Ŀռ��С:\n");
scanf("%d%d",&teskid,&size);
myMalloc2(teskid,size,node);
printNode(node);
}else if(option == 2){//�˻��ڴ�
printf("����������id:\n");
scanf("%d",&teskid);
myFree(teskid,node);
printNode(node);
}else if(option == 3){//�鿴�ڴ������״
printNode(node);
}else if(option == 4){//�˳�
destory(node);	//��������
initNode(init);	//���³�ʼ�� 
node = init;	//����ָ��ͷ 
break;
}else{
printf("���������������������룡\n");
continue;
}
}
} 
return 0;
}