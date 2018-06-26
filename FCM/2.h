
#include<iostream.h>
#include<math.h>
#include<fstream.h>
#include<strstrea.h>
#include<conio.h>
#include<memory.h>

#define YB_number 150    //样本数目
#define E  0.000001   //阀值
#define NUM  3	        //类中心的个数

typedef struct node   //每个样本点4个属性值
{
	float a,b,c,d;
}Node,*pNode;

void fnInput(pNode p,int num);  //数据读入
void fnOutput(int *position,pNode data,int data_num);  //数据输出
float fnDistance(Node a,Node b);   //两个节点的欧几里得距离
void  fnLishu(pNode data,pNode v,float lishu[][YB_number]);  //隶属度矩阵
void  fnCCenter(float lishu[][YB_number],pNode data,pNode v1);  //聚类中心

