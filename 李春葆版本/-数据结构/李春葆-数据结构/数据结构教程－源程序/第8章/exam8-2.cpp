#include "glist.cpp"
int DelNode(GLNode *&g,ElemType x)  		/*g为广义表的表头结点指针*/
{
	GLNode *p=g->val.sublist,*pre,*q;    	/*pre指向p的前驱结点*/
	if (g==NULL)
		return 0;
	while (p!=NULL) 
	{
		if (p->tag==0)                    	/*为原子的情况*/
		{
			if (p->val.data==x)           	/*其data域值为x时删除之*/
			{
				q=p;                        /*q指向被删结点*/
				if (g->val.sublist==p)    	/*被删的是第1个结点*/
					if (p->link==NULL)     	/*被删结点无后续结点*/
						g->val.sublist=NULL;/*置为空表*/
					else
						g->val.sublist=p->link;
					else					/*被删的不是第1个结点*/
						pre->link=p->link;
					p=p->link;
					free(q);
			}
			else 							/*原子结点的data域值不为x*/
			{
				pre=p;
				p=p->link; 
			}
		}
		else             					/*为子表的情况*/
		{
			pre=p;
			DelNode(p,x);					/*递归删除子表中的x*/
			p=p->link;
		}
	}
	return 1;
}
void main()
{
	GLNode *g;
	char *s="(a,(a,b),((a,b),c))";
	g=CreateGL(s);
	printf("g:");DispGL(g);printf("\n");
	printf("删除a\n");
	DelNode(g,'a');
	printf("g:");DispGL(g);printf("\n");
}
