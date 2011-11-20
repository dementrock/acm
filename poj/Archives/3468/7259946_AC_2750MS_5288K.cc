#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 100001
long long a[MAXN];
long long sum[8*MAXN],c[8*MAXN];
void createtree(int p, int left, int right){
	if(left==right){
		sum[p]=a[left];
		return;
	}
	int mid=left+right>>1;
	createtree(p*2,left,mid);
	createtree(p*2+1,mid+1,right);
	sum[p]=sum[p*2]+sum[p*2+1];
}
void add(int p, int left, int right, int l, int r, long long value){
	if(left==l&&right==r){
		c[p]+=value;
		return;
	}
	int mid=left+right>>1;
	if(r<=mid){
		add(p*2,left,mid,l,r,value);
	}
	else if(l>=mid+1){
		add(p*2+1,mid+1,right,l,r,value);
	}
	else{
		add(p*2,left,mid,l,mid,value);
		add(p*2+1,mid+1,right,mid+1,r,value);
	}
	sum[p]=sum[p*2]+sum[p*2+1]+c[p*2]*(mid-left+1)+c[p*2+1]*(right-mid);
}
long long getsum(int p, int left, int right, int l, int r){
	long long delt=(r-l+1)*c[p];
	if(left==l&&right==r){
		return sum[p]+delt;
	}
	int mid=left+right>>1;
	if(r<=mid){
		return getsum(p*2,left,mid,l,r)+delt;
	}
	else if(l>=mid+1){
		return getsum(p*2+1,mid+1,right,l,r)+delt;
	}
	else{
		return getsum(p*2,left,mid,l,mid)+getsum(p*2+1,mid+1,right,mid+1,r)+delt;
	}
}
int main(){
	char c;
	int n,q,l,r;
	long long v;
	scanf("%d %d\n",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%I64d",&a[i]);
	scanf("\n");
	createtree(1,1,n);
	for(int i=1;i<=q;++i){
		scanf("%c",&c);
		if(c=='C'){
			scanf(" %d %d %I64d\n",&l,&r,&v);
		//	printf("%I64d\n",v);
			add(1,1,n,l,r,v);
		}
		else{
			scanf(" %d %d\n",&l,&r);
			printf("%I64d\n",getsum(1,1,n,l,r));
		}
	}
	return 0;
}
