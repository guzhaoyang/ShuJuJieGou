#include <stdio.h>
int Fib1(int n)
{
	int i,f1,f2,f3;
	if (n==1 || n==2)
		return(1);
	f1=1;f2=1;
	for (i=3;i<=n;i++)
	{	
		f3=f1+f2;
		f1=f2;
		f2=f3;
	}
	return(f3);
}
void main()
{
	int i;
	for (i=1;i<10;i++)
		printf("%d ",Fib1(i));
	printf("\n");
}