#include<stdio.h>
#define MAXN 200001
inline long long min(long long a, long long b){
	return a<b?a:b;
}
class Node{
	public:
		long long minv, v;
		int size,lc,rc,fa,rev,d;
		void swap(){
			int t=lc;lc=rc;rc=t;
			rev^=1;
		}
		void add(int t){
			minv+=t,v+=t,d+=t;
		}
} node[MAXN];
int cnt=0;
class splaytree{
	private:
		int root;
		void tran(int x){
			if(node[x].rev){
				node[node[x].lc].swap(),node[node[x].rc].swap();
				node[x].rev=0;
			}
			int d;
			if(d=node[x].d){
				node[node[x].lc].add(d),node[node[x].rc].add(d);
				node[x].d=0;
			}
		}
		void update(int x){
			node[x].size=node[node[x].lc].size+node[node[x].rc].size+1;
			node[x].minv=node[x].v;
			node[x].minv=min(node[x].minv,node[node[x].lc].minv);
			node[x].minv=min(node[x].minv,node[node[x].rc].minv); 
		}
		int newnode(int v, int fa){
			int x=++cnt;
			node[x].v=node[x].minv=v;
			node[x].size=1;
			node[x].lc=node[x].rc=0;
			node[x].fa=fa;
			return x;
		}
		int find(int x, int k){
			int lc=node[x].lc;
			if(k==node[lc].size+1) return x;
			if(k<=node[lc].size) return find(lc,k);
			else return find(node[x].rc,k-1-node[lc].size);
		}
		void leftrotate(int x){
			int rc=node[x].rc,fa=node[x].fa;
			tran(x),tran(rc);
			node[x].rc=node[rc].lc;
			node[node[x].rc].fa=x;
			node[rc].lc=x;
			node[x].fa=rc;
			node[rc].fa=fa;
			if(fa){
				if(x==node[fa].lc) node[fa].lc=rc;
				else node[fa].rc=rc;
			}
			update(x);
			update(rc);
		}
		void rightrotate(int x){
			int lc=node[x].lc,fa=node[x].fa;
			tran(x),tran(lc);
			node[x].lc=node[lc].rc;
			node[node[x].lc].fa=x;
			node[lc].rc=x;
			node[x].fa=lc;
			node[lc].fa=fa;
			if(fa){
				if(x==node[fa].lc) node[fa].lc=lc;
				else node[fa].rc=lc;
			}
			update(x);
			update(lc);
		}
		void splay(int x, int FA){
			tran(x);
			int fa,Fa;
			while((fa=node[x].fa)!=FA){
				if((Fa=node[fa].fa)==FA){
					if(x==node[fa].lc){
						rightrotate(fa);
					}else{
						leftrotate(fa);
					}
				}else if(x==node[fa].lc){
					if(fa==node[Fa].lc){
						rightrotate(Fa);
						rightrotate(fa);
					}else{
						rightrotate(fa);
						leftrotate(Fa);
					}
				}else{
					if(fa==node[Fa].rc){
						leftrotate(Fa);
						leftrotate(fa);
					}else{
						leftrotate(fa);
						rightrotate(Fa);
					}
				}
			}
			if(!FA) root=x;
		}
	public:
		int find(int k){
			return find(root,k);
		}
		void setroot(int _root){
			root=_root;
		}
		int buildtree(int l, int r, int fa){
			if(l>r) return 0;
			int mid=l+r>>1;
			int x=++cnt;
			node[x].v=node[x].minv=0;
			node[x].size=r-l+1;
			node[x].fa=fa;
			node[x].lc=buildtree(l,mid-1,x);
			node[x].rc=buildtree(mid+1,r,x);
			return x;
		}
		void add(int l, int r, int v){
			splay(l=find(l),0);
			splay(r=find(r+2),l);
			node[node[r].lc].add(v);
		}
		void reverse(int l, int r){
			splay(l=find(l),0);
			splay(r=find(r+2),l);
			node[node[r].lc].swap();
		}
		void revolve(int a, int c, int b){
			b=(b-1)%(c-a+1)+1;
			b=c-b;
			splay(c=find(c+2),0);
			splay(a=find(a),c);
			splay(b=find(b+2),a);
			int x=b;
			while(node[x].rc) x=node[x].rc;
			node[x].rc=node[b].lc;
			node[node[x].rc].fa=x;
			node[b].lc=0; 
		}
		void insert(int x, int p){
			int t1,t2,t3;
			splay(t1=find(x+1),0);
			splay(t2=find(x+2),t1);
			t3=node[t2].lc=newnode(p,t2);
			splay(t3,0);
		}
		void del(int x){
			int t1,t2,t3;
			splay(t1=find(x),0);
			splay(t2=find(x+2),t1);
			node[t2].lc=0;
		}
		long long getmin(int l, int r){
			splay(l=find(l),0);
			splay(r=find(r+2),l);
			return node[node[r].lc].minv;
		}
} T;
void clear(){
	for(char ch=getchar();ch!=' ';ch=getchar());
}
int getn(){
	int res=0;
	for(char ch=getchar();'0'<=ch&&ch<='9';ch=getchar())
		res=res*10+ch-'0';
	return res;
}
int main(){
	int n,m;
	scanf("%d\n",&n);
	T.setroot(T.buildtree(0,n+1,0));
	for(int i=1;i<=n;++i){
		int x=getn();
		T.add(i,i,x);
	}
	scanf("%d\n",&m);
	for(int i=1;i<=m;++i){
		char ch=getchar();
		int x,y,t;
		switch(ch){
			case 'A':
				clear();
				x=getn(),y=getn(),t=getn();
				T.add(x,y,t);
				break;
			case 'R':
				ch=getchar(),ch=getchar(),ch=getchar();
				clear();
				if(ch=='E'){
					x=getn(),y=getn();
					T.reverse(x,y);
				}else{
					x=getn(),y=getn(),t=getn();
					T.revolve(x,y,t);
				}
				break;
			case 'I':
				clear();
				x=getn(),y=getn();
				T.insert(x,y);
				break;
			case 'D':
				clear();
				x=getn();
				T.del(x);
				break;
			case 'M':
				clear();
				x=getn(),y=getn();
				printf("%I64d\n",T.getmin(x,y));
				break;
		}
	}
	return 0;
}
