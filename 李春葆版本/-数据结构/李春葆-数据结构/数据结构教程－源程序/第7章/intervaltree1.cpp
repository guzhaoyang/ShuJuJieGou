#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define MaxWidth 40
typedef struct node
{
	int i,j;						/*��ʾ����[i,j]*/
	int cover;						/*�������Ƿ񱻸���*/
	int bj;							/*������ı��*/
	struct node *lchild,*rchild;	/*���Һ���ָ��*/
} ITree;
ITree *CreateTree(int a,int b)	/*��[a,b]�����߶���*/
{
	ITree *r;
	if (b<a) return(NULL);				/*������Ч����NULL*/
	r=(ITree *)malloc(sizeof(ITree));	/*���������*/
	r->i=a;r->j=b;
	r->cover=0;r->bj=0;
	if (b-a>1)							/*���䳤�ȴ���1*/
	{
		r->lchild=CreateTree(a,(a+b)/2);/*�ݹ鴴��������*/
		r->rchild=CreateTree((a+b)/2,b);/*�ݹ鴴��������*/
	}
	else								/*���䳤�ȵ���1*/
		r->lchild=r->rchild=NULL;
	return(r);
}
void Clean(ITree *&p)  /*���±�ǵĹ���*/
{
	p->cover=0;			/*��ǰ����Ϊδ����*/
	p->bj=0;			/*��ǰ����bj��Ϊ0*/
	p->lchild->bj=-1;	/*���ӽ���bj��Ϊ-1*/
	p->rchild->bj=-1;	/*�Һ��ӽ���bj��Ϊ-1*/
}
void InsTree(ITree *r,int a,int b)	/*���߶���r�в���[a,b]*/
{
	int mid;
	if (r->bj==-1) Clean(r);			/*��*r��㱻��������*/
	if (r->cover==1) return;			/*���������ѱ�Ϳɫ,�˳�����*/
	if (a<=r->i && b>=r->j)				/*[a,b]������ǰ����*/
	{
		r->cover=1;
		return;
	}
	mid=(r->i+r->j)/2;					/*���м�λ��mid*/
	if (a<mid) InsTree(r->lchild,a,b);	/*���������в���[a,b]*/
	if (b>mid) InsTree(r->rchild,a,b);	/*���������в���[a,b]*/
}
void DelTree(ITree *r,int a,int b)		/*���߶���r��ɾ��[a,b]*/
{
	int mid;
	if (r->bj==-1) return;	/*���߶α����,˵�����߶��Ѳ�������,�����ٽ���ɾ��,�˳�����*/
	if (a<=r->i && b>=r->j)	/*[a,b]������ǰ����*/
	{
		r->cover=0;
		r->lchild->bj=-1;	/*�������ѱ�ɾ������Ϣ��������*/
		r->rchild->bj=-1;	/*�������ѱ�ɾ������Ϣ�����Һ���*/
		return;
	}
	if (r->cover==1)	/*�����߶��Ǳ�Ϳ��ɫ��*/
	{
		r->cover=0;
		r->lchild->bj=-1;	/*�������ѱ�ɾ������Ϣ��������,��ɾ��*/
		r->rchild->bj=-1;	/*�������ѱ�ɾ������Ϣ�����Һ���,��ɾ��*/
		if (r->i<a) InsTree(r,r->i,a);	/*�ٲ���*/
		if (b<r->j) InsTree(r,b,r->j);
	}
	else  /*������������Ҷ��ӵ���ɾ������*/
	{
		mid=(r->i+r->j)/2;			/*���м�λ��k*/
		if (a<mid) DelTree(r->lchild,a,b);	/*����������ɾ��[a,b]*/
		if (b<mid) DelTree(r->rchild,a,b);	/*����������ɾ��[a,b]*/
	}
}
int Calculate(ITree *r)		/*���㱻���ǵĵ�λ�߶�����*/
{
	if (r==NULL) return(0);		/*��������0*/
	if (r->bj==-1) return(0);	/*�߶α����,˵���Ѳ�����,����*/
	if (r->cover==1)			/*��������Ϳ��ɫ*/
		return(r->j-r->i);	
	return(Calculate(r->lchild)+Calculate(r->rchild));
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
			printf("[%d,%d:%d,%d](%c)",p->i,p->j,p->cover,p->bj,type);
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
	ITree *r;
	r=CreateTree(1,7);
	InsTree(r,1,5);
	printf("�߶���:\n");DispTree(r);
	printf("Num=%d\n",Calculate(r));
	DelTree(r,2,3);
	printf("�߶���:\n");DispTree(r);
	printf("Num=%d\n",Calculate(r));
}


