#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;						/*表示区间[i,j]*/
	int cover;						/*该区间是否被覆盖*/
	int bj;							/*该区间的标记*/
	struct node *lchild,*rchild;	/*左、右孩子指针*/
} ITree;
ITree *CreateTree(int a,int b)	/*由[a,b]建立线段树*/
{
	ITree *r;
	if (b<a) return(NULL);				/*区间无效返回NULL*/
	r=(ITree *)malloc(sizeof(ITree));	/*创建根结点*/
	r->i=a;r->j=b;
	r->cover=0;r->bj=0;
	if (b-a>1)							/*区间长度大于1*/
	{
		r->lchild=CreateTree(a,(a+b)/2);/*递归创建左子树*/
		r->rchild=CreateTree((a+b)/2,b);/*递归创建右子树*/
	}
	else								/*区间长度等于1*/
		r->lchild=r->rchild=NULL;
	return(r);
}
void Clean(ITree *&p)  /*更新标记的过程*/
{
	p->cover=0;			/*当前结点改为未覆盖*/
	p->bj=0;			/*当前结点的bj置为0*/
	p->lchild->bj=-1;	/*左孩子结点的bj置为-1*/
	p->rchild->bj=-1;	/*右孩子结点的bj置为-1*/
}
void InsTree(ITree *r,int a,int b)	/*在线段树r中插入[a,b]*/
{
	int mid;
	if (r->bj==-1) Clean(r);			/*若*r结点被标记则更新*/
	if (r->cover==1) return;			/*若该区间已被涂色,退出过程*/
	if (a<=r->i && b>=r->j)				/*[a,b]包含当前区间*/
	{
		r->cover=1;
		return;
	}
	mid=(r->i+r->j)/2;					/*求中间位置mid*/
	if (a<mid) InsTree(r->lchild,a,b);	/*在左子树中插入[a,b]*/
	if (b>mid) InsTree(r->rchild,a,b);	/*在右子树中插入[a,b]*/
}
void DelTree(ITree *r,int a,int b)		/*在线段树r中删除[a,b]*/
{
	int mid;
	if (r->bj==-1) return;	/*若线段被标记,说明该线段已不复存在,无需再进行删除,退出过程*/
	if (a<=r->i && b>=r->j)	/*[a,b]包含当前区间*/
	{
		r->cover=0;
		r->lchild->bj=-1;	/*把区问已被删除的信息传给左孩子*/
		r->rchild->bj=-1;	/*把区问已被删除的信息传给右孩子*/
		return;
	}
	if (r->cover==1)	/*若该线段是被涂了色的*/
	{
		r->cover=0;
		r->lchild->bj=-1;	/*把区问已被删除的信息传给左孩子,先删除*/
		r->rchild->bj=-1;	/*把区问已被删除的信息传给右孩子,先删除*/
		if (r->i<a) InsTree(r,r->i,a);	/*再插入*/
		if (b<r->j) InsTree(r,b,r->j);
	}
	else  /*否则继续对左右儿子调用删除过程*/
	{
		mid=(r->i+r->j)/2;			/*求中间位置k*/
		if (a<mid) DelTree(r->lchild,a,b);	/*在左子树中删除[a,b]*/
		if (b<mid) DelTree(r->rchild,a,b);	/*在右子树中删除[a,b]*/
	}
}
int Calculate(ITree *r)		/*计算被覆盖的单位线段条数*/
{
	if (r==NULL) return(0);		/*空树返回0*/
	if (r->bj==-1) return(0);	/*线段被标记,说明已不存在,返回*/
	if (r->cover==1)			/*该区段已涂颜色*/
		return(r->j-r->i);	
	return(Calculate(r->lchild)+Calculate(r->rchild));
	/*统计左右子树已涂颜色的区段数之和*/
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
			printf("[%d,%d:%d,%d](%c)",p->i,p->j,p->cover,p->bj,type);
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
	ITree *r;
	r=CreateTree(1,7);
	InsTree(r,1,5);
	printf("线段树:\n");DispTree(r);
	printf("Num=%d\n",Calculate(r));
	DelTree(r,2,3);
	printf("线段树:\n");DispTree(r);
	printf("Num=%d\n",Calculate(r));
}


