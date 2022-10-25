#include<stdio.h>
#include<stdlib.h>
struct nodespace{
int teskid;   //任务号 
int begin;    //开始地址 
int size;     //大小 
int status;   //状态 0代表占用，1代表空闲 
struct nodespace *next;  //指针 
};
 
void initNode(struct nodespace *p){//初始化
if(p == NULL){	//如果为空则新创建一个 
p = (struct nodespace*)malloc(sizeof(struct nodespace));
}
p->teskid = -1;
p->begin = 0;
p->size = 1024;
p->status = 1;
p->next =NULL; 
}
 
/*
* 最佳适应算法 
*/
void myMalloc2(int teskid,int size,struct nodespace *node){
//最佳块指针 
struct nodespace *q = NULL;
struct nodespace *p = NULL;
//首先找到第一个满足条件的空闲块 
while(node != NULL){
if(node->status == 1 && node->size >= size){
q = node;
break;
}
//如果下一个为空则说明没有空闲区可以分配 
if(node->next == NULL){
printf("分配失败，没有足够的空间！\n");
break;	
} else{			
node = node->next;		
}	
} 
	
//遍历寻找最佳的空闲块 	
while(node != NULL){		
if(node->status == 1 && node->size >= size && node->size < q->size){  //空闲的空间	
q = node;	
}
	
node = node->next;
}
if(q->size > size){  			//最佳空闲块的大小大于需求大小 
		//分配后剩余的空间 
p = (struct nodespace*)malloc(sizeof(struct nodespace));
p->begin = q->begin + size;	
p->size = q->size - size;	
p->status = 1;	
p->teskid = -1;//分配的空间	
q->teskid = teskid; 
q->size = size;
q->status = 0;
//改变节点的连接 
p->next = q->next; 
q->next = p;
}else if(q->size == size){  	//最佳空闲块空间大小和需求相等
q->teskid = teskid; 
q->size = size;
q->status = 0;
}		
}
 
void myFree(int teskid,struct nodespace *node){
struct nodespace *q;
if(node->next == NULL && node->teskid == -1){
printf("还没有分配任何任务！\n");
}
	
while(node != NULL){
if(node->status == 1 && node->next->status ==0 && node->next->teskid == teskid){  //释放空间的上一块空间空闲时 
node->size = node->size + node->next->size;
q = node->next;
node->next = node->next->next;
free(&q);
if(node->next->status == 1){ //下一个空间是空闲空间时 
node->size = node->size + node->next->size;
q = node->next;
node->next = node->next->next;
free(&q);
}
break;
}else if(node->status == 0 && node->teskid == teskid){  //释放空间和空闲空间不连续时 
node->status = 1;
node->teskid = -1;
if(node->next != NULL && node->next->status == 1){ //下一个空间是空闲空间时 
node->size = node->size + node->next->size;
q = node->next;
node->next = node->next->next;
free(&q);
}
break;
}else if(node->next == NULL){  //任务id不匹配时 
printf("没有此任务！\n");
break;
}
node = node->next;
}
	
	 
}
 
void printNode(struct nodespace *node){
printf("                        内存情况                        \n"); 
printf(" -------------------------------------------------------\n");
printf("| 起始地址\t结束地址\t大小\t状态\t任务id\t|\n");
while(node != NULL){
if(node->status==1){
printf("| %d\t\t%d\t\t%dKB\tfree\t 无\t|\n", node->begin + 1, node->begin+node->size, node->size);
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
printf("1.分配内存\n");
printf("2.回收内存\n");
printf("3.查看内存情况\n");
printf("4.退出\n");
printf("请输入选项:");
}
 
int main(){
	// node为整个空间 
struct nodespace *init = (struct nodespace*)malloc(sizeof(struct nodespace));
struct nodespace *node = NULL;
int option=0;
int teskid;
int size;
int n=0;

initNode(init);			//初始化主链 
node = init; 			//指向链表头 
while(1){//不断循环最佳适应		
while(1){//循环操作
menu();//显示操作选项
scanf("%d",&option);
if(option == 1){	//申请内存 
printf("请输入任务id以及申请的空间大小:\n");
scanf("%d%d",&teskid,&size);
myMalloc2(teskid,size,node);
printNode(node);
}else if(option == 2){//退还内存
printf("请输入任务id:\n");
scanf("%d",&teskid);
myFree(teskid,node);
printNode(node);
}else if(option == 3){//查看内存分配现状
printNode(node);
}else if(option == 4){//退出
destory(node);	//销毁链表
initNode(init);	//重新初始化 
node = init;	//重新指向开头 
break;
}else{
printf("您的输入有误，请重新输入！\n");
continue;
}
}
} 
return 0;
}