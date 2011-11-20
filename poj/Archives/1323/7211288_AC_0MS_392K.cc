#include<stdio.h>
#include<stdlib.h>
int a[101],b[1001],bn;
int cmp(const void *a, const void *b){
	return *(int*)b-*(int *)a;
}
int main(){
	int n,m,cnt=0;
	while(scanf("%d%d",&n,&m)){
		if(!n&&!m) break;
		int vis[1001]={};
		++cnt;
		bn=0;
		for(int i=1;i<=m;++i){
			scanf("%d",&a[i]);
			vis[a[i]]=1;
		}
		for(int i=n*m;i>=1;--i){
			if(!vis[i])
				b[++bn]=i;
		}
		qsort(a+1,m,sizeof(a[0]),cmp);
		int pos1=1,pos2=1,ans=0;
		while(pos1<=m){
			if(a[pos1]>b[pos2]){
				++ans;
				++pos1;
			}else{
				++pos1,++pos2;
			}
		}
		printf("Case %d: %d\n",cnt,ans);
	}
	return 0;
}
