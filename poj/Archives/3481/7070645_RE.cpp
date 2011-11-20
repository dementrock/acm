#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct sbt
{
	int l,r,s,w,id;
} t[100001];
int data[100001],tot,root;
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
void insert(int &now, int w, int id)
{
	if(!now)
	{
		t[++tot].l=0;
		t[tot].r=0;
		t[tot].s=1;
		t[tot].w=w;
		t[tot].id=id;
		now=tot;
		return;
	}
	if(w<t[now].w) insert(t[now].l,w,id);
	else insert(t[now].r,w,id);
	t[now].s=t[t[now].l].s+t[t[now].r].s+1;
	maintain(now,w<t[now].w);
}
int del(int &now, int w)
{
	--t[now].s;
	if(w==t[now].w
	||w<t[now].w&&!t[now].l
	||w>=t[now].w&&!t[now].r)
	{
		int tmp=t[now].w;
		if(!t[now].l||!t[now].r)
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
int select(int now, int p)
{
	if(p==t[t[now].l].s+1)
		return now;
	else if(p<t[t[now].l].s+1)
		return select(t[now].l,p);
	else return select(t[now].r,p-1-t[t[now].l].s);
}
int main()
{
	int type,k,p,counter=0;
	while(1)
	{
		scanf("%d",&type);
		if(!type) break;
		if(type==2)
		{
			if(!counter)
				printf("0\n");
			else
			{
				int now=select(root,counter);
				printf("%d\n",t[now].id);
				if(counter) --counter;
				del(root,t[now].w);
			}
		}
		else if(type==3)
		{
			if(!counter)
				printf("0\n");
			else
			{
				int now=select(root,1);
				printf("%d\n",t[now].id);
				if(counter) --counter;
				del(root,t[now].w);
			}
		}
		else
		{
			++counter;
			scanf("%d%d",&k,&p);
			data[k]=p;
			insert(root,p,k);
		}
	}
	return 0;
}
