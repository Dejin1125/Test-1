
#include"2.h"
#define YB_number 150 
void main()
{
//初始化:
	int    k=0;             //统计迭代次数
	Node   data[YB_number];		//样本
	float  lishu[NUM][YB_number]; //隶属度矩阵，类中心个数个行，样本数据个列
	Node   v[NUM];          //工作中心;
	Node   v1[NUM];         //聚类中心
	int    i,j;				//循环计数
	float max,temps;
//输入:
	fnInput(data,YB_number);   //样本数据的读入
	memcpy(v1,data,sizeof(Node)*NUM); //前三个样本作为初始聚类中心？？？这样好么？？

	//void *memcpy(void *dest, const void *src, size_t n);
	//从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中

//处理:
	int numerator=10;//分子是不是为0,当为10时不为0,当为-10时,分母为0
	k=0;
	do{
		memcpy(v,v1,sizeof(Node)*NUM);    //类中心复制

		fnLishu(data,v1,lishu);            //隶属度，//把前三个样本作为初始聚类中心，然后初始化隶属度矩阵

		fnCCenter(lishu,data,v1);         //计算类中心：

		max=(float)sqrt(fnDistance(v[0],v1[0]));

		for(i=1;i<NUM;i++)
		{//计算max与E相比,来判断是否还要继续循环
			temps=(float)sqrt(fnDistance(v[i],v1[i]));	
			if(max<temps)
			{
				max=temps;
			}
		}
		k++;//k记录进行了多少次循环
	}while(max>E);

	cout<<"计算进行了"<<k<<"次循环"<<endl;
	cout<<"类中心为:"<<endl;
	for(i=0;i<NUM;i++)
	{
		cout<<"("<<v1[i].a<<" "<<v1[i].b<<" "<<v1[i].c<<" "<<v1[i].d<<")"<<endl;
	}
	memcpy(v,v1,sizeof(Node)*NUM);
	fnLishu(data,v,lishu);					//类中心计算出后:再求隶属度

	float dddd;
	int position[YB_number];	//初始每一个样本为一类
	for(j=0;j<YB_number;j++)
	{ 
		dddd=lishu[0][j];//每一个样本对于第一类的隶属度值
		position[j]=0;//默认为第一类
		for(i=1;i<NUM;i++)
		{
			if(dddd<lishu[i][j])//选取隶属度矩阵每列最大值，然后归为该类
			{
				dddd=lishu[i][j];
				position[j]=i;	//第j个样本属于第i类		
			}
		}
	}
//输出:
	cout<<"  是否保存成TXT文件(Y/N)?"<<endl;
	char ch;
	cin>>ch;
	if(ch=='Y'||ch=='y')
	{
		fnOutput(position,data,YB_number);
	}	
	//getch();//从控制台读取一个字符，但不显示在屏幕上
}
















