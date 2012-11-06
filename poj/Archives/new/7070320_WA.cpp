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
int rank(int now, int w)
{
	if(!now)
		return 1;
	if(w<t[now].w)
		return rank(t[now].l,w);
	else
		return t[t[now].l].s+rank(t[now].r,w)+1;
}
int select(int now, int p)
{
	if(p==t[t[now].l].s+1)
		return t[now].w;
	if(p<t[now].w)
		return select(t[now].l,p);
	else
		return select(t[now].r,p-1-t[t[now].l].s);
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
void print(int now)
{
//	printf("pp::%d %d %d %d\n",now,t[now].w,t[now].l,t[now].r);
	if(t[now].l) print(t[now].l);
	if(t[now].r) print(t[now].r);
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
			if(!cut[last])
			{
				cutlist[++cutlist[0]]=last;
				cut[cutlist[cutlist[0]]]=true;
				insert(root,last);
			//	printf("-----------\n");
				print(root);
			}
		}
		else
		{
			scanf(" %d\n",&q);
			if(cut[q])
				printf("0\n");
			else
			{
			//	printf("%d\n",q);
				t1=-1,t2=9999;
				find1(root,q);
				find2(root,q);
			//	printf("%d %d\n",t1,t2);
				if(t2-t1-1<0)
					printf("0\n");
				else printf("%d\n",t2-t1-1);
			}
		}
	}
	return 0;
}
