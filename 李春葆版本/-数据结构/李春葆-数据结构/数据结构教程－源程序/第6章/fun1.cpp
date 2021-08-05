#include <stdio.h>
int fun1(int n)
{
	int f=1,i;
	for (i=2;i<=n;i++)
		f=f*i;
	return(f);
}
void main()
{
	int n=5;
	printf("%d!=%d\n",n,fun1(n));
}