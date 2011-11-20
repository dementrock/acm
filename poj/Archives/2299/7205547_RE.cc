#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#define MAXN 10001
#define oo 99999999
using namespace std;
struct SplayTree{
	struct SplayNode{
		int v,Size;
		SplayNode *c[2],*f;
	} *Root,*Null,mempool[MAXN];
	int memnum;
	SplayNode *newsplaynode(int v, SplayNode *f){
		SplayNode *t=&mempool[memnum++];
		t->v=v;
		t->f=f;
		t->c[0]=t->c[1]=Null;
		t->Size=1;
	}
	void update(SplayNode *x){
		if(x==Null) return;
		x->Size=x->c[0]->Size+x->c[1]->Size+1;
	}
	void init(){
		memnum=0;
		Null=NULL;
		Null=&mempool[memnum++];
		Null->v=-oo;
		Null->f=NULL;
		Null->c[0]=Null->c[1]=NULL;
		Null->Size=0;
		Root=newsplaynode(-oo,Null);
	}
	void rotate(SplayNode *x, int d){
		SplayNode *y=x->f;
		y->c[d]=x->c[!d];
		x->c[!d]->f=y;
		x->f=y->f;
		if(y->f->c[0]==y)
			y->f->c[0]=x;
		else
			y->f->c[1]=x;
		y->f=x;
		x->c[!d]=y;
		update(y);
		update(x);
		if(Root==y) Root=x;
	}
	void splay(SplayNode *x, SplayNode *f){
		while(x->f!=f){
			if(x->f->f==f){
				if(x==x->f->c[0])
					rotate(x,0);
				else
					rotate(x,1);
			}else if(x==x->f->c[0]){
				if(x->f==x->f->f->c[0]){
					rotate(x->f,0),rotate(x,0);
				}else{
					rotate(x,0),rotate(x,1);
				}
			}else{
				if(x->f==x->f->f->c[1]){
					rotate(x->f,1),rotate(x,1);
				}else{
					rotate(x,1),rotate(x,0);
				}
			}
		}
	}
	int insert(int v){
		SplayNode *x=Root;
		int rank=0;
		for(;;){
			int c=v<x->v&&x->c[0]==Null||v>=x->v&&x->c[1]==Null;
			if(v<x->v&&x->c[0]==Null||v>=x->v&&x->c[1]==Null){
				x->c[v<x->v?0:1]=newsplaynode(v,x);
				if(v>=x->v)
					rank+=x->c[0]->Size+1;
				splay(x->c[v<x->v?0:1],Root);
				return rank;
			}else{
				if(v<x->v){
					x=x->c[0];
				}else{
					rank+=x->c[0]->Size+1;
					x=x->c[1];
				}
			}
		}
	}
} tree;
int main(){
	int N,K,x,now,ans=0,ansi;
	while(scanf("%d",&N)!=EOF){
		if(!N) break;
		tree.init();
		now=0;
		for(int i=1;i<=N;++i){
			scanf("%d",&x);
			now+=i-tree.insert(x);
		}
		printf("%d\n",now);
	}
	return 0;
}
