#include "sqstring.cpp"
int Strcmp(SqString s,SqString t)
{
	int i,comlen;
	if (s.len<t.len) comlen=s.len;	/*��s��t�Ĺ�ͬ����*/
	else comlen=t.len;
	for (i=0;i<comlen;i++)  		/*�ڹ�ͬ����������ַ��Ƚ�*/
		if (s.data[i]<t.data[i]) 
			return -1;
		else if (s.data[i]>t.data[i]) 
			return 1;
	if (s.len==t.len)     			/*s==t*/
		return 0;
	else if (s.len<t.len)   		/*s<t*/
		return -1;
	else  return 1;           		/*s>t*/
}
void main()
{
	SqString s,t;
	StrAssign(s,"abcdefg");
	StrAssign(t,"ab");
	printf("s:");DispStr(s);
	printf("t:");DispStr(t);
	printf("Strcmp(s,t)=%d\n",Strcmp(s,t));

	StrAssign(s,"abcd");
	StrAssign(t,"abcd");
	printf("s:");DispStr(s);
	printf("t:");DispStr(t);
	printf("Strcmp(s,t)=%d\n",Strcmp(s,t));
}

