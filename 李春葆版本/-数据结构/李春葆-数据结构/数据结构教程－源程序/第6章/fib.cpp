#include <stdio.h>
int Fib(int n)
{
	if (n==1 || n==2)
		return(1);
	else
		return(Fib(n-1)+Fib(n-2));
}
void main()
{
	int i;
	for (i=1;i<10;i++)
		printf("%d ",Fib(i));
	printf("\n");
}