#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int N,T,S,E,id[201],appear[1001],n;
long long mult[20][201][201],v[201][201],ans[201][201],matrix[201][201],oo;
long long min(long long a, long long b){return a>b?b:a;}
void init()
{
	int l,i1,i2;
	scanf("%d%d%d%d",&N,&T,&S,&E);
	for(int i=1;i<=T;++i)
	{
		scanf("%d%d%d",&l,&i1,&i2);
		if(!appear[i1]){id[++n]=i1;appear[i1]=n;}
		if(!appear[i2]){id[++n]=i2;appear[i2]=n;}
		v[appear[i1]][appear[i2]]=v[appear[i2]][appear[i1]]=l;
	}
}
void work()
{
	int tmp=N,t=0,binary[21]={};
	while(tmp)
	{
		binary[++t]=tmp&1;
		tmp>>=1;
	}
	memset(mult,0x77,sizeof(mult));
	memset(&oo,0x77,sizeof(oo));
	memcpy(mult[1],v,sizeof(v));
	for(int p=2;p<=t;++p)
	{
		for(int k=1;k<=n;++k)
			for(int i=1;i<=n;++i) if(i!=k)
				for(int j=1;j<=n;++j) if(j!=k&&i!=j&&mult[p-1][i][k]<oo&&mult[p-1][k][j]<oo)
					mult[p][i][j]=min(mult[p][i][j],mult[p-1][i][k]+mult[p-1][k][j]);
	}
	for(int ii=1;ii<=t;++ii) if(binary[ii])
	{
		memcpy(ans,mult[ii],sizeof(mult[ii]));
		for(int p=ii+1;p<=t;++p) if(binary[p])
		{
			memcpy(matrix,ans,sizeof(ans));
			memset(ans,0x77,sizeof(ans));
			for(int k=1;k<=n;++k)
				for(int i=1;i<=n;++i) if(i!=k)
					for(int j=1;j<=n;++j) if(j!=k&&i!=j&&matrix[i][k]<oo&&mult[p][k][j]<oo)
						ans[i][j]=min(ans[i][j],matrix[i][k]+mult[p][k][j]);
		}
	}
	printf("%I64d\n",ans[appear[S]][appear[E]]);
}
int main()
{
	init();
	work();
	return 0;	
}
