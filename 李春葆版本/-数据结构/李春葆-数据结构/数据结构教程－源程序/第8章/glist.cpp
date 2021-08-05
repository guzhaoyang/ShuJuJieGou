#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode
{	
	int tag;					/*������ͱ�ʶ*/
	union 
	{
		ElemType data;			/*ԭ��ֵ*/
		struct lnode *sublist;	/*ָ���ӱ��ָ��*/
	} val;
	struct lnode *link;			/*ָ����һ��Ԫ��*/
} GLNode;						/*����������Ͷ���*/
GLNode *CreateGL(char *&s)		/*���ɹ������ʽ�洢�ṹ*/
{	
	GLNode *h;
	char ch;
	ch=*s;                             /*ȡһ��ɨ���ַ�*/
	s++;                               /*��ָ�����һλ*/
	if (ch!='\0')                      /*��δ�����ж�*/
	{
		h=(GLNode *)malloc(sizeof(GLNode));/*����һ���½��*/
		if (ch=='(')                   /*��ǰ�ַ�Ϊ������ʱ*/
		{	
			h->tag=1;                  /*�½����Ϊ��ͷ���*/
			h->val.sublist=CreateGL(s); /*�ݹ鹹���ӱ�������ͷ���*/
		}
		else if (ch==')') 
			h=NULL;           			/*����')'�ַ�,�ӱ�Ϊ��*/
		else 
		{	
			h->tag=0;                   /*�½����Ϊԭ�ӽ��*/
			h->val.data=ch;
		}
	}
	else 
		h=NULL;                         /*������,�ӱ�Ϊ��*/
	ch=*s;                              /*ȡ��һ��ɨ���ַ�*/
	s++;                                /*��ָ�����һλ*/
	if (h!=NULL)                        /*��δ�����ж�*/
		if (ch==',')                    /*��ǰ�ַ�Ϊ','*/
			h->link=CreateGL(s);         /*�ݹ鹹������ӱ�*/
		else                            /*������*/
			h->link=NULL;               /*���������һ��Ԫ��*/
		return h;                       /*���ع����ָ��*/
}
void DispGL(GLNode *g)		/*gΪһ��������ͷ���ָ��*/
{
	if (g!=NULL)                 		/*��Ϊ���ж�*/
	{
		if (g->tag==1)               	/*Ϊ����ʱ*/
		{
			printf("(");                /*���'('*/
			if (g->val.sublist==NULL)  	
				printf("");				/*������ӱ�*/
			else 
				DispGL(g->val.sublist); /*�ݹ�����ӱ�*/
		}
		else 
			printf("%c", g->val.data);  /*Ϊԭ��ʱ���Ԫ��ֵ*/
		if (g->tag==1) 
			printf(")");               	/*Ϊ����ʱ���')'*/
		if (g->link!=NULL) 
		{
			printf(",");
			DispGL(g->link);            /*�ݹ���������������*/
		}
	}
}
int GLLength(GLNode *g)		/*gΪһ�������ͷ����ָ��*/
{
	int n=0;
	g=g->val.sublist;		/*gָ������ĵ�һ��Ԫ��*/
	while (g!=NULL) 
	{
		n++;				/*�ۼ�Ԫ�ظ���*/
		g=g->link;
	}
	return n;
}
int GLDepth(GLNode *g) 	/*���ͷ���Ĺ����g�����*/
{
   	int max=0,dep;
	if (g->tag==0)			/*Ϊԭ��ʱ����0*/
		return 0;
	g=g->val.sublist;		/*gָ���һ��Ԫ��*/
	if  (g==NULL)			/*Ϊ�ձ�ʱ����1*/
		return  1;
	while (g!=NULL)     	/*�������е�ÿһ��Ԫ��*/
	{	
		if (g->tag==1)   	/*Ԫ��Ϊ�ӱ�����*/
		{
			dep=GLDepth(g);	/*�ݹ��������ӱ�����*/
			if (dep>max)/*maxΪͬһ����������ӱ�����ȵ����ֵ*/
				max=dep;
		}
        g=g->link;  		/*ʹgָ����һ��Ԫ��*/
	}
    return(max+1);    		/*���ر�����*/
}
GLNode *GLCopy(GLNode *p)  /*pΪ�����ƵĹ�����ͷ���ָ��*/
{
	GLNode *q;
	if (p==NULL)			/*�ձ��ؿձ�*/
		return NULL;
	q=(GLNode *)malloc(sizeof(GLNode));	/*����һ�����*/
	q->tag=p->tag;						/*����*/
	if (p->tag==1)
		q->val.sublist=GLCopy(p->val.sublist);
	else
		q->val.data=p->val.data;
	q->link=GLCopy(p->link);			/*����������һ��Ԫ��*/
	return q;
}
/*�������������ڵ���
void main()
{
	GLNode *g,*g1;
	char *s="(a,(a,b),((a,b),c))";
	g=CreateGL(s);
	printf("g�ĳ���:%d\n",GLLength(g));
	printf("g�����:%d\n",GLDepth(g));
	printf("g:");DispGL(g);printf("\n");
	printf("g => g1\n");
	g1=GLCopy(g);
	printf("g1:");DispGL(g1);printf("\n");
}
*/