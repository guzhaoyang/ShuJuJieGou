#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
void trans(char *exp,char postexp[])     
/*将算术表达式exp转换成后缀表达式postexp*/
{
	struct
	{	
		char data[MaxSize];		/*存放运算符*/
		int top;				/*栈指针*/
	} op;						/*定义运算符栈*/
	int i=0;					/*i作为postexp的下标*/
	op.top=-1;
	while (*exp!='\0')			/*exp表达式未扫描完时循环*/
	{	
		switch(*exp)
		{
		case '(':				/*判定为左括号*/
			op.top++;op.data[op.top]=*exp;
			exp++;				/*继续扫描其他字符*/
			break;
		case ')':				/*判定为右括号*/
			while (op.data[op.top]!='(')
			{	/*将栈中'('前面的运算符退栈并存放到postexp中*/
				postexp[i++]=op.data[op.top];
				op.top--;
			}
			op.top--;			/*将(退栈*/
			exp++;				/*继续扫描其他字符*/
			break;
		case '+':				/*判定为加或减号*/
		case '-':
			while (op.top!=-1 && op.data[op.top]!='(') 
			{	/*将栈中'('前面的运算符退栈并存放到postexp中*/
				postexp[i++]=op.data[op.top];
				op.top--;
			}
			op.top++;op.data[op.top]=*exp; /*将'+'或'-'进栈*/
			exp++;				/*继续扫描其他字符*/
			break;
		case '*':				/*判定为'*'或'/'号*/
		case '/':
			while (op.data[op.top]=='*' || op.data[op.top]=='/')
			{	/*将栈中'*'或'/'运算符依次出栈并存放到postexp中*/
				postexp[i++]=op.data[op.top];
				op.top--;
			}
			op.top++;op.data[op.top]=*exp; /*将'*'或'/'进栈*/
			exp++;				/*继续扫描其他字符*/
			break;
		case ' ':break;			/*过滤掉空格*/
		default:				/*处理数字字符*/
			while (*exp>='0' && *exp<='9') /*判定为数字*/
			{	
				postexp[i++]=*exp;
				exp++;
			}
			postexp[i++]='#';	/*用#标识一个数值串结束*/
		}
	}
	while (op.top!=-1)			/*此时exp扫描完毕,栈不空时循环*/
	{	
		postexp[i++]=op.data[op.top];
		op.top--;  
	}
	postexp[i]='\0';			/*给postexp表达式添加结束标识*/
}
float compvalue(char *postexp )	/*计算后缀表达式的值*/
{
	struct 
	{	
		float data[MaxSize];	/*存放数值*/
		int top;				/*栈指针*/
	} st;						/*定义数值栈*/
	float d,a,b,c;
	st.top=-1;
	while (*postexp!='\0')		/*postexp字符串未扫描完时循环*/
	{	
		switch (*postexp)
		{
		case '+':				/*判定为'+'号*/
			a=st.data[st.top];
			st.top--;			/*退栈取数值a*/
			b=st.data[st.top];
			st.top--;			/*退栈取数值b*/
			c=a+b;				/*计算c*/
			st.top++;
			st.data[st.top]=c;	/*将计算结果进栈*/
			break;
		case '-':				/*判定为'-'号*/
			a=st.data[st.top];
			st.top--;			/*退栈取数值a*/
			b=st.data[st.top];
			st.top--;			/*退栈取数值b*/
			c=b-a;				/*计算c*/
			st.top++;
			st.data[st.top]=c;	/*将计算结果进栈*/
			break;
		case '*':				/*判定为'*'号*/
			a=st.data[st.top];
			st.top--;			/*退栈取数值a*/
			b=st.data[st.top];
			st.top--;			/*退栈取数值b*/
			c=a*b;				/*计算c*/
			st.top++;
			st.data[st.top]=c;	/*将计算结果进栈*/
			break;
		case '/':				/*判定为'/'号*/
			a=st.data[st.top];
			st.top--;			/*退栈取数值a*/
			b=st.data[st.top];
			st.top--;			/*退栈取数值b*/
			if (a!=0)
			{
				c=b/a;			/*计算c*/
				st.top++;
				st.data[st.top]=c;	/*将计算结果进栈*/
			}
			else
		    {	
				printf("\n\t除零错误!\n");
				exit(0);		/*异常退出*/
			}
			break;
		default:				/*处理数字字符*/
			d=0;				/*将连续的数字字符转换成对应的数值存放到d中*/
			while (*postexp>='0' && *postexp<='9')   /*判定为数字字符*/
			{	
				d=10*d+*postexp-'0';  
				postexp++;
			}
			st.top++;
			st.data[st.top]=d;
			break;
		}
		postexp++;				/*继续处理其他字符*/
	}
	return(st.data[st.top]);
}
void main()
{
	char exp[]="(56-20)/(4+2)";
	char postexp[MaxSize];
	trans(exp,postexp);
	printf("中缀表达式:%s\n",exp);
	printf("后缀表达式:%s\n",postexp);
	printf("表达式的值:%g\n",compvalue(postexp));
}