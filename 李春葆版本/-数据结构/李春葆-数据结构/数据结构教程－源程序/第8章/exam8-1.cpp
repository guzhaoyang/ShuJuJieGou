#include "glist.cpp"
GLNode *head(GLNode *h)  /*hΪһ��������ͷ���ָ��*/
{
	GLNode *p=h->val.sublist;
	GLNode *q,*t;
	if (p==NULL) 
	{
		printf("�ձ������ͷ\n");
		return NULL;
	}
	else if (h->tag==0) 
	{
		printf("ԭ�Ӳ������ͷ\n");
		return NULL;
	}
	if (p->tag==0)                /*Ϊԭ�ӽ��ʱ*/
	{
		q=(GLNode *)malloc(sizeof(GLNode));
		q->tag=0;q->val.data=p->val.data;
		q->link=NULL;
	}
	else 						/*Ϊ�ӱ�ʱ,�������ӱ�t*/
	{
		t=(GLNode *)malloc(sizeof(GLNode));
		t->tag=1;t->val.sublist=p->val.sublist;
		t->link=NULL;
		q=GLCopy(t);
		free(t);
	}
	return q;
}
GLNode *tail(GLNode *g)  /*gΪһ��������ͷ���ָ��*/
{
	GLNode *p=g->val.sublist;
	GLNode *q,*t;
	if (g==NULL) 					/*Ϊ�ձ�ʱ*/
	{
		printf("�ձ������β\n");
		return NULL;
	}
	else if (g->tag==0)               /*Ϊԭ��ʱ*/
	{
		printf("ԭ�Ӳ������β\n");
		return NULL;
	}
	p=p->link;
	t=(GLNode *)malloc(sizeof(GLNode)); /*����һ�����t*/
	t->tag=1;t->link=NULL;
	t->val.sublist=p;
	q=GLCopy(t);
	free(t);
	return q;
}
int GLLength1(GLNode *g)	/*���ͷ�������g�ĳ���*/
{
	GLNode *gt;
	if (g==NULL)				/*�ձ���0*/
		return 0;
	else if (g->val.sublist==NULL)	/*�ձ�ʱ����0*/
		return 0;
	else
	{	gt=tail(g);				/*���g�ı�β*/
		return(GLLength1(gt)+1);/*���ر�β�ĳ���+1*/
	}
}
int GLDepth1(GLNode *g) 	/*���ͷ�������g�����*/
{
	int maxdep,dep1,dep2;
	GLNode *gh,*gt;
	if (g==NULL)			/*�ձ���0*/
		return 0;
	else if (g->tag==0)		/*ԭ�ӷ���0*/
		return 0;
	else if (g->val.sublist==NULL)	/*�ձ�ʱ����1*/
		return 1;
	else
	{	gh=head(g);			/*���g�ı�ͷ*/
		dep1=GLDepth1(gh)+1;/*�����ͷ�����+1*/
		gt=tail(g);			/*���g�ı�β*/
		dep2=GLDepth1(gt);	/*�����β�����+1*/
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
	printf("��ͷ:");DispGL(gh);printf("\n");
	printf("��β:");DispGL(gt);printf("\n");
	printf("g�ĳ���:%d\n",GLLength1(g));
	printf("g�����:%d\n",GLDepth1(g));
}
