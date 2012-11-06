#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[30],tf[30],d[30],t[30],h,onroad,maxtime,ans,n,ansi,ansstay[1000],stay[1000];
inline int max(int a, int b){return a>b?a:b;}
bool more(int a[], int b[], int c)
{
	for(int i=1;i<=c;++i)
	{
		if(a[i]>b[i]) return true;
		if(a[i]<b[i]) return false;
	}
	return false;
}
int main()
{
	int tc=0;
	while(scanf("%d",&n)!=EOF)
	{
		if(!n) break;
		scanf("%d",&h);
		onroad=0;
		ans=0;
		for(int i=1;i<=n;++i) scanf("%d",&f[i]);
		for(int i=1;i<=n;++i) scanf("%d",&d[i]);
		for(int i=2;i<=n;++i) scanf("%d",&t[i]);
		for(int i=1;i<=n;++i)
		{
			memcpy(tf,f,sizeof(f));
			memset(stay,0,sizeof(stay));
			int tans=0;
			onroad+=t[i];
			maxtime=h*12-onroad;
			if(maxtime<0) break;
			int tmp;
			for(tmp=maxtime;tmp>=1;--tmp)
			{
				int maxf=-1,maxj=0;
				for(int j=1;j<=i;++j)
				{
					if(tf[j]>0&&tf[j]>maxf)
					{
						maxf=tf[j];
						maxj=j;
					}
				}
				if(maxf<=0) break;
				tans+=tf[maxj];
				tf[maxj]-=d[maxj];
				if(tf[maxj]<0) tf[maxj]=0;
				++stay[maxj];
			}
			stay[1]+=tmp;
			if(tans>ans||tans==ans&&more(stay,ansstay,ansi))
			{
				ans=tans;
				ansi=i;
				memset(ansstay,0,sizeof(ansstay));
				for(int j=1;j<=i;++j) ansstay[j]=stay[j];
			}
		}
		printf("%d",ansstay[1]*5);
		for(int i=2;i<=n;++i)
			printf(", %d",ansstay[i]*5);
		printf("\n");
		printf("Number of fish expected: %d\n\n",ans);
	}
	return 0;
}
