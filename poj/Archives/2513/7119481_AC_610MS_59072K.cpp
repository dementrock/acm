#include<stdio.h>
#include<string.h>
#define MAXN 500001
struct Trie
{
	int id;
	Trie *next[26];
} head, mempool[10*MAXN];
int deg[MAXN],memnum,tot,father[MAXN];
int find(char s[])
{
	Trie *snow=&head;
	int i;
	for(i=0;i<strlen(s);++i)
	{
		if(snow->next[s[i]-'a']==NULL)
			break;
		snow=snow->next[s[i]-'a'];
	}
	for(int j=i;j<strlen(s);++j)
	{
		Trie *t=&mempool[memnum++];
		t->id=-1;
		memset(t->next,0,sizeof(t->next));
		snow->next[s[j]-'a']=t;
		snow=t;
	}
	if(snow->id==-1)
		snow->id=++tot;
	return snow->id;
}
int getfather(int x)
{
	if(father[x]==x) return x;
	return father[x]=getfather(father[x]);
}
void together(int a, int b)
{
	int x=getfather(a),y=getfather(b);
	father[x]=y;
}
void judge()
{
	if(!tot)
	{
		printf("Possible\n");
		return;
	}
	else{
		for(int i=2;i<=tot;++i)
			if(getfather(i)!=getfather(i-1))
			{
				printf("Impossible\n");
				return;
			}
		int cnt=0;
		for(int i=1;i<=tot;++i)
			cnt+=deg[i]&1;
		if(cnt==0||cnt==2)
			printf("Possible\n");
		else printf("Impossible\n");
	}
}
int main()
{
	char str1[10],str2[10];
	memset(head.next,0,sizeof(head.next));
	head.id=-1;
	while(~scanf("%s %s\n",str1,str2))
	{
	//	printf("%s %s\n",str1,str2);
		int s1=find(str1),s2=find(str2);
	//	printf("%d %d\n",s1,s2);
		if(!deg[s1]) father[s1]=s1;
		if(!deg[s2]) father[s2]=s2;
		++deg[s1],++deg[s2];
		together(s1,s2);
	}
	judge();
	return 0;
}
