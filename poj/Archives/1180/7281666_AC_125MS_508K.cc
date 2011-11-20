#include<stdio.h>
#include<string.h>
#define MAXN 10001
#define oo 0x77777777
struct Stack{
	int s,t,id;
} stack[MAXN];
int N,S,sumt[MAXN],sumf[MAXN],f[MAXN],head,K;
inline int min(int a, int b){
	return a<b?a:b;
}
inline int getw(int i, int j){
	return (S+sumt[j]-sumt[i])*(sumf[N]-sumf[i]);
}
inline int getf(int j, int i){
	return f[j]+getw(j,i);
}
void update(int now){
	while(head&&now<stack[head].s&&getf(now,stack[head].s)<getf(stack[head].id,stack[head].s)){
		stack[head-1].t=stack[head].t;
		--head;
	}
	int l=stack[head].s,r=stack[head].t,m;
	while(l<=r){
		m=l+r>>1;
		if(getf(now,m)<getf(stack[head].id,m))
			r=m-1;
		else
			l=m+1;
	}
	while(l<=stack[head].t&&getf(now,l)>getf(stack[head].id,l)) ++l;
	stack[head].t=l-1;
	if(stack[head].t<stack[head].s) --head;
	if(l>N) return;
	stack[++head].s=l;
	stack[head].t=N;
	stack[head].id=now;
}
int main(){
	scanf("%d\n%d\n",&N,&S);
	for(int i=1;i<=N;++i){
		scanf("%d %d",&sumt[i],&sumf[i]);
		sumt[i]+=sumt[i-1],sumf[i]+=sumf[i-1];
	}
	stack[head=1].s=1,stack[K=1].t=N;
	for(int i=1;i<=N;++i){
		if(i>stack[K].t)
			++K;
		f[i]=getf(stack[K].id,i);
		update(i);
	}
	printf("%d\n",f[N]);
	return 0;
}
