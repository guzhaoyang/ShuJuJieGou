#include <stdio.h>
#define MaxSize 100
struct
{	int n;			/*����nֵ*/
	int f;			/*����fun2(n)ֵ*/
	int tag;		/*��ʶ�Ƿ����fun2(n)ֵ,1:δ���,0:�����*/
} St[MaxSize];		/*����ջ*/
int top=-1;
int fun2(int n)
{
	top++;				/*��ֵ��ջ*/
	St[top].n=n;
	St[top].tag=1;
	while (top>-1)		/*ջ����ʱѭ��*/
	{	
		if (St[top].tag==1)					/*δ�����ջ��Ԫ�ص�fֵ*/
		{	
			if (St[top].n==1)				/*(1)ʽ*/
			{	
				St[top].f=1;
				St[top].tag=0;
			}
			else							/*(2)ʽ�ֽ����*/
			{	
				top++;
				St[top].n=St[top-1].n-1;
				St[top].tag=1;
			}
		}
		else if (St[top].tag==0)				/*�Ѽ����fֵ*/
		{	
			St[top-1].f=St[top-1].n*St[top].f;	/*(2)ʽ��ֵ����*/
			St[top-1].tag=0;
			top--;
		}
		if (top==0 && St[top].tag==0) /*ջ��ֻ��һ�������f��Ԫ��ʱ�˳�ѭ��*/
			break;
	}
	return(St[top].f);
}
void main()
{
	int n=5;
	printf("%d!=%d\n",n,fun2(n));
}