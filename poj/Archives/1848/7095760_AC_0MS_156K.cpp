#include <iostream>
using namespace std;
#define min(a,b) ((a)<(b)?(a):(b))
#define MAXN 101
#define INF 0xffff

int N;
struct Tree 
{
 int selflink;//自连时最小连线数
 int flink;//所有孩子自连时最小连线数
 int clink;//仅有一个孩子非自连(即子树中的某些节点与树外节点构成环)最小连线数
 int c;//child
 int b;//brother
 int f;//father
}tree[MAXN];
char pMatrix[MAXN][MAXN];
char mark[MAXN];

int root;

void getlink(int id)
{
 if (!tree[id].c)
 {//leaf
  tree[id].selflink=tree[id].clink=INF;
  tree[id].flink=0;
  return;
 }
 
 int sum=0;
 int fst=INF,sec=INF;//两个孩子非自连;最小，次小
 int small=INF;//一个孩子clink
 int c=tree[id].c;
 while (c)
 {
  sum+=tree[c].selflink;
  int cur1=min(tree[c].flink,tree[c].clink)-tree[c].selflink;
  if (cur1<=fst)
   sec=fst,fst=cur1;
  else if (cur1<sec)
   sec=cur1;
  small=min(small,tree[c].clink-tree[c].selflink);
  c=tree[c].b;
 }
 int ans=sum+min(fst+sec,small)+1;
 tree[id].selflink=ans>INF?INF:ans;
 ans=sum+fst;
 tree[id].clink=ans>INF?INF:ans;
 tree[id].flink=sum>INF?INF:sum;
}

bool dfs(int id)
{
 if(!id) return true;
 if(!dfs(tree[id].c)) return false;
 getlink(id);
 if(tree[id].flink==INF&&tree[id].clink==INF&&tree[id].selflink==INF)
  return false;
 if(!dfs(tree[id].b)) return false;
 return true;
}

void buildtree(int r)
{
 mark[r]=1;
 int c;
 for (c=1;c<=N;c++)
 {
  if (c==r||!pMatrix[r][c]||mark[c]) continue;
  tree[c].b=tree[r].c;tree[r].c=c;tree[c].f=r;
  buildtree(c);
 }
}

int main()
{
 int i;
 while(EOF!=scanf("%d",&N))
 {
  root=0;
  memset(tree,0,sizeof(tree));
  memset(pMatrix,0,sizeof(pMatrix));
  memset(mark,0,sizeof(mark));
  int id1,id2;
  for(i=1;i<=N-1;i++)
  {
   scanf("%d%d",&id1,&id2);
   pMatrix[id1][id2]=pMatrix[id2][id1]=1;
  }
  root=1;
  buildtree(root);
  if (!dfs(root)||tree[root].selflink>=INF)
   printf("-1\n");
  else printf("%d\n",tree[root].selflink);
 }
 return 0;
}
