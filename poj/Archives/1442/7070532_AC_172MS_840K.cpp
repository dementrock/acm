#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct sbt
{
	int l,r,s,w;
} t[30001];
int tot,root,m,n,a[30001]={},b[30001]={};
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
	if(!now)
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
int select(int now ,int p)
{
	if(p==t[t[now].l].s+1)
		return t[now].w;
	else if(p<t[t[now].l].s+1)
		return select(t[now].l,p);
	else return select(t[now].r,p-1-t[t[now].l].s);
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&b[i]);
		for(int j=b[i-1]+1;j<=b[i];++j) insert(root,a[j]);
		printf("%d\n",select(root,i));
	}
	return 0;
}
