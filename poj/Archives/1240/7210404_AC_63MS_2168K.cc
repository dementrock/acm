#include<stdio.h>
#include<string.h>
#include<string>
using namespace std;
struct segment{
	int i1,j1,i2,j2;
};
int F[26][26][26][26],N;
int s1[26],s2[26];
int dfs(segment seg[], int nseg, int now, int deep);
void dp(int i1, int j1, int i2, int j2);
int same(int a[], int b[]){
	for(int i=0;i<26;++i)
		if(a[i]!=b[i])
			return 0;
	return 1;
}
int dfs(segment seg[], int nseg, int now, int deep){
	int res=0;
	if(now==nseg) return 1;
	if(deep==N){
		if(F[seg[now+1].i1][seg[nseg].j1][seg[now+1].i2][seg[nseg].j2]==-1)
			dp(seg[now+1].i1,seg[nseg].j1,seg[now+1].i2,seg[nseg].j2);
		return F[seg[now+1].i1][seg[nseg].j1][seg[now+1].i2][seg[nseg].j2];
	}
	for(int i=now+1;i<=nseg;++i){
		if(F[seg[now+1].i1][seg[i].j1][seg[now+1].i2][seg[i].j2]==-1)
			dp(seg[now+1].i1,seg[i].j1,seg[now+1].i2,seg[i].j2);
		res+=F[seg[now+1].i1][seg[i].j1][seg[now+1].i2][seg[i].j2]*dfs(seg,nseg,i,deep+1);
	}
	res+=dfs(seg,nseg,now,deep+1);
	return res;
}
void dp(int i1, int j1, int i2, int j2){
	int appear1[26]={},appear2[26]={},nseg=0;
	segment seg[26];
	F[i1][j1][i2][j2]=0;
	if(s1[i1]!=s2[j2])
		return;
	if(i1==j1&&i2==j2){
		F[i1][j1][i2][j2]=1;
		return;
	}
	int ppos1=i1+1,ppos2=i2;
	for(int pos1=i1+1,pos2=i2;pos1<=j1&&pos2<j2;++pos1,++pos2){
		appear1[s1[pos1]]=appear2[s2[pos2]]=1;
		if(same(appear1,appear2)){
			seg[++nseg].i1=ppos1;
			seg[nseg].j1=pos1;
			seg[nseg].i2=ppos2;
			seg[nseg].j2=pos2;
			ppos1=pos1+1;
			ppos2=pos2+1;
			memset(appear1,0,sizeof(appear1));
			memset(appear2,0,sizeof(appear2));
		}
	}
	F[i1][j1][i2][j2]=dfs(seg,nseg,0,1);
}
int main(){
	char c;
	while(scanf("%d",&N)!=EOF){
		if(!N) break;
		int tmp=0;
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		memset(F,0xff,sizeof(F));
		while((c=getchar())==' ');
		s1[tmp++]=c-'a';
		while((c=getchar())!=' ')
			s1[tmp++]=c-'a';
		tmp=0;
		while((c=getchar())==' ');
		s2[tmp++]=c-'a';
		while((c=getchar())!='\n')
			s2[tmp++]=c-'a';
		dp(0,tmp-1,0,tmp-1);
		printf("%d\n",F[0][tmp-1][0][tmp-1]);
	}
	return 0;
}
