#include <stdio.h>
#define MaxSize 20
typedef int KeyType;  	/*定义关键字类型*/
typedef char InfoType[10];
typedef struct       	/*记录类型*/
{
	KeyType key;   		/*关键字项*/
	InfoType data; 		/*其他数据项,类型为InfoType*/
} RecType;				/*排序的记录类型定义*/
void QuickSort1(RecType R[],int s,int t) /*对R[s]至R[t]的元素进行快速排序*/
{
	int i=s,j=t;
	KeyType pivot;
	pivot=R[(s+t)/2].key;		/*用区间中间记录作为基准*/
	RecType tmp;
	if (s<t) 					/*区间内至少存在两个元素的情况*/
	{	
		while (i!=j)  			/*从区间两端交替向中间扫描,直至i=j为止*/
		{	
			while (j>i && R[j].key>pivot) 
				j--;  			/*从右向左扫描,找第1个小于tmp.key的R[j]*/
			while (i<j && R[i].key<pivot) 
				i++;			/*从左向右扫描,找第1个大于tmp.key的记录R[i]*/
			if (i<=j)			/*R[i]和R[j]进行交换*/
			{
				tmp=R[i];
				R[i]=R[j];
				R[j]=tmp;
			}
		}
		QuickSort1(R,s,i-1);		/*对左区间递归排序*/
		QuickSort1(R,j+1,t);    	/*对右区间递归排序*/
	}
}
void main()
{
	int i,n=10;
	RecType R[MaxSize];
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("排序前:");
	for (i=0;i<n;i++)
		printf("%d ",R[i].key);
	printf("\n");
	QuickSort1(R,0,n-1);
	printf("排序后:");
	for (i=0;i<n;i++)
		printf("%d ",R[i].key);
	printf("\n");
}


