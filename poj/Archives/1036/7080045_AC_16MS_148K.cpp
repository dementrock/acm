#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,k,t,T[101],P[101],S[101],f[101],ans;
inline int max(int a, int b){return a>b?a:b;}
void swap(int &a, int &b){int x=a;a=b;b=x;}
void quicksort(int left, int right){
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(T[i],T[right]);
	swap(S[i],S[right]);
	swap(P[i],P[right]);
	for(j=left,i=left-1;j<right;++j)
		if(T[j]<T[right])
		{
			++i;
			swap(T[i],T[j]);
			swap(S[i],S[j]);
			swap(P[i],P[j]);
		}
	++i;
	swap(T[i],T[right]);
	swap(S[i],S[right]);
	swap(P[i],P[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
void dp(int now)
{
	f[now]=0;
	for(int i=0;i<now;++i)
		if(T[now]-T[i]>=abs(S[i]-S[now]))
		{
			if(f[i]==-1) dp(i);
			f[now]=max(f[now],f[i]+P[now]);
		}
}
int main()
{
	scanf("%d%d%d",&n,&k,&t);
	for(int i=1;i<=n;++i) scanf("%d",&T[i]);
	for(int i=1;i<=n;++i) scanf("%d",&P[i]);
	for(int i=1;i<=n;++i) scanf("%d",&S[i]);
	T[0]=0;
	S[0]=0;
	P[0]=100000000;
	memset(f,0xff,sizeof(f));
	f[0]=P[0];
	quicksort(1,n);
	for(int i=0;i<=n;++i)
	{
		if(f[i]==-1) dp(i);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans-100000000);
	return 0;
}
