

#include"2.h"

float fnDistance(Node a,Node b)//�������ڵ��ŷʽ����
{
	float d;
	d=(a.a-b.a)*(a.a-b.a)+(a.b-b.b)*(a.b-b.b)+(a.c-b.c)*(a.c-b.c)+(a.d-b.d)*(a.d-b.d);
	return d;	
}


void fnInput(pNode p,int num)  //���ж�ȡ���ַ��������ݣ�numΪ������������
{//��������;data[150]//OK
	char chars;
	int i;

	char datainput[20];
	cout <<"\n�����ļ���:  ";
	cin >>datainput;
	ifstream myf(datainput,ios::nocreate);//�ļ�

	char linetemp[100];
	if(myf.fail())
	{
		cout<<"Sorry ,Cann't open the file"<<endl;
	}
	else
	{//���ļ�
		i=0;  //���ж�ȡ���ݣ�0,1,2....
		while(!myf.eof())
		{
			myf.getline(linetemp,100,';');
			//cin.getline(�ַ�ָ��,�ַ�����N,������);
			//�����ǣ�һ�ζ�ȡ����ַ�(�����հ��ַ�����ֱ������N-1������������ָ���Ľ�����Ϊֹ(Ĭ�ϵ�����'\n'������

			istrstream str(linetemp); 

			/*
			istrstream ���Ǵ� istream �������ģ������������ı���ת��Ϊ��������Ҫ���ڲ���ʽ��
			istrstream ��Ĺ��캯����������istrstream::istrstream(char *s) �� istrstream::istrstream(char *s,int n);
			����˵��������һ������ s ��һ���ַ�ָ����ַ����飬ʹ�øô�����ʼ��Ҫ������������
			�� n ��ʾʹ��ǰ n ���ַ�������������
			*/

			str>>p[i].a>>chars>>p[i].b>>chars>>p[i].c>>chars>>p[i].d>>chars;
			i++;
		}
	}
}


void fnOutput(int *position,pNode data,int data_num) //data_numΪ������ 
{//�������Ϊ.txt�ļ�

	char dataoutput[20];
	cout <<"\n����ļ���:  ";
	cin >>dataoutput;
	ofstream omyf(dataoutput,ios::out,filebuf::sh_read);//�ļ�

	if(omyf.fail())
	{
		cout<<"Sorry ,Cann't open the file"<<endl;
	}
	else
	{//����ļ�
		for(int i=0;i<NUM;i++)  //NUMΪ�������ĸ���
		{
			omyf<<i<<"----------------------------------------------\n";
			for(int j=0;j<data_num;j++)
			if(position[j]==i)  //jΪ�ѷ�����
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
{//�������Ⱦ���
	int j,i,numerator=10;
	float temps=0;
	float  d[NUM];//����
	for( j=0;j<YB_number;j++)
	{//ÿһ������
		for(i=0;i<NUM;i++)
		{
			d[i]=fnDistance(v[i],data[j]);//����������data[j]��ÿ�������ĵľ���
		}
		for(int ii=0;ii<NUM;ii++)
		{//����data[j]��ÿһ��������������
			temps=0.0;
			for(int jj=0;jj<NUM;jj++)
			{
				if(d[jj]==0.0)
				{//�о���Ϊ��ʱ
					if(jj==ii)
					{//���ӣ���ĸ��Ϊ��ʱ������Ϊ1��
						temps=1.0;
					}
					else
					{//���ӡ���ĸ��ͬʱΪ����˵������һ�㲻��������࣬������Ϊ����
						numerator=-10;
					}
					break;
				}
				else
				{//���ӷ�ĸȫ��Ϊ��ʱ��
					//temps=temps+d[ii]/d[jj];//Դ���򣺼��������ȵķ�ĸ����
					temps=temps+(d[ii]/d[jj])*(d[ii]/d[jj]);//���������ȵķ�ĸ���֣���Ϊ����m=2������2/(m-2)=2��
				}
			}

			//data[j]����ii�������ĵ�������
			if(numerator==-10)
			{//���ӡ���ĸ��ͬΪ����˵������һ�㲻��������࣬������Ϊ����
				lishu[ii][j]=0;
				numerator=10;
			}
			else
			{
				lishu[ii][j]=1/temps;//�����j���������ڵ�ii���������ֵ
			}		
		}//����data[j]��ÿһ��������������
	}///ÿһ������
}

void  fnCCenter(float lishu[][YB_number],pNode data,pNode v1)  //v1Ϊ�������Ľڵ�
{//����������
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
			E_ux.a=E_ux.a+lishu[i][j]*lishu[i][j]*data[j].a;//����������ĵķ��Ӳ��֣���Ȩ����m=2
			E_ux.b=E_ux.b+lishu[i][j]*lishu[i][j]*data[j].b; 
			E_ux.c=E_ux.c+lishu[i][j]*lishu[i][j]*data[j].c; 
			E_ux.d=E_ux.d+lishu[i][j]*lishu[i][j]*data[j].d; 
			E_u=E_u+lishu[i][j]*lishu[i][j];   //�����ĸ����
		}
		v1[i].a=E_ux.a/E_u;  //�����i���������ĵĵ�һ��������ֵ
		v1[i].b=E_ux.b/E_u;
		v1[i].c=E_ux.c/E_u;
		v1[i].d=E_ux.d/E_u;
	}
}


