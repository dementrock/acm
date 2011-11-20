#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 2000001
int change[101][101];
struct strie{
	int score;
	strie *next[26];
} *shead, smempool[MAXN];
int smemnum,maxscore;
char str[101],ans[101],maxs[101];
inline strie *newspace(){
	return &smempool[smemnum++];
}
void addc(int a, int b){
	change[a][++change[a][0]]=b;
}
void add(char *str, int score){
	strie *x=shead;
//	printf("%s\n",str);
	for(int i=0;i<strlen(str);++i){
		int tmp=str[i]-'a';
		if(x->next[tmp]==NULL){
			x->next[tmp]=newspace();
		}
//		printf("y");
		x=x->next[tmp];
		x->score+=score;
	}
}
void init(){
	shead=newspace();
	int n,score;
	char str[101];
	scanf("%d\n",&n);
	//	printf("y");
	for(int i=1;i<=n;++i){
		scanf("%s %d\n",str,&score);
	//	printf("y");
		add(str,score);
	}
}
void iddfs(strie *x, int snow, int maxdeep){
	if(snow==maxdeep){
		if(x->score>maxscore){
			maxscore=x->score;
		//	printf("%d\n",maxscore);
			strcpy(maxs,ans);
		}
		return;
	}
	int now=str[snow]-'0';
	for(int i=1;i<=change[now][0];++i){
		if(x->next[change[now][i]-'a']!=NULL){
			ans[snow]=change[now][i];
			iddfs(x->next[change[now][i]-'a'],snow+1,maxdeep);
			ans[snow]=0;
		}
	}
}
void work(){
	int k;
	scanf("%d\n",&k);
	for(int i=1;i<=k;++i){
		scanf("%s\n",str);
		for(int j=1;j<strlen(str);++j){
			maxscore=0;
			iddfs(shead,0,j);
			if(maxscore)
				printf("%s\n",maxs);
			else
				printf("MANUALLY\n");
		}
		printf("\n");
	}
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	addc(2,'a');
	addc(2,'b');
	addc(2,'c');
	addc(3,'d');
	addc(3,'e');
	addc(3,'f');
	addc(4,'g');
	addc(4,'h');
	addc(4,'i');
	addc(5,'j');
	addc(5,'k');
	addc(5,'l');
	addc(6,'m');
	addc(6,'n');
	addc(6,'o');
	addc(7,'p');
	addc(7,'q');
	addc(7,'r');
	addc(7,'s');
	addc(8,'t');
	addc(8,'u');
	addc(8,'v');
	addc(9,'w');
	addc(9,'x');
	addc(9,'y');
	addc(9,'z');
	int t;
	scanf("%d\n",&t);
	for(int times=1;times<=t;++times){
		printf("Scenario #%d:\n",times);
		init();
		work();
		printf("\n");
	}
	return 0;
}
