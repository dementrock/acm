#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,m,ans,filla[100],fillb[100],a[100],b[100],map[100][100];
int main()
{
	while(scanf("%d%d",&n,&m))
	{
		memset(map,0,sizeof(map));
		memset(filla,0,sizeof(filla));
		memset(fillb,0,sizeof(fillb));
		ans=0;
		if(!n&&!m) break;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=m;++i) scanf("%d",&b[i]);
		for(int i=1;i<=n;++i)
			if(!filla[i])
			{
				int flag=0;
				for(int j=1;j<=m;++j)
					if(a[i]==b[j]&&!fillb[j]&&!map[i][j])
					{
						fillb[j]=1;
						map[i][j]=1;
						ans+=a[i];
						flag=1;
						break;
					}
				if(flag) continue;
				for(int j=1;j<=m;++j)
					if(a[i]==b[j]&&!map[i][j])
					{
						map[i][j]=1;
						ans+=a[i];
						flag=1;
						break;
					}
				if(flag) continue;
				for(int j=1;j<=m;++j)
					if(a[i]<=b[j]&&!map[i][j])
					{
						map[i][j]=1;
						ans+=a[i];
						flag=1;
						break;
					}
			}
		for(int i=1;i<=m;++i)
			if(!fillb[i])
			{
				int flag=0;
				for(int j=1;j<=n;++j)
					if(b[i]==a[j]&&!map[j][i])
					{
						map[j][i]=1;
						ans+=b[i];
						flag=1;
						break;
					}
				if(flag) continue;
				for(int j=1;j<=n;++j)
					if(b[i]<=a[j]&&!map[j][i])
					{
						map[i][j]=1;
						ans+=b[i];
						flag=1;
						break;
					}
			}
		printf("%d\n",ans);
	}
}
