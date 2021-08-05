#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;						/*表示区间[i,j]*/
	int cover;						/*覆盖该区间的线段的条数*/
	struct node *lchild,*rchild;	/*左、右孩子指针*/
} ITree;
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
void InsTree(ITree *r,int a,int b)	/*在线段树r中插入[a,b]*/
{
	int mid;
	if (a<=r->i && r->j<=b)				/*找到该区间,覆盖线段数增1*/
		r->cover++;
	else								/*不是要找的区间*/
	{
		mid=(r->i+r->j)/2;				/*求中间位置mid*/
		if (b<=mid) 
			InsTree(r->lchild,a,b);		/*在左子树中插入[a,b]*/
		else if (mid<=a) 
			InsTree(r->rchild,a,b);		/*在右子树中插入[a,b]*/
		else
		{
			InsTree(r->lchild,a,mid);	/*在左子树中插入[a,mid]*/
			InsTree(r->rchild,mid,b);	/*在右子树中插入[mid,b]*/
		}
	}
}
void DelTree(ITree *r,int a,int b)	/*在线段树r中删除[a,b]*/
{
	int mid;
	if (a<=r->i && r->j<=b)				/*找到该区间,覆盖线段数减1*/
		r->cover--;
	else								/*不是要找的区间*/
	{
		mid=(r->i+r->j)/2;				/*求中间位置mid*/
		if (b<=mid) 
			DelTree(r->lchild,a,b);		/*在左子树中删除[a,b]*/
		else if (mid<=a) 
			DelTree(r->rchild,a,b);		/*在右子树中删除[a,b]*/
		else
		{
			DelTree(r->lchild,a,mid);	/*在左子树中删除[a,mid]*/
			DelTree(r->rchild,mid,b);	/*在右子树中删除[mid,b]*/
		}
	}
}
int Count(ITree *r)		/*计算线段树r的测度*/
{
	if (r->cover>0)
		return(r->j-r->i);	/*该结点cover大于0*/
	else if (r->j-r->i==1)	/*是叶子结点*/
		return(0);
	else 
		return(Count(r->lchild)+Count(r->rchild));/*计算左右子树的测度*/
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
void fun()
{
	ITree *r;
	r=CreateTree(1,10);
	printf("线段树:\n");DispTree(r);
	InsTree(r,3,6);
	InsTree(r,7,9);
	printf("插入[3,6]和[7,9]线段,Count=%d\n",Count(r));
	DelTree(r,4,5);
	DelTree(r,7,8);
	printf("线段树:\n");DispTree(r);
	printf("删除[4,5]和[7,8]线段,Count=%d\n",Count(r));
	InsTree(r,1,5);
	printf("插入[1,5]线段,Count=%d\n",Count(r));
	DelTree(r,4,6);
	printf("删除[4,6]线段,Count=%d\n",Count(r));
}
void main()
{
	fun();
}
