#include <stdio.h>
#define MaxSize 100
typedef struct
{	
	char data[MaxSize];
	int len;			/*����*/
} SqString;
void StrAssign(SqString &str,char cstr[])	/*strΪ�����Ͳ���*/
{
    int i;
    for (i=0;cstr[i]!='\0';i++)
		str.data[i]=cstr[i];
    str.len=i;
}
void StrCopy(SqString &s,SqString t)		/*sΪ�����Ͳ���*/
{
    int i;
    for (i=0;i<t.len;i++)
        s.data[i]=t.data[i];
    s.len=t.len;
}
int StrEqual(SqString s,SqString t)
{
	int same=1,i;
	if (s.len!=t.len)      		/*���Ȳ����ʱ����0*/
		same=0;
	else 
		for (i=0;i<s.len;i++)
			if (s.data[i]!=t.data[i])	/*��һ����Ӧ�ַ�����ͬʱ����0*/
			{	
				same=0;
				break;
			}
			return same;
}
int StrLength(SqString s)
{
    return s.len;
}
SqString Concat(SqString s,SqString t)
{
    SqString str;
    int i;
    str.len=s.len+t.len;
    for (i=0;i<s.len;i++)   	/*��s.data[0]��s.data[s.len-1]���Ƶ�str*/
        str.data[i]=s.data[i]; 
    for (i=0;i<t.len;i++)   	/*��t.data[0]��t.data[t.len-1]���Ƶ�str*/
        str.data[s.len+i]=t.data[i];
    return str;
}
SqString SubStr(SqString s,int i,int j)
{
	SqString str;
	int k;
	str.len=0;
	if (i<=0 || i>s.len || j<0 || i+j-1>s.len)
		return str;          		/*��������ȷʱ���ؿմ�*/
	for (k=i-1;k<i+j-1;k++)  		/*��s.data[i]��s.data[i+j]���Ƶ�str*/
		str.data[k-i+1]=s.data[k];
	str.len=j;
	return str;
} 
SqString InsStr(SqString s1,int i,SqString s2)
{
	int j;
	SqString str;
	str.len=0;
	if (i<=0 || i>s1.len+1)     /*��������ȷʱ���ؿմ�*/
		return str;
	for (j=0;j<i-1;j++)         /*��s1.data[0]��s1.data[i-2]���Ƶ�str*/
		str.data[j]=s1.data[j];
	for (j=0;j<s2.len;j++)     	/*��s2.data[0]��s2.data[s2.len-1]���Ƶ�str*/
		str.data[i+j-1]=s2.data[j];
	for (j=i-1;j<s1.len;j++) 	/*��s1.data[i-1]��s.data[s1.len-1]���Ƶ�str*/
		str.data[s2.len+j]=s1.data[j];
	str.len=s1.len+s2.len;
    return str;
}
SqString DelStr(SqString s,int i,int j)
{
	int k;
	SqString str;
	str.len=0;
	if (i<=0 || i>s.len || i+j>s.len+1) /*��������ȷʱ���ؿմ�*/
		return str;
	for (k=0;k<i-1;k++)       /*��s.data[0]��s.data[i-2]���Ƶ�str*/
		str.data[k]=s.data[k];
	for (k=i+j-1;k<s.len;k++)/*��s.data[i+j-1]��data[s.len-1]���Ƶ�str*/
		str.data[k-j]=s.data[k];
	str.len=s.len-j;
	return str;
}
SqString RepStr(SqString s,int i,int j,SqString t)
{
	int k;
	SqString str;
	str.len=0;
	if (i<=0 || i>s.len || i+j-1>s.len) /*��������ȷʱ���ش�s*/
		return str;
	for (k=0;k<i-1;k++)			/*��s.data[0]��s.data[i-2]���Ƶ�str*/
		str.data[k]=s.data[k];
	for (k=0;k<t.len;k++)      	/*��t.data[0]��t.data[t.len-1]���Ƶ�str*/
		str.data[i+k-1]=t.data[k];
	for (k=i+j-1;k<s.len;k++)	/*��s.data[i+j-1]��data[s.len-1]���Ƶ�str*/
        str.data[t.len+k-j]=s.data[k];
	str.len=s.len-j+t.len;
	return str;
}
void DispStr(SqString s)
{
	int i;
	if (s.len>0)
	{	
		for (i=0;i<s.len;i++)
			printf("%c",s.data[i]);
		printf("\n");
	}
}
