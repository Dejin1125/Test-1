
#include<iostream.h>
#include<math.h>
#include<fstream.h>
#include<strstrea.h>
#include<conio.h>
#include<memory.h>

#define YB_number 150    //������Ŀ
#define E  0.000001   //��ֵ
#define NUM  3	        //�����ĵĸ���

typedef struct node   //ÿ��������4������ֵ
{
	float a,b,c,d;
}Node,*pNode;

void fnInput(pNode p,int num);  //���ݶ���
void fnOutput(int *position,pNode data,int data_num);  //�������
float fnDistance(Node a,Node b);   //�����ڵ��ŷ����þ���
void  fnLishu(pNode data,pNode v,float lishu[][YB_number]);  //�����Ⱦ���
void  fnCCenter(float lishu[][YB_number],pNode data,pNode v1);  //��������

