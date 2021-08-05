#include <stdio.h>
#define MaxSize 100
struct
{	int n;			/*保存n值*/
	int f;			/*保存fun2(n)值*/
	int tag;		/*标识是否求出fun2(n)值,1:未求出,0:已求出*/
} St[MaxSize];		/*定义栈*/
int top=-1;
int fun2(int n)
{
	top++;				/*初值进栈*/
	St[top].n=n;
	St[top].tag=1;
	while (top>-1)		/*栈不空时循环*/
	{	
		if (St[top].tag==1)					/*未计算出栈顶元素的f值*/
		{	
			if (St[top].n==1)				/*(1)式*/
			{	
				St[top].f=1;
				St[top].tag=0;
			}
			else							/*(2)式分解过程*/
			{	
				top++;
				St[top].n=St[top-1].n-1;
				St[top].tag=1;
			}
		}
		else if (St[top].tag==0)				/*已计算出f值*/
		{	
			St[top-1].f=St[top-1].n*St[top].f;	/*(2)式求值过程*/
			St[top-1].tag=0;
			top--;
		}
		if (top==0 && St[top].tag==0) /*栈中只有一个已求出f的元素时退出循环*/
			break;
	}
	return(St[top].f);
}
void main()
{
	int n=5;
	printf("%d!=%d\n",n,fun2(n));
}