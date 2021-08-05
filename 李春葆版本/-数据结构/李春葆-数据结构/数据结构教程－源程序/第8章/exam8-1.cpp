#include "glist.cpp"
GLNode *head(GLNode *h)  /*h为一个广义表的头结点指针*/
{
	GLNode *p=h->val.sublist;
	GLNode *q,*t;
	if (p==NULL) 
	{
		printf("空表不能求表头\n");
		return NULL;
	}
	else if (h->tag==0) 
	{
		printf("原子不能求表头\n");
		return NULL;
	}
	if (p->tag==0)                /*为原子结点时*/
	{
		q=(GLNode *)malloc(sizeof(GLNode));
		q->tag=0;q->val.data=p->val.data;
		q->link=NULL;
	}
	else 						/*为子表时,产生虚子表t*/
	{
		t=(GLNode *)malloc(sizeof(GLNode));
		t->tag=1;t->val.sublist=p->val.sublist;
		t->link=NULL;
		q=GLCopy(t);
		free(t);
	}
	return q;
}
GLNode *tail(GLNode *g)  /*g为一个广义表的头结点指针*/
{
	GLNode *p=g->val.sublist;
	GLNode *q,*t;
	if (g==NULL) 					/*为空表时*/
	{
		printf("空表不能求表尾\n");
		return NULL;
	}
	else if (g->tag==0)               /*为原子时*/
	{
		printf("原子不能求表尾\n");
		return NULL;
	}
	p=p->link;
	t=(GLNode *)malloc(sizeof(GLNode)); /*建立一个虚表t*/
	t->tag=1;t->link=NULL;
	t->val.sublist=p;
	q=GLCopy(t);
	free(t);
	return q;
}
int GLLength1(GLNode *g)	/*求带头结点广义表g的长度*/
{
	GLNode *gt;
	if (g==NULL)				/*空表返回0*/
		return 0;
	else if (g->val.sublist==NULL)	/*空表时返回0*/
		return 0;
	else
	{	gt=tail(g);				/*求出g的表尾*/
		return(GLLength1(gt)+1);/*返回表尾的长度+1*/
	}
}
int GLDepth1(GLNode *g) 	/*求带头结点广义表g的深度*/
{
	int maxdep,dep1,dep2;
	GLNode *gh,*gt;
	if (g==NULL)			/*空表返回0*/
		return 0;
	else if (g->tag==0)		/*原子返回0*/
		return 0;
	else if (g->val.sublist==NULL)	/*空表时返回1*/
		return 1;
	else
	{	gh=head(g);			/*求出g的表头*/
		dep1=GLDepth1(gh)+1;/*求出表头的深度+1*/
		gt=tail(g);			/*求出g的表尾*/
		dep2=GLDepth1(gt);	/*求出表尾的深度+1*/
		maxdep=(dep1>dep2 ? dep1 : dep2);
		return(maxdep);
	}
}

void main()
{
	GLNode *g,*gh,*gt;
	char *s="(a,(a,b),((a,b),c))";
	g=CreateGL(s);
	printf("g:");DispGL(g);printf("\n");
	gh=head(g);
	gt=tail(g);
	printf("表头:");DispGL(gh);printf("\n");
	printf("表尾:");DispGL(gt);printf("\n");
	printf("g的长度:%d\n",GLLength1(g));
	printf("g的深度:%d\n",GLDepth1(g));
}
