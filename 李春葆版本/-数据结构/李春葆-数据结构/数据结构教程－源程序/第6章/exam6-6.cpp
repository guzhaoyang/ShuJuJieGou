#include <stdio.h>
#define MaxSize 1000
int akm(int m,int n)
{
	int g;
	if (m==0) 
		return(n+1);
	else if	(n==0)
		return akm(m-1,1);
	else
	{	
		g=akm(m,n-1);
		return(akm(m-1,g));
	}
}

int akm1(int m,int n)
{
	struct 
	{	int m,n;						/*�ֱ𱣴�m��nֵ*/
		int f;							/*����akm(m,n)ֵ*/
		int tag;						/*��ʶ�Ƿ����akm(m,n)ֵ*/
		int trans;						/*ָ���ֽ�������*/
	} St[MaxSize];						/*����ջ*/
	int top=-1;							/*ջָ��*/
	int v;
	top++;								/*��ֵ��ջ*/
	St[top].m=m;St[top].n=n;
	St[top].tag=0;
	printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
	while (top>-1)						/*ջ����ʱѭ��*/
	{	
		if (St[top].tag==0)				/*δ�����ջ��Ԫ�ص�fֵ*/
		{	
			if (St[top].m==0)			/*����(1)ʽ,ֱ���������ֵ*/
			{	
				St[top].f=St[top].n+1;
				St[top].tag=1;			/*����ֵ�����*/
			}
			else if (St[top].m!=0 && St[top].n==0)	/*����(2)ʽ����*/
			{	
				top++;					/*��akm(m-1,1)��ջ*/
				St[top].m=St[top-1].m-1;
				St[top].n=1;
				St[top].tag=0;			/*����ֵδ���*/
				St[top].trans=1;		/*�ֽ����1*/
				printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
			}
			else if (St[top].m!=0 && St[top].n!=0)	/*����(3)ʽ����*/
			{	
				top++;					/*��akm(m,n-1)��ջ*/
				St[top].m=St[top-1].m;
				St[top].n=St[top-1].n-1;
				St[top].tag=0;			/*����ֵδ���*/
				St[top].trans=3;		/*�ֽ����3*/
				printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
			}
		}
		else if (St[top].tag==1)		/*�Ѽ����fֵ*/
		{	
			if (St[top].trans==1)		/*ֱ����(2)ʽ���*/
			{	
				St[top-1].f=St[top].f;
				St[top-1].tag=1;		/*����ֵ�����*/
				printf("Pop:  %d  %d  %d  %d\n",St[top].m,St[top].n,St[top].f,St[top].tag);
				top--;					/*�˳�akm(m-1,1)*/
			}
			else if (St[top].trans==3)	/*����akm(m-1,v),����v=akm(m,n-1)*/
			{	
				v=St[top].f;
				m=St[top].m;
				printf("Pop:  %d  %d  %d  %d\n",St[top].m,St[top].n,St[top].f,St[top].tag);
				top--;					/*�˳�akm(m,n-1)*/
				top++;					/*��akm(m-1,v)��ջ*/
				St[top].m=m-1;
				St[top].n=v;;
				St[top].tag=0;			/*����ֵδ���*/
				St[top].trans=2;		/*�ֽ����2*/
				printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
			}
			else if (St[top].trans==2)	/*ֱ����(3)ʽ���*/
			{	
				St[top-1].f=St[top].f;
				St[top-1].tag=1;		/*����ֵ�����*/
				printf("Pop:  %d  %d  %d  %d\n",St[top].m,St[top].n,St[top].f,St[top].tag);
				top--;					/*�˳�akm(m-1,v)*/
			}
		}
		if (top==0 && St[top].tag==1) /*ջ��ֻ��һ�������f��Ԫ��ʱ�˳�ѭ��*/
			break;
	} 
	return St[top].f;
}
void main()
{
	int m=2,n=1;
	printf("akm(%d,%d)=%d\n",m,n,akm(m,n));
	printf("akm1:Stջ��Ԫ�ز�������:\n");
	printf("akm1(%d,%d)=%d\n",m,n,akm1(m,n));
}