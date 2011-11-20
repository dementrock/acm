#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 200001
int sum[8*MAXN],c[MAXN],p[MAXN],ans[MAXN],n;
void create(int p, int left, int right){
	sum[p]=right-left+1;
	if(left==right) return;
	int mid=left+right>>1;
	create(p*2,left,mid);
	create(p*2+1,mid+1,right);
}
int find(int p, int left, int right, int k){
	if(left==right){
		sum[p]=0;
		return left;
	}
	int mid=left+right>>1,ans=0;
	if(sum[p*2]>=k)
		ans=find(p*2,left,mid,k);
	else
		ans=find(p*2+1,mid+1,right,k-sum[p*2]);
	sum[p]=sum[p*2]+sum[p*2+1];
	return ans;
}
int main()
{
	while(scanf("%d",&n)!=EOF){
		create(1,1,n);
		for(int i=1;i<=n;++i){
			scanf("%d%d",&p[i],&c[i]);
			++p[i];
		}
		for(int i=n;i>=1;--i){
			ans[find(1,1,n,p[i])]=c[i];
		}
		for(int i=1;i<=n;++i){
			printf("%d",ans[i]);
			if(i<n)
				printf(" ");
			else
				printf("\n");
		}
	}
	return 0;
}
