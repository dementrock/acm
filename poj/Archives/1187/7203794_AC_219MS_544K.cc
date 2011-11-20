#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[31][11][11][11];
void dp(int d, int l1, int l2, int l3){
	f[d][l1][l2][l3]=0;
	if(!l1&&!l2&&!l3){
		f[d][l1][l2][l3]=1;
		return;
	}
	if(!d) return;
	int s=l1+l2+l3;
	for(int ll1=0;ll1<=l1;++ll1)
		for(int ll2=0;ll2<=l2;++ll2)
			for(int ll3=0;ll3<=l3;++ll3){
				int t1,t2;
				if(f[d][l1-ll1][l2-ll2][l3-ll3]==-1)
					dp(d,l1-ll1,l2-ll2,l3-ll3);
				t1=f[d][l1-ll1][l2-ll2][l3-ll3];
				if(ll1){
					if(f[d-1][ll1-1][ll2][ll3]==-1)
						dp(d-1,ll1-1,ll2,ll3);
					t2=f[d-1][ll1-1][ll2][ll3];
				}else if(ll2){
					if(f[d-1][ll1][ll2-1][ll3]==-1)
						dp(d-1,ll1,ll2-1,ll3);
					t2=f[d-1][ll1][ll2-1][ll3];
				}else if(ll3){
					if(f[d-1][ll1][ll2][ll3-1]==-1)
						dp(d-1,ll1,ll2,ll3-1);
					t2=f[d-1][ll1][ll2][ll3-1];
				}
				if(t1>=0&&t2>=0){
					f[d][l1][l2][l3]+=t1*t2%11380;
					f[d][l1][l2][l3]%=11380;
				}
			}
}
int main(){
	int l1,l2,l3,d;
	scanf("%d%d%d%d",&l1,&l2,&l3,&d);
	memset(f,0xff,sizeof(f));
	if(l1+l2+l3<d)
		printf("0\n");
	else{
		if(f[d][l1][l2][l3]==-1)
			dp(d,l1,l2,l3);
		if(f[d-1][l1][l2][l3]==-1)
			dp(d-1,l1,l2,l3);
		printf("%d\n",(f[d][l1][l2][l3]-f[d-1][l1][l2][l3]+11380)%11380);
	}
	return 0;
} 
