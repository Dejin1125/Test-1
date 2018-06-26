

#include"2.h"

float fnDistance(Node a,Node b)//计算两节点的欧式距离
{
	float d;
	d=(a.a-b.a)*(a.a-b.a)+(a.b-b.b)*(a.b-b.b)+(a.c-b.c)*(a.c-b.c)+(a.d-b.d)*(a.d-b.d);
	return d;	
}


void fnInput(pNode p,int num)  //整行读取带字符串的数据，num为读入样本个数
{//输入数据;data[150]//OK
	char chars;
	int i;

	char datainput[20];
	cout <<"\n输入文件名:  ";
	cin >>datainput;
	ifstream myf(datainput,ios::nocreate);//文件

	char linetemp[100];
	if(myf.fail())
	{
		cout<<"Sorry ,Cann't open the file"<<endl;
	}
	else
	{//读文件
		i=0;  //逐行读取数据，0,1,2....
		while(!myf.eof())
		{
			myf.getline(linetemp,100,';');
			//cin.getline(字符指针,字符个数N,结束符);
			//功能是：一次读取多个字符(包括空白字符），直到读满N-1个，或者遇到指定的结束符为止(默认的是以'\n'结束）

			istrstream str(linetemp); 

			/*
			istrstream 类是从 istream 类派生的，它是用来将文本项转换为变量所需要的内部格式。
			istrstream 类的构造函数有两个：istrstream::istrstream(char *s) 和 istrstream::istrstream(char *s,int n);
			参数说明：⒈第一个参数 s 是一个字符指针或字符数组，使用该串来初始化要创建的流对象。
			⒉ n 表示使用前 n 个字符来构造流对象。
			*/

			str>>p[i].a>>chars>>p[i].b>>chars>>p[i].c>>chars>>p[i].d>>chars;
			i++;
		}
	}
}


void fnOutput(int *position,pNode data,int data_num) //data_num为样本数 
{//输出数据为.txt文件

	char dataoutput[20];
	cout <<"\n输出文件名:  ";
	cin >>dataoutput;
	ofstream omyf(dataoutput,ios::out,filebuf::sh_read);//文件

	if(omyf.fail())
	{
		cout<<"Sorry ,Cann't open the file"<<endl;
	}
	else
	{//输出文件
		for(int i=0;i<NUM;i++)  //NUM为聚类中心个数
		{
			omyf<<i<<"----------------------------------------------\n";
			for(int j=0;j<data_num;j++)
			if(position[j]==i)  //j为已分类编号
			{
				omyf<<data[j].a<<","<<data[j].b<<","
					<<data[j].c<<","<<data[j].d<<";\n";
			}
			omyf<<"-----------------------------------------------------\n";
		}
		omyf.close();
	}
}


void  fnLishu(pNode data,pNode v,float lishu[][YB_number])  
{//求隶属度矩阵
	int j,i,numerator=10;
	float temps=0;
	float  d[NUM];//距离
	for( j=0;j<YB_number;j++)
	{//每一个样本
		for(i=0;i<NUM;i++)
		{
			d[i]=fnDistance(v[i],data[j]);//计算样本点data[j]到每个类中心的距离
		}
		for(int ii=0;ii<NUM;ii++)
		{//计算data[j]到每一个类中心隶属度
			temps=0.0;
			for(int jj=0;jj<NUM;jj++)
			{
				if(d[jj]==0.0)
				{//有距离为０时
					if(jj==ii)
					{//分子．分母都为０时隶属度为1；
						temps=1.0;
					}
					else
					{//分子　分母不同时为０，说明，这一点不属于这个类，隶属度为０；
						numerator=-10;
					}
					break;
				}
				else
				{//分子分母全不为０时，
					//temps=temps+d[ii]/d[jj];//源程序：计算隶属度的分母部分
					temps=temps+(d[ii]/d[jj])*(d[ii]/d[jj]);//计算隶属度的分母部分（因为觉得m=2，所以2/(m-2)=2）
				}
			}

			//data[j]到第ii个类中心的隶属度
			if(numerator==-10)
			{//分子　分母不同为０，说明，这一点不属于这个类，隶属度为０；
				lishu[ii][j]=0;
				numerator=10;
			}
			else
			{
				lishu[ii][j]=1/temps;//计算第j个样本属于第ii类的隶属度值
			}		
		}//计算data[j]到每一个类中心隶属度
	}///每一个样本
}

void  fnCCenter(float lishu[][YB_number],pNode data,pNode v1)  //v1为聚类中心节点
{//计算类中心
	int i,j;
	float E_u=0;
	Node E_ux;
	for(i=0;i<NUM;i++)
	{
		E_u=0.0;
		E_ux.a=0.0;
		E_ux.b=0.0;
		E_ux.c=0.0;
		E_ux.d=0.0;
		for(j=0;j<YB_number;j++)
		{
			E_ux.a=E_ux.a+lishu[i][j]*lishu[i][j]*data[j].a;//计算聚类中心的分子部分，加权参数m=2
			E_ux.b=E_ux.b+lishu[i][j]*lishu[i][j]*data[j].b; 
			E_ux.c=E_ux.c+lishu[i][j]*lishu[i][j]*data[j].c; 
			E_ux.d=E_ux.d+lishu[i][j]*lishu[i][j]*data[j].d; 
			E_u=E_u+lishu[i][j]*lishu[i][j];   //计算分母部分
		}
		v1[i].a=E_ux.a/E_u;  //计算第i个聚类中心的第一个分量的值
		v1[i].b=E_ux.b/E_u;
		v1[i].c=E_ux.c/E_u;
		v1[i].d=E_ux.d/E_u;
	}
}


