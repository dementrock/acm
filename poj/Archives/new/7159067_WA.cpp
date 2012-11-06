#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[101][101][101],n,m,forbid[101],ans,
cnt[101],state[101],snum;
inline int max(int a, int b){
	return a>b?a:b;
}
void getstate(int now, int s, int c){
	if(now==m+1){
		state[++snum]=s;
		cnt[snum]=c;
		return;
	}
	if(now+2<=m)
		getstate(now+3,(s<<3)+4,c+1);
	else if(now+1<=m)
		getstate(now+2,(s<<2)+2,c+1);
	else
		getstate(now+1,(s<<1)+1,c+1);
	getstate(now+1,s<<1,c);
}
void init(){
	char c;
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			c=getchar();
			forbid[i]<<=1;
			forbid[i]+=c=='H'?1:0;
		}
		getchar();
	}
	getstate(1,0,0);
}
void work(){
	for(int i=1;i<=snum;++i)
		if(!(forbid[1]&state[i]))
			f[1][i][0]=cnt[i];
	for(int i=1;i<=snum;++i) if(!(forbid[2]&state[i]))
		for(int j=1;j<=snum;++j)  if(!(forbid[1]&state[j]))
			if(!(state[i]&state[j]))
				f[2][i][j]=cnt[i]+f[1][j][0];
	for(int i=3;i<=n;++i)
		for(int j=1;j<=snum;++j) if(!(forbid[i]&state[j]))
			for(int k=1;k<=snum;++k) if(!(forbid[i-1]&state[k]))
				if(!(state[j]&state[k]))
					for(int p=1;p<=snum;++p) if(!(forbid[i-2]&state[p]))
						if(!(state[j]&state[p])&&!(state[k]&state[p]))
							f[i][j][k]=max(f[i][j][k],cnt[j]+f[i-1][k][p]);
							
	for(int i=1;i<=snum;++i)
		for(int j=1;j<=snum;++j)
			ans=max(ans,f[n][i][j]);
	printf("%d\n",ans);
}
int main(){
	init();
	work();
	return 0;
}
