/*
Netflow SAP Algorithm
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,m,v[201][201],oo=99999999;
int list[201],layer[201],s,t;
int path[201],ans,minf=oo;
bool found=false;
int counter[301];
/* ********** BEGIN ************ */
void aug(int now)
{
	int i,tmp=minf,minl=t;
	if(now==t)
	{
		found=true;
		ans+=minf;
		return;
	}
	for(i=s;i<=t;++i)
	{
		if(v[now][i]>0)
		{
			if(layer[now]==layer[i]+1)
			{
				if(v[now][i]<minf) minf=v[now][i];
				aug(i);
				if(layer[s]>t) return;
				if(found) break;
				minf=tmp;
			}
			if(layer[i]<minl) minl=layer[i];
		}
	}
	if(!found)
	{
		--counter[layer[now]];
		if(counter[layer[now]]==0) layer[s]=t+1;
		layer[now]=minl+1;
		++counter[layer[now]];
	}
	else
	{
		v[now][i]-=minf;
		v[i][now]+=minf;
	}
}
void sap()
{
	memset(list,0,sizeof(list));
	memset(layer,0,sizeof(layer));
	memset(path,0,sizeof(path));
	memset(counter,0,sizeof(counter));
	counter[0]=t+1;
	ans=0;
	while(layer[s]<=t)
	{
		minf=oo;
		found=false;
		aug(s);
	}
}
/* ********** END ************ */
int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int x,y,z;
		scanf("%d %d %d\n",&x,&y,&z);
		--x,--y;
		v[x][y]+=z;
	}
	counter[0]=m;
	s=0,t=m-1;
	sap();
	printf("%d\n",ans);
	return 0;
}

/* Binary Index Tree */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct news
{
	int id,num;
} ta[50001];
__int64 a[50001],b[50001],c[50001],d[50001],e[50001],n,ans[10],data[50001];
void swap(news &a, news &b)
{
	news x=a;a=b;b=x;
}
int partition(news a[], int left, int right)
{
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	for(j=left,i=left-1;j<right;++j)
		if(a[j].num<a[right].num)
			swap(a[++i],a[j]);
	swap(a[++i],a[right]);
	return i;
}
void quicksort(news a[], int left, int right)
{
	if(left>=right) return;
	int i=partition(a,left,right);
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}
int lowbit(int k)
{
	return k&(-k);
}
long long sum(int k)
{
	long long ans=0,t=k;
	while(t>0)
	{
		ans+=data[t];
		t-=lowbit(t);
	}
	return ans;
}
void change(int id, __int64 k)
{
	int t=id;
	while(t<=n)
	{
		data[t]+=k;
		t+=lowbit(t);
	}
}
void init()
{
	int t=1;
	if(scanf("%d\n",&n)==EOF) exit(0);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	memset(d,0,sizeof(d));
	memset(ans,0,sizeof(ans));
	memset(ta,0,sizeof(ta));
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		ta[i].id=i;
		scanf("%d",&ta[i].num);
	}
	quicksort(ta,1,n);
	for(int i=1;i<=n;++i)
	{
		a[ta[i].id]=t;
		if(t==n||ta[i].num!=ta[i+1].num) ++t;
	}
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		change(a[i],1);
		b[i]=sum(a[i]-1);
	}
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		change(a[i],b[i]);
		c[i]=sum(a[i]-1);
	}
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		change(a[i],c[i]);
		d[i]=sum(a[i]-1);
	}
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		change(a[i],d[i]);
		ans[0]+=sum(a[i]-1);
		for(int i=1;i<=9;++i)
		{
			ans[i]+=ans[i-1]/10000000;
			ans[i-1]%=10000000;
		}
	}
}
void print()
{
	int i;
	for(i=9;i>=0;--i) if(ans[i]!=0) break;
	printf("%I64d",ans[i]);
	for(--i;i>=0;--i)
	{
		if(ans[i]<1000000)
			printf("0");
		if(ans[i]<100000)
			printf("0");
		if(ans[i]<10000)
			printf("0");
		if(ans[i]<1000)
			printf("0");
		if(ans[i]<100)
			printf("0");
		if(ans[i]<10)
			printf("0");
		printf("%I64d",ans[i]);
	}
	printf("\n");
}
int main()
{
	while(1){
	init();
	work();
	print();}
	return 0;
}

/* SBT */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct sbt
{
	int l,r,s,w;
} t[50001];
int tot=0,cut[50001],cutlist[50001],t1,t2,root;
inline int max(int a, int b){return a>b?a:b;}
inline int min(int a, int b){return a<b?a:b;}
void rightrotate(int &k)
{
	int p=t[k].l;
	t[k].l=t[p].r;
	t[p].r=k;
	t[p].s=t[k].s;
	t[k].s=t[t[k].l].s+t[t[k].r].s+1;
	k=p;
}
void leftrotate(int &k)
{
	int p=t[k].r;
	t[k].r=t[p].l;
	t[p].l=k;
	t[p].s=t[k].s;
	t[k].s=t[t[k].l].s+t[t[k].r].s+1;
	k=p;
}
void maintain(int &k, int flag)
{
	if(flag)
	{
		if(t[t[t[k].l].l].s>t[t[k].r].s)
			rightrotate(k);
		else if(t[t[t[k].l].r].s>t[t[k].r].s)
		{
			leftrotate(t[k].l);
			rightrotate(k);
		}
		else return;
	}
	else
	{
		if(t[t[t[k].r].r].s>t[t[k].l].s)
			leftrotate(k);
		else if(t[t[t[k].r].l].s>t[t[k].l].s)
		{
			rightrotate(t[k].r);
			leftrotate(k);
		}
		else return;
	}
	maintain(t[k].l,false);
	maintain(t[k].r,true);
	maintain(k,false);
	maintain(k,true);
}
void insert(int &now, int w)
{
	if(now==0)
	{
		t[++tot].l=0;
		t[tot].r=0;
		t[tot].s=1;
		t[tot].w=w;
		now=tot;
		return;
	}
	if(w<t[now].w) insert(t[now].l,w);
	else insert(t[now].r,w);
	t[now].s=t[t[now].l].s+t[t[now].r].s+1;
	maintain(now,w<t[now].w);
}
int del(int &now, int w)
{
	--t[now].s;
	if(t[now].w==w
	||w<t[now].w&&t[now].l==0
	||w>=t[now].w&&t[now].r==0)
	{
		int tmp=t[now].w;
		if(t[now].l==0||t[now].r==0)
			now=t[now].l+t[now].r;
		else
			t[now].w=del(t[now].l,w+1);
		return tmp;
	}
	else
		if(w<t[now].w)
			return del(t[now].l,w);
	else return del(t[now].r,w);
}
void find1(int now, int p)
{
	if(p>=t[now].w)
	{
		t1=max(t1,t[now].w);
		if(t[now].r)
			find1(t[now].r,p);
	}
	else
		if(t[now].l)
			find1(t[now].l,p);
}
void find2(int now, int p)
{
	if(p<=t[now].w)
	{
		t2=min(t2,t[now].w);
		if(t[now].l)
			find2(t[now].l,p);
	}
	else
		if(t[now].r)
			find2(t[now].r,p);
}
int main()
{
	char c;
	int n,m,q;
	int root=0,last=0;
	scanf("%d %d\n",&n,&m);
	insert(root,0);
	insert(root,n+1);
	for(int i=1;i<=m;++i)
	{
		scanf("%c",&c);
		if(c=='R')
		{
			scanf("\n");
			if(cutlist[0])
				if(cut[cutlist[cutlist[0]]])
				{
					cut[cutlist[cutlist[0]]]=false;
					del(root,cutlist[cutlist[0]]);
					--cutlist[0];
				}
		}
		else if(c=='D')
		{
			scanf(" %d\n",&last);
			cutlist[++cutlist[0]]=last;
			if(!cut[cutlist[cutlist[0]]])
			{
				cut[cutlist[cutlist[0]]]=true;
				insert(root,cutlist[cutlist[0]]);
			}
		}
		else
		{
			scanf(" %d\n",&q);
			if(cut[q])
				printf("0\n");
			else
			{
				t1=-1,t2=99999;
				find1(root,q);
				find2(root,q);
				if(t2-t1-1<0)
					printf("0\n");
				else printf("%d\n",t2-t1-1);
			}
		}
	}
	return 0;
}

/* SPFA */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000
#define MAXM 5000
struct Edge
{
	int v;
	double w;
	Edge *next;
} *edge[MAXM+1],mempool[MAXM+1];
int vis[MAXN+1],que[MAXN+1],c[MAXN+1],
map[MAXN+1][MAXN+1],
closed,Open,m,n,memnum;
double dis[MAXN+1],v[MAXN+1][MAXN+1],f[MAXN+1],l,r,mid,oo=1999999999;
void add(int u, int v, double w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}
int spfa(double mid)
{
	for(int i=1;i<=n;++i) dis[i]=oo;
	memset(vis,0,sizeof(vis));
	memset(c,0,sizeof(c));
	memset(que,0,sizeof(que));
	dis[1]=0;
	vis[1]=true;
	que[0]=1;
	closed=-1,Open=0;
	while(closed!=Open)
	{
		closed=(closed+1)%n;
		int now=que[closed];
		if(c[now]>n) return 0;
		for(Edge *tmp=edge[now];tmp!=NULL;tmp=tmp->next)
			if(dis[now]+tmp->w*mid-f[now]<dis[tmp->v])
			{
				dis[tmp->v]=dis[now]+tmp->w*mid-f[now];
				if(!vis[tmp->v])
				{
					Open=(Open+1)%n;
					vis[tmp->v]=true;
					que[Open]=tmp->v;
					++c[tmp->v];
					if(c[tmp->v]>n) return 0;
				}
			}
		vis[now]=false;
	}
	return 1;
}
void init()
{
	int x,y;
	double z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lf",&f[i]);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%lf",&x,&y,&z);
		add(x,y,z);
		v[x][y]=z;
		map[x][y]=true;
	}
}
void work()
{
	l=0,r=1000.0;
	while(r-l>0.0001)
	{
		mid=0.5*(l+r);
		if(spfa(mid))
			r=mid;
		else l=mid;
	}
	printf("%.2lf\n",l);
}
int main()
{
	init();
	work();
	return 0;
}

/* RMQ & LCA */
void find(int l, int k)
{
	if(k==0){ f[l][k]=num[l];return;}
	if(!f[l][k-1]) find(l,k-1);
	if(!f[l+(1<<(k-1))][k-1]) find(l+(1<<(k-1)),k-1);
	f[l][k]=max(f[l][k-1],f[l+(1<<(k-1))][k-1]);
}
int rmq(int l, int r)
{
	if(l>=r) return 0;
	int m=(int)(log(1.0*(r-l+1))/log(2.0)),
		mr=r-(1<<m)+1;
	if(!f[l][m]) find(l,m);
	if(!f[mr][m]) find(mr,m);
	return max(f[l][m],f[mr][m]);
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
