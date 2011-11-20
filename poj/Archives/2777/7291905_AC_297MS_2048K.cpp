#include<stdio.h>
#define MAXN 1000001
int same[MAXN],c[MAXN];
void swap(int &a, int &b){
	int x=a;a=b;b=x;
}
void init(int p, int l, int r){
	c[p]=1;
	if(l==r) return;
	init(p*2,l,(l+r)>>1);
	init(p*2+1,((l+r)>>1)+1,r);
}
void add(int p, int l, int r, int x1, int x2, int color){
	if(l==x1&&r==x2||l==r){
		c[p]=1<<(color-1);
		same[p]=1;
		return;
	}
	if(same[p]){
		same[p*2]=same[p*2+1]=1;
		c[p*2]=c[p*2+1]=c[p];
	}
	same[p]=0;
	int m=l+r>>1;
	if(x2<=m){
		add(p*2,l,m,x1,x2,color);
	}else if(m+1<=x1){
		add(p*2+1,m+1,r,x1,x2,color);
	}else{
		add(p*2,l,m,x1,m,color);
		add(p*2+1,m+1,r,m+1,x2,color);
	}
	c[p]=c[p*2]|c[p*2+1];
}
int query(int p, int l, int r, int x1, int x2){
	if(l==x1&&r==x2||l==r)
		return c[p];
	int m=l+r>>1;
	if(same[p]){
		same[p*2]=same[p*2+1]=1;
		c[p*2]=c[p*2+1]=c[p];
	}
	same[p]=0;
	if(x2<=m){
		return query(p*2,l,m,x1,x2);
	}else if(m+1<=x1){
		return query(p*2+1,m+1,r,x1,x2);
	}else{
		return query(p*2,l,m,x1,m)|query(p*2+1,m+1,r,m+1,x2);
	}
}
int main(){
	char ch;
	int L,T,O,a,b,c;
	scanf("%d %d %d\n",&L,&T,&O);
	init(1,1,L);
	for(int i=1;i<=O;++i){
		ch=getchar();
		if(ch=='C'){
			scanf("%d %d %d\n",&a,&b,&c);
			if(a>b) swap(a,b);
			add(1,1,L,a,b,c);
		}else{
			scanf("%d %d\n",&a,&b);
			int k=query(1,1,L,a,b),ans=0;
			while(k){ ans+=k&1;k>>=1;}
			printf("%d\n",ans);
		}
	}
	return 0;
}
