#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,m,a[101][101];
long long f[52][52][2];
void init(){
	char c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=i;++j){
			while((c=getchar())!='*'&&c!='.');
			a[i][j]=c=='*'?1:0;
		}
	}
	for(int i=1;i<=n+1;++i) a[n+1][i]=1;
	for(int i=1;i<=n+1;++i)
		for(int j=1;j<=i;++j)
			f[i][j][1]=1;
}
long long getgcd(long long a, long long b){
	if(a>b) return getgcd(b,a);
	if(!(b%a))
		return a;
	return getgcd(b%a,a);
}
void add(int id,long long a[], long long b[]){
	long long tb0=b[0],tb1=b[1];
	if(!id){
		if(b[0]&1) b[1]<<=1;
		else b[0]>>=1;
	}
	long long gcd=getgcd(a[1],b[1]);
	long long lcm=((double)1.0*a[1]/gcd*b[1]);
	a[0]=a[0]*(lcm/a[1])+b[0]*(lcm/b[1]);
	a[1]=lcm;
	b[0]=tb0,b[1]=tb1;
	while(!(a[0]&1)&&!(a[1]&1))
		a[0]>>=1,a[1]>>=1;
}
void work(){
	f[1][1][1]=f[1][1][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=i;++j){
			if(a[i][j]){
				add(0,f[i+1][j],f[i][j]);
				add(0,f[i+1][j+1],f[i][j]);
			}
			else{
				for(int k=i+2;k<=n+1;k+=2){
					if(a[k][j+(k-i)/2]){
						add(1,f[k][j+(k-i)/2],f[i][j]);
						break;
					}
				}
			}
		}
	}
	printf("%I64d/%I64d\n",f[n+1][m+1][0],f[n+1][m+1][1]);
}
int main(){
	init();
	work();
	return 0;
}
