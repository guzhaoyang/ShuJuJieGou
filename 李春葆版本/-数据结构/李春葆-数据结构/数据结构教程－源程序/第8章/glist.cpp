#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode
{	
	int tag;					/*结点类型标识*/
	union 
	{
		ElemType data;			/*原子值*/
		struct lnode *sublist;	/*指向子表的指针*/
	} val;
	struct lnode *link;			/*指向下一个元素*/
} GLNode;						/*广义表结点类型定义*/
GLNode *CreateGL(char *&s)		/*生成广义表链式存储结构*/
{	
	GLNode *h;
	char ch;
	ch=*s;                             /*取一个扫描字符*/
	s++;                               /*串指针后移一位*/
	if (ch!='\0')                      /*串未结束判断*/
	{
		h=(GLNode *)malloc(sizeof(GLNode));/*创建一个新结点*/
		if (ch=='(')                   /*当前字符为左括号时*/
		{	
			h->tag=1;                  /*新结点作为表头结点*/
			h->val.sublist=CreateGL(s); /*递归构造子表并链到表头结点*/
		}
		else if (ch==')') 
			h=NULL;           			/*遇到')'字符,子表为空*/
		else 
		{	
			h->tag=0;                   /*新结点作为原子结点*/
			h->val.data=ch;
		}
	}
	else 
		h=NULL;                         /*串结束,子表为空*/
	ch=*s;                              /*取下一个扫描字符*/
	s++;                                /*串指针后移一位*/
	if (h!=NULL)                        /*串未结束判断*/
		if (ch==',')                    /*当前字符为','*/
			h->link=CreateGL(s);         /*递归构造后续子表*/
		else                            /*串结束*/
			h->link=NULL;               /*处理表的最后一个元素*/
		return h;                       /*返回广义表指针*/
}
void DispGL(GLNode *g)		/*g为一个广义表的头结点指针*/
{
	if (g!=NULL)                 		/*表不为空判断*/
	{
		if (g->tag==1)               	/*为表结点时*/
		{
			printf("(");                /*输出'('*/
			if (g->val.sublist==NULL)  	
				printf("");				/*输出空子表*/
			else 
				DispGL(g->val.sublist); /*递归输出子表*/
		}
		else 
			printf("%c", g->val.data);  /*为原子时输出元素值*/
		if (g->tag==1) 
			printf(")");               	/*为表结点时输出')'*/
		if (g->link!=NULL) 
		{
			printf(",");
			DispGL(g->link);            /*递归输出后续表的内容*/
		}
	}
}
int GLLength(GLNode *g)		/*g为一个广义表头结点的指针*/
{
	int n=0;
	g=g->val.sublist;		/*g指向广义表的第一个元素*/
	while (g!=NULL) 
	{
		n++;				/*累加元素个数*/
		g=g->link;
	}
	return n;
}
int GLDepth(GLNode *g) 	/*求带头结点的广义表g的深度*/
{
   	int max=0,dep;
	if (g->tag==0)			/*为原子时返回0*/
		return 0;
	g=g->val.sublist;		/*g指向第一个元素*/
	if  (g==NULL)			/*为空表时返回1*/
		return  1;
	while (g!=NULL)     	/*遍历表中的每一个元素*/
	{	
		if (g->tag==1)   	/*元素为子表的情况*/
		{
			dep=GLDepth(g);	/*递归调用求出子表的深度*/
			if (dep>max)/*max为同一层所求过的子表中深度的最大值*/
				max=dep;
		}
        g=g->link;  		/*使g指向下一个元素*/
	}
    return(max+1);    		/*返回表的深度*/
}
GLNode *GLCopy(GLNode *p)  /*p为被复制的广义表的头结点指针*/
{
	GLNode *q;
	if (p==NULL)			/*空表返回空表*/
		return NULL;
	q=(GLNode *)malloc(sizeof(GLNode));	/*创建一个结点*/
	q->tag=p->tag;						/*复制*/
	if (p->tag==1)
		q->val.sublist=GLCopy(p->val.sublist);
	else
		q->val.data=p->val.data;
	q->link=GLCopy(p->link);			/*继续复制下一个元素*/
	return q;
}
/*以下主函数用于调试
void main()
{
	GLNode *g,*g1;
	char *s="(a,(a,b),((a,b),c))";
	g=CreateGL(s);
	printf("g的长度:%d\n",GLLength(g));
	printf("g的深度:%d\n",GLDepth(g));
	printf("g:");DispGL(g);printf("\n");
	printf("g => g1\n");
	g1=GLCopy(g);
	printf("g1:");DispGL(g1);printf("\n");
}
*/