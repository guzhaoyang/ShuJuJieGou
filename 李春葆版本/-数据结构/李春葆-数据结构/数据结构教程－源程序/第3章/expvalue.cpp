#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
void trans(char *exp,char postexp[])     
/*���������ʽexpת���ɺ�׺���ʽpostexp*/
{
	struct
	{	
		char data[MaxSize];		/*��������*/
		int top;				/*ջָ��*/
	} op;						/*���������ջ*/
	int i=0;					/*i��Ϊpostexp���±�*/
	op.top=-1;
	while (*exp!='\0')			/*exp���ʽδɨ����ʱѭ��*/
	{	
		switch(*exp)
		{
		case '(':				/*�ж�Ϊ������*/
			op.top++;op.data[op.top]=*exp;
			exp++;				/*����ɨ�������ַ�*/
			break;
		case ')':				/*�ж�Ϊ������*/
			while (op.data[op.top]!='(')
			{	/*��ջ��'('ǰ����������ջ����ŵ�postexp��*/
				postexp[i++]=op.data[op.top];
				op.top--;
			}
			op.top--;			/*��(��ջ*/
			exp++;				/*����ɨ�������ַ�*/
			break;
		case '+':				/*�ж�Ϊ�ӻ����*/
		case '-':
			while (op.top!=-1 && op.data[op.top]!='(') 
			{	/*��ջ��'('ǰ����������ջ����ŵ�postexp��*/
				postexp[i++]=op.data[op.top];
				op.top--;
			}
			op.top++;op.data[op.top]=*exp; /*��'+'��'-'��ջ*/
			exp++;				/*����ɨ�������ַ�*/
			break;
		case '*':				/*�ж�Ϊ'*'��'/'��*/
		case '/':
			while (op.data[op.top]=='*' || op.data[op.top]=='/')
			{	/*��ջ��'*'��'/'��������γ�ջ����ŵ�postexp��*/
				postexp[i++]=op.data[op.top];
				op.top--;
			}
			op.top++;op.data[op.top]=*exp; /*��'*'��'/'��ջ*/
			exp++;				/*����ɨ�������ַ�*/
			break;
		case ' ':break;			/*���˵��ո�*/
		default:				/*���������ַ�*/
			while (*exp>='0' && *exp<='9') /*�ж�Ϊ����*/
			{	
				postexp[i++]=*exp;
				exp++;
			}
			postexp[i++]='#';	/*��#��ʶһ����ֵ������*/
		}
	}
	while (op.top!=-1)			/*��ʱexpɨ�����,ջ����ʱѭ��*/
	{	
		postexp[i++]=op.data[op.top];
		op.top--;  
	}
	postexp[i]='\0';			/*��postexp���ʽ��ӽ�����ʶ*/
}
float compvalue(char *postexp )	/*�����׺���ʽ��ֵ*/
{
	struct 
	{	
		float data[MaxSize];	/*�����ֵ*/
		int top;				/*ջָ��*/
	} st;						/*������ֵջ*/
	float d,a,b,c;
	st.top=-1;
	while (*postexp!='\0')		/*postexp�ַ���δɨ����ʱѭ��*/
	{	
		switch (*postexp)
		{
		case '+':				/*�ж�Ϊ'+'��*/
			a=st.data[st.top];
			st.top--;			/*��ջȡ��ֵa*/
			b=st.data[st.top];
			st.top--;			/*��ջȡ��ֵb*/
			c=a+b;				/*����c*/
			st.top++;
			st.data[st.top]=c;	/*����������ջ*/
			break;
		case '-':				/*�ж�Ϊ'-'��*/
			a=st.data[st.top];
			st.top--;			/*��ջȡ��ֵa*/
			b=st.data[st.top];
			st.top--;			/*��ջȡ��ֵb*/
			c=b-a;				/*����c*/
			st.top++;
			st.data[st.top]=c;	/*����������ջ*/
			break;
		case '*':				/*�ж�Ϊ'*'��*/
			a=st.data[st.top];
			st.top--;			/*��ջȡ��ֵa*/
			b=st.data[st.top];
			st.top--;			/*��ջȡ��ֵb*/
			c=a*b;				/*����c*/
			st.top++;
			st.data[st.top]=c;	/*����������ջ*/
			break;
		case '/':				/*�ж�Ϊ'/'��*/
			a=st.data[st.top];
			st.top--;			/*��ջȡ��ֵa*/
			b=st.data[st.top];
			st.top--;			/*��ջȡ��ֵb*/
			if (a!=0)
			{
				c=b/a;			/*����c*/
				st.top++;
				st.data[st.top]=c;	/*����������ջ*/
			}
			else
		    {	
				printf("\n\t�������!\n");
				exit(0);		/*�쳣�˳�*/
			}
			break;
		default:				/*���������ַ�*/
			d=0;				/*�������������ַ�ת���ɶ�Ӧ����ֵ��ŵ�d��*/
			while (*postexp>='0' && *postexp<='9')   /*�ж�Ϊ�����ַ�*/
			{	
				d=10*d+*postexp-'0';  
				postexp++;
			}
			st.top++;
			st.data[st.top]=d;
			break;
		}
		postexp++;				/*�������������ַ�*/
	}
	return(st.data[st.top]);
}
void main()
{
	char exp[]="(56-20)/(4+2)";
	char postexp[MaxSize];
	trans(exp,postexp);
	printf("��׺���ʽ:%s\n",exp);
	printf("��׺���ʽ:%s\n",postexp);
	printf("���ʽ��ֵ:%g\n",compvalue(postexp));
}