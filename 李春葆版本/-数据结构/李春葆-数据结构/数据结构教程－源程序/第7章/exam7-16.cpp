#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;						/*��ʾ����[i,j]*/
	int cover;						/*���Ǹ�������߶ε�����*/
	struct node *lchild,*rchild;	/*���Һ���ָ��*/
} ITree;
ITree *CreateTree(int a,int b)	/*��[a,b]�����߶���*/
{
	ITree *r;
	if (b<a) return(NULL);				/*������Ч����NULL*/
	r=(ITree *)malloc(sizeof(ITree));	/*���������*/
	r->i=a;r->j=b;r->cover=0;
	if (b-a>1)							/*���䳤�ȴ���1*/
	{
		r->lchild=CreateTree(a,(a+b)/2);/*�ݹ鴴��������*/
		r->rchild=CreateTree((a+b)/2,b);/*�ݹ鴴��������*/
	}
	else								/*���䳤�ȵ���1*/
		r->lchild=r->rchild=NULL;
	return(r);
}
void InsTree(ITree *r,int a,int b)	/*���߶���r�в���[a,b]*/
{
	int mid;
	if (a<=r->i && r->j<=b)				/*�ҵ�������,�����߶�����1*/
		r->cover++;
	else								/*����Ҫ�ҵ�����*/
	{
		mid=(r->i+r->j)/2;				/*���м�λ��mid*/
		if (b<=mid) 
			InsTree(r->lchild,a,b);		/*���������в���[a,b]*/
		else if (mid<=a) 
			InsTree(r->rchild,a,b);		/*���������в���[a,b]*/
		else
		{
			InsTree(r->lchild,a,mid);	/*���������в���[a,mid]*/
			InsTree(r->rchild,mid,b);	/*���������в���[mid,b]*/
		}
	}
}
void DelTree(ITree *r,int a,int b)	/*���߶���r��ɾ��[a,b]*/
{
	int mid;
	if (a<=r->i && r->j<=b)				/*�ҵ�������,�����߶�����1*/
		r->cover--;
	else								/*����Ҫ�ҵ�����*/
	{
		mid=(r->i+r->j)/2;				/*���м�λ��mid*/
		if (b<=mid) 
			DelTree(r->lchild,a,b);		/*����������ɾ��[a,b]*/
		else if (mid<=a) 
			DelTree(r->rchild,a,b);		/*����������ɾ��[a,b]*/
		else
		{
			DelTree(r->lchild,a,mid);	/*����������ɾ��[a,mid]*/
			DelTree(r->rchild,mid,b);	/*����������ɾ��[mid,b]*/
		}
	}
}
int Count(ITree *r)		/*�����߶���r�Ĳ��*/
{
	if (r->cover>0)
		return(r->j-r->i);	/*�ý��cover����0*/
	else if (r->j-r->i==1)	/*��Ҷ�ӽ��*/
		return(0);
	else 
		return(Count(r->lchild)+Count(r->rchild));/*�������������Ĳ��*/
}
void DispTree(ITree *r)  /*�԰����ʾ�����һ���߶���*/
{
	ITree *St[MaxSize],*p;
	int level[MaxSize][2],top=-1,n,i,width=4;
	char type;
	if (r!=NULL)
	{
		top++;
		St[top]=r;						/*�������ջ*/
		level[top][0]=width;
		level[top][1]=2;				/*2��ʾ�Ǹ�*/
		while (top>-1)
		{
			p=St[top];					/*��ջ��������ʾ�ý��ֵ*/
			n=level[top][0];
			switch(level[top][1])
			{
			case 0:type='L';break;		/*����֮�����(L)*/
			case 1:type='R';break;		/*�ҽ��֮�����(R)*/
			case 2:type='B';break;		/*�����֮��ǰ���(B)*/
			}
			for (i=1;i<=n;i++)			/*����nΪ��ʾ����,�ַ����Ҷ�����ʾ*/
				printf(" ");
			printf("[%d,%d:%d](%c)",p->i,p->j,p->cover,type);
			for (i=n+1;i<=MaxWidth;i+=2)
				printf("--");
			printf("\n");
			top--;
			if (p->rchild!=NULL)
			{							/*���������������ջ*/
				top++;
				St[top]=p->rchild;
				level[top][0]=n+width;	/*��ʾ������width*/
				level[top][1]=1;		/*1��ʾ��������*/
			}
			if (p->lchild!=NULL)
			{							/*���������������ջ*/
				top++;
				St[top]=p->lchild;
				level[top][0]=n+width;  /*��ʾ������width*/
				level[top][1]=0;        /*0��ʾ��������*/
			}
		}
	}
}
void fun()
{
	ITree *r;
	r=CreateTree(1,10);
	printf("(1)����[3,6]��[7,9]�߶�\n");
	InsTree(r,3,6);
	InsTree(r,7,9);
	printf("Count=%d\n",Count(r));
	printf("(2)ɾ��[7,9]�߶�\n");
	DelTree(r,7,9);
	printf("Count=%d\n",Count(r));
	printf("(3)����[7,10]�߶�\n");
	InsTree(r,7,10);
	printf("Count=%d\n",Count(r));
	printf("(4)ɾ��[3,6]�߶�\n");
	DelTree(r,3,6);
	printf("Count=%d\n",Count(r));
	//DispTree(r);
}
void main()
{
	fun();
}
