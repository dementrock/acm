#include<stdio.h>
int h,size,n,heap[1<<21],a[1<<21],stack[1<<21],maxd,sub;
void dfs(int now)
{
	if(now*2<=size)
		dfs(now*2);
	if(now*2+1<=size){
		++sub;
		dfs(now*2+1);
	}
	a[++n]=heap[now]-sub;
}
int main()
{
	scanf("%d",&h);
	while(scanf("%d",&heap[size+1])!=EOF)
		++size;
	dfs(1);
	stack[1]=maxd=1;
//	for(int i=1;i<=n;++i) printf("%d ",a[i]);
//	printf("\n");
	for(int i=2;i<=n;++i)
	{
		int left=1,right=maxd,mid;
		while(left<=right){
			mid=left+right>>1;
			if(a[i]>=a[stack[mid]])
				left=mid+1;
			else 
				right=mid-1;
		}
		if(left>maxd)
		{
			++maxd;
			stack[maxd]=i;
		}
		else if(a[i]<a[stack[left]]) stack[left]=i;
	}
	printf("%d\n",size-maxd);
	return 0;
}
