#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;							/*表示区间[i,j]*/
	int cover;							/*覆盖该区间的线段的条数*/
	struct node *lchild,*rchild;		/*左、右孩子指针*/
} ITree;
int Flag[MaxSize];		/*全局变量,Flag[i]=1表示出现颜色i*/
ITree *CreateTree(int a,int b)	/*由[a,b]建立线段树*/
{
	ITree *r;
	if (b<a) return(NULL);				/*区间无效返回NULL*/
	r=(ITree *)malloc(sizeof(ITree));	/*创建根结点*/
	r->i=a;r->j=b;r->cover=0;
	if (b-a>1)							/*区间长度大于1*/
	{
		r->lchild=CreateTree(a,(a+b)/2);/*递归创建左子树*/
		r->rchild=CreateTree((a+b)/2,b);/*递归创建右子树*/
	}
	else								/*区间长度等于1*/
		r->lchild=r->rchild=NULL;
	return(r);
}
void InsTree(ITree *r,int a,int b,int c)/*在线段树r中插入[a,b],颜色为c*/
{
	int mid;
	if (r==NULL) return;				/*空树,返回*/
	if (a<=r->i && r->j<=b)				/*[a,b]包含该区间,颜色置为c*/
		r->cover=c;
	else								/*[a,b]不包含该区间*/
	{
		if (r->cover>=0)				/*该区间已染颜色*/
		{
			if (r->lchild!=NULL)		/*其左孩子置为原颜色*/
				r->lchild->cover=r->cover;	
			if (r->rchild!=NULL)		/*其右孩子置为原颜色*/
				r->rchild->cover=r->cover;	
			r->cover=-1;				/**r结点置为多种颜色*/
		}
		mid=(r->i+r->j)/2;				/*求中间位置mid*/
		if (b<=mid)						/*[a,b]属于*r结点的区间的前半部*/
			InsTree(r->lchild,a,b,c);	/*在左子树中插入[a,b]*/
		else if (mid<=a)				/*[a,b]属于*r结点的区间的后半部*/
			InsTree(r->rchild,a,b,c);	/*在右子树中插入[a,b]*/
		else
		{
			InsTree(r->lchild,a,mid,c);	/*在左子树中插入[a,mid]*/
			InsTree(r->rchild,mid,b,c);	/*在右子树中插入[mid,b]*/
		}
	}
}
void Cflag(ITree *r,int a,int b) 	/*用于计算Flag数组值*/
{
	int mid;
	if (r->cover>=0)			/*该结点cover大于0*/
		Flag[r->cover]=1;
	else if (b-a>1)				/*[a,b]长度大于1*/
	{
		mid=(a+b)/2;
		Cflag(r->lchild,a,mid);	/*在左子树中计算Flag数组*/
		Cflag(r->rchild,mid,b);	/*在左子树中计算Flag数组*/
	}
}

int Count(ITree *r,int a,int b) /*计算线段树r颜色总数*/
{
	int i,s=0;
	Cflag(r,a,b);		/*调用Cflag计算Flag数组*/
	for (i=0;i<=12;i++)	/*统计不同颜色数*/
		s+=Flag[i];
	return(s-1);
}
void DispTree(ITree *r)  /*以凹入表示法输出一棵线段树*/
{
	ITree *St[MaxSize],*p;
	int level[MaxSize][2],top=-1,n,i,width=4;
	char type;
	if (r!=NULL)
	{
		top++;
		St[top]=r;						/*根结点入栈*/
		level[top][0]=width;
		level[top][1]=2;				/*2表示是根*/
		while (top>-1)
		{
			p=St[top];					/*退栈并凹入显示该结点值*/
			n=level[top][0];
			switch(level[top][1])
			{
			case 0:type='L';break;		/*左结点之后输出(L)*/
			case 1:type='R';break;		/*右结点之后输出(R)*/
			case 2:type='B';break;		/*根结点之后前输出(B)*/
			}
			for (i=1;i<=n;i++)			/*其中n为显示场宽,字符以右对齐显示*/
				printf(" ");
			printf("[%2d,%2d:%2d](%c)",p->i,p->j,p->cover,type);
			for (i=n+1;i<=MaxWidth;i+=2)
				printf("--");
			printf("\n");
			top--;
			if (p->rchild!=NULL)
			{							/*将右子树根结点入栈*/
				top++;
				St[top]=p->rchild;
				level[top][0]=n+width;	/*显示场宽增width*/
				level[top][1]=1;		/*1表示是右子树*/
			}
			if (p->lchild!=NULL)
			{							/*将左子树根结点入栈*/
				top++;
				St[top]=p->lchild;
				level[top][0]=n+width;  /*显示场宽增width*/
				level[top][1]=0;        /*0表示是左子树*/
			}
		}
	}
}
void main()
{
	int i,s=0;
	ITree *r;
	r=CreateTree(1,12);
	for (i=0;i<=12;i++)	/*置初值0*/
		Flag[i]=0;
	InsTree(r,1,10,1);
	InsTree(r,4,6,2);
	InsTree(r,3,6,3);
	InsTree(r,5,8,4);
	printf("线段树:\n");DispTree(r);
	printf("颜色总数=%d\n",Count(r,1,12));
}
