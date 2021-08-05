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
	{	int m,n;						/*分别保存m和n值*/
		int f;							/*保存akm(m,n)值*/
		int tag;						/*标识是否求出akm(m,n)值*/
		int trans;						/*指出分解情况编号*/
	} St[MaxSize];						/*定义栈*/
	int top=-1;							/*栈指针*/
	int v;
	top++;								/*初值进栈*/
	St[top].m=m;St[top].n=n;
	St[top].tag=0;
	printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
	while (top>-1)						/*栈不空时循环*/
	{	
		if (St[top].tag==0)				/*未计算出栈顶元素的f值*/
		{	
			if (St[top].m==0)			/*满足(1)式,直接求出函数值*/
			{	
				St[top].f=St[top].n+1;
				St[top].tag=1;			/*函数值已求出*/
			}
			else if (St[top].m!=0 && St[top].n==0)	/*满足(2)式条件*/
			{	
				top++;					/*将akm(m-1,1)进栈*/
				St[top].m=St[top-1].m-1;
				St[top].n=1;
				St[top].tag=0;			/*函数值未求出*/
				St[top].trans=1;		/*分解情况1*/
				printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
			}
			else if (St[top].m!=0 && St[top].n!=0)	/*满足(3)式条件*/
			{	
				top++;					/*将akm(m,n-1)进栈*/
				St[top].m=St[top-1].m;
				St[top].n=St[top-1].n-1;
				St[top].tag=0;			/*函数值未求出*/
				St[top].trans=3;		/*分解情况3*/
				printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
			}
		}
		else if (St[top].tag==1)		/*已计算出f值*/
		{	
			if (St[top].trans==1)		/*直接求(2)式左边*/
			{	
				St[top-1].f=St[top].f;
				St[top-1].tag=1;		/*函数值已求出*/
				printf("Pop:  %d  %d  %d  %d\n",St[top].m,St[top].n,St[top].f,St[top].tag);
				top--;					/*退出akm(m-1,1)*/
			}
			else if (St[top].trans==3)	/*再求akm(m-1,v),其中v=akm(m,n-1)*/
			{	
				v=St[top].f;
				m=St[top].m;
				printf("Pop:  %d  %d  %d  %d\n",St[top].m,St[top].n,St[top].f,St[top].tag);
				top--;					/*退出akm(m,n-1)*/
				top++;					/*将akm(m-1,v)进栈*/
				St[top].m=m-1;
				St[top].n=v;;
				St[top].tag=0;			/*函数值未求出*/
				St[top].trans=2;		/*分解情况2*/
				printf("Push: %d  %d  *  %d\n",St[top].m,St[top].n,St[top].tag);
			}
			else if (St[top].trans==2)	/*直接求(3)式左边*/
			{	
				St[top-1].f=St[top].f;
				St[top-1].tag=1;		/*函数值已求出*/
				printf("Pop:  %d  %d  %d  %d\n",St[top].m,St[top].n,St[top].f,St[top].tag);
				top--;					/*退出akm(m-1,v)*/
			}
		}
		if (top==0 && St[top].tag==1) /*栈中只有一个已求出f的元素时退出循环*/
			break;
	} 
	return St[top].f;
}
void main()
{
	int m=2,n=1;
	printf("akm(%d,%d)=%d\n",m,n,akm(m,n));
	printf("akm1:St栈中元素操作过程:\n");
	printf("akm1(%d,%d)=%d\n",m,n,akm1(m,n));
}