#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int h,w,f[12][3000];
void swap(int &a, int &b){int t=a;a=b;b=t;}
void dfs(int row, int now, int s1, int s2)
{
	if(now>w+1) return;
	if(now==w+1)
	{
		f[row][s1]+=f[row-1][s2];
		return;
	}
	dfs(row,now+1,s1<<1,(s2<<1)+1);
	dfs(row,now+1,(s1<<1)+1,s2<<1);
	dfs(row,now+2,(s1<<2)+3,(s2<<2)+3);
}
int main()
{
	while(1)
	{
		memset(f,0,sizeof(f));
		scanf("%d%d",&h,&w);
		if(!h&&!w) break;
		if(h&1&&w&1)
		{
			printf("0\n");
			continue;
		}
		if(h<w) swap(h,w);
		f[0][(1<<w)-1]=1;
		for(int i=1;i<=h;++i)
			dfs(i,1,0,0);
		printf("%d\n",f[h][(1<<w)-1]);
	}
	return 0;
}
