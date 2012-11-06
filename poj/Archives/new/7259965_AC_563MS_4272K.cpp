#include<stdio.h>
#include<stdlib.h>
int data[1025][1025],s;
int lowbit(int i)
{
	return i&(-i);
}
inline int max(int a, int b)
{
	return a>b?a:b;
}
void add(int x, int y, int k)
{
	for(int i=x;i<=s;i+=lowbit(i))
		for(int j=y;j<=s;j+=lowbit(j))
			data[i][j]=max(0,data[i][j]+k);
}
int sum(int x, int y)
{
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i))
		for(int j=y;j>=1;j-=lowbit(j))
		{
			ans+=data[i][j];
	//		printf("%d\n",data[i][j]);
		}
	return ans;
}
int main()
{
	int idnum,x,y,a,l,b,r,t;
	while(1)
	{
		scanf("%d",&idnum);
		if(idnum==0)
			scanf("%d",&s);
		else if(idnum==1)
		{
			scanf("%d%d%d",&x,&y,&a);
			++x;
			++y;
			add(x,y,a);
		}
		else if(idnum==2)
		{
			scanf("%d%d%d%d",&l,&b,&r,&t);
			++l;++b;++r;++t;
			printf("%d\n",sum(r,t)-sum(l-1,t)-sum(r,b-1)+sum(l-1,b-1));
		}
		else break;
	}
	return 0;
}
