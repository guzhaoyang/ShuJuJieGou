#include "glist.cpp"
int DelNode(GLNode *&g,ElemType x)  		/*gΪ�����ı�ͷ���ָ��*/
{
	GLNode *p=g->val.sublist,*pre,*q;    	/*preָ��p��ǰ�����*/
	if (g==NULL)
		return 0;
	while (p!=NULL) 
	{
		if (p->tag==0)                    	/*Ϊԭ�ӵ����*/
		{
			if (p->val.data==x)           	/*��data��ֵΪxʱɾ��֮*/
			{
				q=p;                        /*qָ��ɾ���*/
				if (g->val.sublist==p)    	/*��ɾ���ǵ�1�����*/
					if (p->link==NULL)     	/*��ɾ����޺������*/
						g->val.sublist=NULL;/*��Ϊ�ձ�*/
					else
						g->val.sublist=p->link;
					else					/*��ɾ�Ĳ��ǵ�1�����*/
						pre->link=p->link;
					p=p->link;
					free(q);
			}
			else 							/*ԭ�ӽ���data��ֵ��Ϊx*/
			{
				pre=p;
				p=p->link; 
			}
		}
		else             					/*Ϊ�ӱ�����*/
		{
			pre=p;
			DelNode(p,x);					/*�ݹ�ɾ���ӱ��е�x*/
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
	printf("ɾ��a\n");
	DelNode(g,'a');
	printf("g:");DispGL(g);printf("\n");
}
