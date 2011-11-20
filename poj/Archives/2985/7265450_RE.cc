#include<stdio.h>
#include<string.h>
#define MAXS 300001
#define oo 1e8
int father[MAXS],sum[MAXS];
struct splaytree{
	struct splaynode{
		int s,v,sum;
		splaynode *c[2],*f;
	} *root,*null,mempool[MAXS];
	int memnum,tot;
	void update(splaynode *x){
		x->s=x->c[0]->s+x->c[1]->s+x->sum;
	}
	splaynode *newsplaynode(int v, splaynode *f){
		splaynode *x=&mempool[memnum++];
		x->v=v,x->s=1,x->sum=1,x->c[0]=x->c[1]=null,x->f=f;
		++tot;
		return x;
	}
	void init(){
		memnum=0;
		null=0;
		null=newsplaynode(-oo,0);
		null->s=null->sum=0;
		root=newsplaynode(-oo,null);
		root->c[1]=newsplaynode(oo,root);
		update(root);
	}
	void rotate(splaynode *x, int o){
		splaynode *y=x->f;
		y->c[o]=x->c[!o];
		x->c[!o]->f=y;
		x->f=y->f;
		if(y->f->c[0]==y)
			y->f->c[0]=x;
		else
			y->f->c[1]=x;
		y->f=x;
		x->c[!o]=y;
		update(y);
		update(x);
		if(root==y) root=x;
	}
	void splay(splaynode *x, splaynode *f){
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
	void insert(int v){
		splaynode *x=root,*f=null;
		int flag=0;
	//	printf("%d\n",v);
		for(;;){
	//		printf("%d %d\n",x->v,x->s);	
			f=x;
			if(v==x->v){
				++x->sum,++tot;
				splay(x,null);
				return;	
			}else if(v<x->v){
				x=x->c[0];
				flag=0;
			}else{
				x=x->c[1];
				flag=1;
			}
			if(!x->s) break;
		}
		x=newsplaynode(v,f);
		f->c[flag]=x;
		splay(x,null);
	}
	void select(int k, splaynode *f){
		splaynode *x;
	//	printt();
		for(x=root;k<x->c[0]->s+1||k>x->c[0]->s+x->sum;){
			if(k<x->c[0]->s+1){
				x=x->c[0];
			}else{
				k-=x->c[0]->s+x->sum;
				x=x->c[1];
			}
		}
		splay(x,f);
	}void printv(splaynode *x){
		printf("%d %d Left:%d %d Right:%d %d\n",x->v,x->sum,x->c[0]->v,x->c[0]->sum,x->c[1]->v,x->c[1]->sum);
		if(x->c[0]->s) printv(x->c[0]);
		if(x->c[1]->s) printv(x->c[1]);
	}
	void printt(){
		printv(root);
	}
	void print(int k){
		select(tot-k-1,null);
		printf("%d\n",root->v);
	}
	splaynode *find(int v){
	//	printf("%d\n",v);
		splaynode *x=root;
		for(;;){
	//	printf("%d %d %d\n",x->v,x->c[0]->v,x->c[1]->v);
			if(v==x->v) return x;
			if(v<x->v&&!x->c[0]->s||v>=x->v&&!x->c[1]->s) break;
			else if(v<x->v){
				x=x->c[0];
			}else{
				x=x->c[1];
			}
		}
		return null;
	}
	int rank(int v){
		splaynode *x=find(v);
	//	printf("ok %d\n",x->v);
		splay(x,null);
	//	printf("ok");
		return root->c[0]->s+1;
	}
	void del(int v){
	//	printf("before:\n");
	//	printt();
	//	printf("after:\n");
		--tot;
		splaynode *x=find(v);
	//	printf("%d %d\n",x->v,x->sum);
		if(x->sum>1){
			--x->sum;
			splay(x,null);
		//	printt();
			return;
		}	
		splay(x,null);
		root->c[0]->f=null;
		splaynode *y=root->c[0];
		while(y->c[1]->s) y=y->c[1];
	//	printf("y");
		y->c[1]=root->c[1],root->c[1]->f=y;
		root=root->c[0];
		splay(y->c[1],null);
	//	printt();
	}
} tree;
int getfather(int x){
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}
int getsum(int x){
	if(father[x]==x) return sum[x];
	else return getsum(father[x]);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	tree.init();
//	printf("ok");
	for(int i=1;i<=n;++i){
		father[i]=i,sum[i]=1;
		tree.insert(1);
	}
	//	printf("ok--");
	for(int i=1,o,x,y;i<=m;++i){
		scanf("%d",&o);
		if(o){
			scanf("%d",&x);
		//	printf("%d %d\n",o,x);
			tree.print(x);
		}else{
			scanf("%d%d",&x,&y);
	//		printf("%d %d %d\n",o,x,y);
			int a=getfather(x),b=getfather(y),
			    na=getsum(x),nb=getsum(y);
//	printf("ok");
			tree.del(na),tree.del(nb),tree.insert(na+nb);
//	printf("ok");
			father[a]=b;
			sum[b]=na+nb;
		}
	//	tree.printt();
	//	printf("\n");
	}
	return 0;
}
