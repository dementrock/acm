#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=100000;
struct node
{
	int l,r;
	int id;
}nodes[maxn+20];
int tree[maxn+10];
int lowbit(int n)
{
	return n&(n^(n-1));
}
void insert(int n)
{
	while(n<=maxn+10)
	{
		tree[n]++;
		n=n+lowbit(n);
	}
}
int query(int n)
{
	int ans=0;
	while(n>0)
	{
		ans+=tree[n];
		n=n-lowbit(n);
	}
	return ans;
}
bool operator<(const node p1,const node p2)
{
	if(p1.l==p2.l) return p1.r>p2.r;
	else return p1.l<p2.l;
}
int ans[maxn+20];
int main()
{
	int n;
	while(scanf("%d",&n)&&n)
	{
		memset(ans,0,sizeof(ans));
		memset(tree,0,sizeof(tree));
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&nodes[i].l,&nodes[i].r);
			nodes[i].id=i;
		}
		sort(nodes,nodes+n);
		ans[nodes[0].id]=0;
		insert(nodes[0].r);
		int cnt=0;
		for(int i=1;i<n;i++)
		{
			if(nodes[i].l==nodes[i-1].l&&nodes[i].r==nodes[i-1].r) cnt++;
			else cnt=0;
			ans[nodes[i].id]=i-cnt-query(nodes[i].r-1);
			insert(nodes[i].r);
		}
		printf("%d",ans[0]);
		for(int i=1;i<n;i++) printf(" %d",ans[i]);
		printf("\n");
	}
	return 0;
}
