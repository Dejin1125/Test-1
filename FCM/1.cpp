
#include"2.h"
#define YB_number 150 
void main()
{
//��ʼ��:
	int    k=0;             //ͳ�Ƶ�������
	Node   data[YB_number];		//����
	float  lishu[NUM][YB_number]; //�����Ⱦ��������ĸ������У��������ݸ���
	Node   v[NUM];          //��������;
	Node   v1[NUM];         //��������
	int    i,j;				//ѭ������
	float max,temps;
//����:
	fnInput(data,YB_number);   //�������ݵĶ���
	memcpy(v1,data,sizeof(Node)*NUM); //ǰ����������Ϊ��ʼ�������ģ�����������ô����

	//void *memcpy(void *dest, const void *src, size_t n);
	//��Դsrc��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����n���ֽڵ�Ŀ��dest��ָ���ڴ��ַ����ʼλ����

//����:
	int numerator=10;//�����ǲ���Ϊ0,��Ϊ10ʱ��Ϊ0,��Ϊ-10ʱ,��ĸΪ0
	k=0;
	do{
		memcpy(v,v1,sizeof(Node)*NUM);    //�����ĸ���

		fnLishu(data,v1,lishu);            //�����ȣ�//��ǰ����������Ϊ��ʼ�������ģ�Ȼ���ʼ�������Ⱦ���

		fnCCenter(lishu,data,v1);         //���������ģ�

		max=(float)sqrt(fnDistance(v[0],v1[0]));

		for(i=1;i<NUM;i++)
		{//����max��E���,���ж��Ƿ�Ҫ����ѭ��
			temps=(float)sqrt(fnDistance(v[i],v1[i]));	
			if(max<temps)
			{
				max=temps;
			}
		}
		k++;//k��¼�����˶��ٴ�ѭ��
	}while(max>E);

	cout<<"���������"<<k<<"��ѭ��"<<endl;
	cout<<"������Ϊ:"<<endl;
	for(i=0;i<NUM;i++)
	{
		cout<<"("<<v1[i].a<<" "<<v1[i].b<<" "<<v1[i].c<<" "<<v1[i].d<<")"<<endl;
	}
	memcpy(v,v1,sizeof(Node)*NUM);
	fnLishu(data,v,lishu);					//�����ļ������:����������

	float dddd;
	int position[YB_number];	//��ʼÿһ������Ϊһ��
	for(j=0;j<YB_number;j++)
	{ 
		dddd=lishu[0][j];//ÿһ���������ڵ�һ���������ֵ
		position[j]=0;//Ĭ��Ϊ��һ��
		for(i=1;i<NUM;i++)
		{
			if(dddd<lishu[i][j])//ѡȡ�����Ⱦ���ÿ�����ֵ��Ȼ���Ϊ����
			{
				dddd=lishu[i][j];
				position[j]=i;	//��j���������ڵ�i��		
			}
		}
	}
//���:
	cout<<"  �Ƿ񱣴��TXT�ļ�(Y/N)?"<<endl;
	char ch;
	cin>>ch;
	if(ch=='Y'||ch=='y')
	{
		fnOutput(position,data,YB_number);
	}	
	//getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
















