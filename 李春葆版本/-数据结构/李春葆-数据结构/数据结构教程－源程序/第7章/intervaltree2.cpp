#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;						/*表示区间[i,j]*/
	int count;						/*覆盖该区间的线段的条数*/
	struct node *lchild,*rchild;	/*左、右孩子指针*/
} ITree;
ITree *CreateTree(int a,int b)	/*由[a,b]建立线段树*/
{
	ITree *r;
	if (b<a) return(NULL);				/*区间无效返回NULL*/
	r=(ITree *)malloc(sizeof(ITree));	/*创建根结点*/
	r->i=a;r->j=b;
	r->count=0;
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
	if (r->count!=1)	/**r结点原来没有涂上颜色*/
	{
		if (r->i==a && r->j==b) /*找到该区间, 涂上颜色*/
			 r->count=1;
		else	/*不是要找的区间*/
		{
			//r->count=0; 
           	mid=(r->i+r->j)/2;						/*求中间位置mid*/
			if (mid<=a) InsTree(r->rchild,a,b);		/*在右子树中插入[a,b]*/
			else if (b<=mid) InsTree(r->lchild,a,b);/*在左子树中插入[a,b]*/
			else
			{
				InsTree(r->lchild,a,mid);			/*在左子树中插入[a,mid]*/
				InsTree(r->rchild,mid,b);			/*在右子树中插入[mid,b]*/
			}
		}
	}
}
void DelTree(ITree *r,int a,int b)		/*在线段树r中删除[a,b]*/
{
	int mid;
	if (r->count!=-1)	/**r结点原来没有删除颜色*/
	{
		if (r->i==a && r->j==b)		/*找到了该区间,删除颜色*/
			r->count=-1;	
		else
		{
			//r->count=0;
            mid=(r->i+r->j)/2;			/*求中间位置k*/
			if (mid<=a) 
				DelTree(r->rchild,a,b);	/*在右子树中删除[a,b]*/
			else if (b<=mid) 
				DelTree(r->lchild,a,b);	/*在左子树中删除[a,b]*/
			else
			{
				DelTree(r->lchild,a,mid);	/*在左子树中删除[a,mid]*/
				DelTree(r->rchild,mid,b);	/*在右子树中删除[mid,b]*/
			}
		}
	}
}
int Count(ITree *r)		/*统计线段树已涂颜色的区段数*/
{
	int c=0;
	if (r==NULL) return(0);	/*空树返回0*/
	if (r->count==1)		/*该区段已涂颜色*/
		c=r->j-r->i;	
	else if (r->count==-1)	/*该区段已删除颜色*/
		c=r->i-r->j;
	return(Count(r->lchild)+Count(r->rchild)+c);
	/*统计左、右子树已涂颜色的区段数之和*/
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
			printf("[%d,%d:%d](%c)",p->i,p->j,p->count,type);
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
	char ch;
	ITree *r;
	r=CreateTree(1,7);
	printf("Ins:[1,5]\n");
	InsTree(r,1,5);
	printf("线段树:\n");DispTree(r);
	printf("Count=%d\n",Count(r));
	
	ch=getchar();
	printf("Del:[2,3]\n");
	DelTree(r,2,3);
	printf("线段树:\n");DispTree(r);
	printf("Count=%d\n",Count(r));

	ch=getchar();
	printf("Ins:[2,6]\n");
	InsTree(r,2,6);
	printf("线段树:\n");DispTree(r);
	printf("Count=%d\n",Count(r));
}


