#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,root,q1,q2,vis[10001],found,
ancestor[10001],treein[10001][2],degree[10001],indegree[10001],*tree[10001],father[10001];
void init()
{
	found=false;
	memset(degree,0,sizeof(degree));
	memset(ancestor,0,sizeof(ancestor));
	memset(vis,0,sizeof(vis));
	memset(treein,0,sizeof(treein));
	memset(indegree,0,sizeof(indegree));
	scanf("%d",&n);
	for(int i=1;i<=n-1;++i)
	{
		scanf("%d%d",&treein[i][0],&treein[i][1]);
		++degree[treein[i][0]];
		++indegree[treein[i][1]];
	}
	for(int i=1;i<=n;++i)
	{
	//	printf("%d\n",degree[i]);
		father[i]=i;
		if(degree[i])
		{
			tree[i]=new int[degree[i]+1];
			memset(tree[i],0,sizeof(tree[i]));
		}
		if(!indegree[i]) root=i;
	}
	for(int i=1;i<=n-1;++i)
		tree[treein[i][0]][++tree[treein[i][0]][0]]=treein[i][1];
	scanf("%d%d",&q1,&q2);
}
int find(int a)
{
	if(father[a]==a) return a;
	else return find(father[a]);
}
void getunion(int a, int b)
{
	int fa=find(a),fb=find(b);
	father[fa]=fb;
}
void lca(int k)
{
	if(found) return;
	ancestor[k]=k;
	for(int i=1;i<=degree[k];++i)
	{
		lca(tree[k][i]);
		getunion(k,tree[k][i]);
		ancestor[find(k)]=k;
	}
	vis[k]=true;
	if((k==q1&&vis[q2])||(k==q2&&vis[q1]))
	{
		printf("%d\n",ancestor[find(k==q1?q2:q1)]);
		found=true;
	}
}
void work()
{
	lca(root);
}
void clear()
{
	for(int i=1;i<=n;++i)
		delete [] tree[i];
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;++i)
	{
		init();
		work();
		clear();
	}
	return 0;
}
