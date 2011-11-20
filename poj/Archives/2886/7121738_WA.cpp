#include<stdio.h>
#include<string.h>
int p[]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960};
int pnum[]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200};
int n,k,a[500001],c[500001];
char name[500001][11];
void add(int x, int d)
{
	for(;x<=n;x+=x&(-x))
		c[x]+=d;
}
int getsum(int x)
{
	int res=0;
	for(;x>0;x-=x&(-x))
		res+=c[x];
	return res;
}
int main()
{
	while(scanf("%d %d\n",&n,&k)!=EOF)
	{
		memset(c,0,sizeof(c));
		int m,maxi=0;
		for (;p[maxi+1]<=n;maxi++);
        	m=p[maxi];
		for(int i=1;i<=n;++i)
			scanf("%s %d\n",name[i],&a[i]);
		for (int i=1;i<=n;i++) c[i]=i & -i;
		for(int i=1;i<m;++i)
		{
			int left=1,right=n,next;
			if(a[k]>0)
				next=(a[k]%(n-i)+getsum(k)%(n-i)-1)%(n-i);
			else
				next=(a[k]%(n-i)+getsum(k)%(n-i))%(n-i);
			if(next<=0) next+=n-i;
			add(k,-1);
			while(left<=right)
			{
				int mid=left+right>>1;
				if(getsum(mid)<next)
					left=mid+1;
				else right=mid-1;
			}
			k=left;
		}
		printf("%s %d\n",name[k],pnum[maxi]);
	}
	return 0;
}
