#include "btree.cpp"
void PreOrder1(BTNode *b)	/*先序非递归遍历算法1*/
{
	BTNode *p;
	struct 
	{	BTNode *pt;
		int tag;
	} St[MaxSize];
	int top=-1;
	top++;
	St[top].pt=b;St[top].tag=1;
	while (top>-1)				/*栈不空时循环*/
	{	if (St[top].tag==1)		/*不能直接访问的情况*/
		{	p=St[top].pt;
			top--;
			if (p!=NULL)		/*(2)式*/
			{	top++;			/*右孩子结点进栈*/
				St[top].pt=p->rchild;
				St[top].tag=1;
				top++;			/*左孩子结点进栈*/
				St[top].pt=p->lchild;
				St[top].tag=1;
				top++;			/*根结点进栈*/
				St[top].pt=p;
				St[top].tag=0;
			}
		}
		if (St[top].tag==0)		/*直接访问的情况*/
		{	printf("%c ",St[top].pt->data);
			top--;
		}
	} /*while*/
}
void PreOrder2(BTNode *b)	/*先序非递归遍历算法2*/
{
	BTNode *St[MaxSize],*p;
	int top=-1;
	if (b!=NULL) 
	{   
		top++;						/*根结点进栈*/
		St[top]=b;
		while (top>-1)				/*栈不为空时循环*/
		{
			p=St[top];				/*退栈并访问该结点*/
			top--;
			printf("%c ",p->data);
			if (p->rchild!=NULL)	/*右孩子结点进栈*/
			{
				top++;
               	St[top]=p->rchild;
			}
			if (p->lchild!=NULL)	/*左孩子结点进栈*/
			{
				top++;
               	St[top]=p->lchild;
			}
		}
		printf("\n");
	}
}
void InOrder1(BTNode *b)		/*中序非递归遍历算法1*/
{
	BTNode *p;
	struct 
	{	BTNode *pt;
		int tag;
	} St[MaxSize];
	int top=-1;
	top++;
	St[top].pt=b;St[top].tag=1;
	while (top>-1)					/*栈不空时循环*/
	{	if (St[top].tag==1)			/*不能直接访问的情况*/
		{	p=St[top].pt;
			top--;
			if (p!=NULL)
			{	top++;				/*右孩子结点进栈*/
				St[top].pt=p->rchild;
				St[top].tag=1;
				top++;				/*根结点进栈*/
				St[top].pt=p;
				St[top].tag=0;
				top++;				/*左孩子结点进栈*/
				St[top].pt=p->lchild;
				St[top].tag=1;
			}
		}
		if (St[top].tag==0)			/*直接访问的情况*/
		{	printf("%c ",St[top].pt->data);
			top--;
		}
	} /*while*/
}
void InOrder2(BTNode *b)	/*中序非递归遍历算法2*/
{
	BTNode *St[MaxSize],*p;
	int top=-1;
	if (b!=NULL)
	{
		p=b;
		while (top>-1 || p!=NULL)		/*处理*b结点的左子树*/
		{
			while (p!=NULL)				/*扫描*p的所有左结点并进栈*/
			{
				top++;
				St[top]=p;
				p=p->lchild;
			}
			/*执行到此处时，栈顶元素没有左孩子或左子树均已访问过*/
			if (top>-1)
			{	
				p=St[top];				/*出栈*p结点*/
				top--;
				printf("%c ",p->data);	/*访问之*/
				p=p->rchild;			/*扫描*p的右孩子结点*/
			}
		}
		printf("\n");
	}
}
void PostOrder1(BTNode *b)		/*后序非递归遍历算法1*/
{
	BTNode *p;
	struct 
	{	BTNode *pt;
		int tag;
	} St[MaxSize];
	int top=-1;
	top++;
	St[top].pt=b;St[top].tag=1;
	while (top>-1)				/*栈不空时循环*/
	{	if (St[top].tag==1)		/*不能直接访问的情况*/
		{	p=St[top].pt;
			top--;
			if (p!=NULL)
			{	top++;			/*根结点进栈*/
				St[top].pt=p;
				St[top].tag=0;
				top++;			/*右孩子结点进栈*/
				St[top].pt=p->rchild;
				St[top].tag=1;
				top++;			/*左孩子结点进栈*/
				St[top].pt=p->lchild;
				St[top].tag=1;
			}
		}
		if (St[top].tag==0)		/*直接访问的情况*/
		{	printf("%c ",St[top].pt->data);
			top--;
		}
	} /*while*/
}
void PostOrder2(BTNode *b)		/*后序非递归遍历算法2*/
{
	BTNode *St[MaxSize];
	BTNode *p;
	int flag,top=-1;				/*栈指针置初值*/
	if (b!=NULL)
	{
		do
		{
			while (b!=NULL)			/*将*b的所有左结点进栈*/
			{
				top++;
				St[top]=b;
				b=b->lchild;
			}
			/*执行到此处时，栈顶元素没有左孩子或左子树均已访问过*/
			p=NULL;					/*p指向栈顶结点的前一个已访问的结点*/
			flag=1;					/*设置b的访问标记为已访问过*/
			while (top!=-1 && flag)
			{	b=St[top];			/*取出当前的栈顶元素*/
				if (b->rchild==p)	
				{	
					printf("%c ",b->data);	/*访问*b结点*/
					top--;
					p=b;			/*p指向刚访问过的结点*/
				}
				else
				{	
					b=b->rchild;	/*b指向右孩子结点*/
					flag=0;			/*设置未被访问的标记*/
				}
			}
		} while (top!=-1);
		printf("\n");
	} 
}
void main()
{
	BTNode *b;
	CreateBTNode(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTNode(b);printf("\n");
	printf("先序遍历序列1:");PreOrder1(b);printf("\n");
	printf("先序遍历序列2:");PreOrder2(b);printf("\n");
	printf("中序遍历序列1:");InOrder1(b);printf("\n");
	printf("中序遍历序列2:");InOrder2(b);printf("\n");
	printf("后序遍历序列1:");PostOrder1(b);printf("\n");
	printf("后序遍历序列2:");PostOrder2(b);printf("\n");
}
