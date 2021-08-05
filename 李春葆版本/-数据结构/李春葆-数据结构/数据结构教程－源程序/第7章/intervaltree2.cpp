#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;						/*��ʾ����[i,j]*/
	int count;						/*���Ǹ�������߶ε�����*/
	struct node *lchild,*rchild;	/*���Һ���ָ��*/
} ITree;
ITree *CreateTree(int a,int b)	/*��[a,b]�����߶���*/
{
	ITree *r;
	if (b<a) return(NULL);				/*������Ч����NULL*/
	r=(ITree *)malloc(sizeof(ITree));	/*���������*/
	r->i=a;r->j=b;
	r->count=0;
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
	if (r->count!=1)	/**r���ԭ��û��Ϳ����ɫ*/
	{
		if (r->i==a && r->j==b) /*�ҵ�������, Ϳ����ɫ*/
			 r->count=1;
		else	/*����Ҫ�ҵ�����*/
		{
			//r->count=0; 
           	mid=(r->i+r->j)/2;						/*���м�λ��mid*/
			if (mid<=a) InsTree(r->rchild,a,b);		/*���������в���[a,b]*/
			else if (b<=mid) InsTree(r->lchild,a,b);/*���������в���[a,b]*/
			else
			{
				InsTree(r->lchild,a,mid);			/*���������в���[a,mid]*/
				InsTree(r->rchild,mid,b);			/*���������в���[mid,b]*/
			}
		}
	}
}
void DelTree(ITree *r,int a,int b)		/*���߶���r��ɾ��[a,b]*/
{
	int mid;
	if (r->count!=-1)	/**r���ԭ��û��ɾ����ɫ*/
	{
		if (r->i==a && r->j==b)		/*�ҵ��˸�����,ɾ����ɫ*/
			r->count=-1;	
		else
		{
			//r->count=0;
            mid=(r->i+r->j)/2;			/*���м�λ��k*/
			if (mid<=a) 
				DelTree(r->rchild,a,b);	/*����������ɾ��[a,b]*/
			else if (b<=mid) 
				DelTree(r->lchild,a,b);	/*����������ɾ��[a,b]*/
			else
			{
				DelTree(r->lchild,a,mid);	/*����������ɾ��[a,mid]*/
				DelTree(r->rchild,mid,b);	/*����������ɾ��[mid,b]*/
			}
		}
	}
}
int Count(ITree *r)		/*ͳ���߶�����Ϳ��ɫ��������*/
{
	int c=0;
	if (r==NULL) return(0);	/*��������0*/
	if (r->count==1)		/*��������Ϳ��ɫ*/
		c=r->j-r->i;	
	else if (r->count==-1)	/*��������ɾ����ɫ*/
		c=r->i-r->j;
	return(Count(r->lchild)+Count(r->rchild)+c);
	/*ͳ������������Ϳ��ɫ��������֮��*/
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
			printf("[%d,%d:%d](%c)",p->i,p->j,p->count,type);
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
	char ch;
	ITree *r;
	r=CreateTree(1,7);
	printf("Ins:[1,5]\n");
	InsTree(r,1,5);
	printf("�߶���:\n");DispTree(r);
	printf("Count=%d\n",Count(r));
	
	ch=getchar();
	printf("Del:[2,3]\n");
	DelTree(r,2,3);
	printf("�߶���:\n");DispTree(r);
	printf("Count=%d\n",Count(r));

	ch=getchar();
	printf("Ins:[2,6]\n");
	InsTree(r,2,6);
	printf("�߶���:\n");DispTree(r);
	printf("Count=%d\n",Count(r));
}


