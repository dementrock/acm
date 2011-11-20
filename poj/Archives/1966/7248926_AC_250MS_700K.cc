#include<stdio.h>
#include<string.h>
#define MAXN 201
int n,m,S,T,v[MAXN][MAXN],layer[MAXN],counter[MAXN],
minf,ans,K,found,tv[MAXN][MAXN],oo=0x77777777;
inline int min(int a, int b){
	return a<b?a:b;
}
void aug(int now){
	if(now==T){
		found=1;
		ans+=minf;
		return;
	}
	int i,tmp=minf,minl=2*n;
	for(i=1;i<=2*n;++i){
		if(v[now][i]){
			if(layer[now]==layer[i]+1){
				minf=min(minf,v[now][i]);
				aug(i);
				if(layer[S]>2*n) return;
				if(found) break;
				minf=tmp;
			}
			minl=min(minl,layer[i]);
		}
	}
	if(!found){
		if(!(--counter[layer[now]])) layer[S]=2*n+1;
		++counter[layer[now]=minl+1];
	}else{
		v[now][i]-=minf;
		v[i][now]+=minf;
	}
}
void sap(){
	memcpy(tv,v,sizeof(v));
	memset(counter,0,sizeof(counter));
	memset(layer,0,sizeof(layer));
	ans=0;
	counter[0]=2*n;
	while(layer[S]<=2*n){
		found=0;
		minf=oo;
		aug(S);
	}
	memcpy(v,tv,sizeof(tv));
}
int main(){
	char str[11];
	while(scanf("%d %d",&n,&m)!=EOF){
		if(!n||n>1&&!m){
			printf("0\n");
			continue;
		}else if(n==1){
			printf("1\n");
			continue;
		}
		K=n;
		memset(v,0,sizeof(v));
		for(int i=1,j,k1,k2;i<=m;++i){
			scanf("%s",str);
			for(j=1,k1=0;str[j]!=',';++j)
				k1=k1*10+str[j]-'0';
			for(++j,k2=0;str[j]!=')';++j)
				k2=k2*10+str[j]-'0';
			++k1,++k2;
			v[k1+n][k2]=v[k2+n][k1]=oo;
		}
		for(int i=1;i<=n;++i)
			v[i][i+n]=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i!=j&&!v[i+n][j]){
					S=i+n,T=j;
					sap();
					K=min(K,ans);
				}
			}
		}
		printf("%d\n",K);
	}
	return 0;
}
