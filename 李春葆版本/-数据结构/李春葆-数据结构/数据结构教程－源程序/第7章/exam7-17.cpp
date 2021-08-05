#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;							/*��ʾ����[i,j]*/
	int cover;							/*���Ǹ�������߶ε�����*/
	struct node *lchild,*rchild;		/*���Һ���ָ��*/
} ITree;
int Flag[MaxSize];		/*ȫ�ֱ���,Flag[i]=1��ʾ������ɫi*/
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
void InsTree(ITree *r,int a,int b,int c)/*���߶���r�в���[a,b],��ɫΪc*/
{
	int mid;
	if (r==NULL) return;				/*����,����*/
	if (a<=r->i && r->j<=b)				/*[a,b]����������,��ɫ��Ϊc*/
		r->cover=c;
	else								/*[a,b]������������*/
	{
		if (r->cover>=0)				/*��������Ⱦ��ɫ*/
		{
			if (r->lchild!=NULL)		/*��������Ϊԭ��ɫ*/
				r->lchild->cover=r->cover;	
			if (r->rchild!=NULL)		/*���Һ�����Ϊԭ��ɫ*/
				r->rchild->cover=r->cover;	
			r->cover=-1;				/**r�����Ϊ������ɫ*/
		}
		mid=(r->i+r->j)/2;				/*���м�λ��mid*/
		if (b<=mid)						/*[a,b]����*r���������ǰ�벿*/
			InsTree(r->lchild,a,b,c);	/*���������в���[a,b]*/
		else if (mid<=a)				/*[a,b]����*r��������ĺ�벿*/
			InsTree(r->rchild,a,b,c);	/*���������в���[a,b]*/
		else
		{
			InsTree(r->lchild,a,mid,c);	/*���������в���[a,mid]*/
			InsTree(r->rchild,mid,b,c);	/*���������в���[mid,b]*/
		}
	}
}
void Cflag(ITree *r,int a,int b) 	/*���ڼ���Flag����ֵ*/
{
	int mid;
	if (r->cover>=0)			/*�ý��cover����0*/
		Flag[r->cover]=1;
	else if (b-a>1)				/*[a,b]���ȴ���1*/
	{
		mid=(a+b)/2;
		Cflag(r->lchild,a,mid);	/*���������м���Flag����*/
		Cflag(r->rchild,mid,b);	/*���������м���Flag����*/
	}
}

int Count(ITree *r,int a,int b) /*�����߶���r��ɫ����*/
{
	int i,s=0;
	Cflag(r,a,b);		/*����Cflag����Flag����*/
	for (i=0;i<=12;i++)	/*ͳ�Ʋ�ͬ��ɫ��*/
		s+=Flag[i];
	return(s-1);
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
			printf("[%2d,%2d:%2d](%c)",p->i,p->j,p->cover,type);
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
void main()
{
	int i,s=0;
	ITree *r;
	r=CreateTree(1,12);
	for (i=0;i<=12;i++)	/*�ó�ֵ0*/
		Flag[i]=0;
	InsTree(r,1,10,1);
	InsTree(r,4,6,2);
	InsTree(r,3,6,3);
	InsTree(r,5,8,4);
	printf("�߶���:\n");DispTree(r);
	printf("��ɫ����=%d\n",Count(r,1,12));
}
