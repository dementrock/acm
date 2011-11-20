#include<stdio.h>
#define MAXN 400001
inline int min(int a, int b){
	return a<b?a:b;
}
class Node{
	public:
		int minv, v;
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
		int root,tot;
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
			if(node[x].lc)node[x].minv=min(node[x].minv,node[node[x].lc].minv);
			if(node[x].rc)node[x].minv=min(node[x].minv,node[node[x].rc].minv); 
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
			for(int lc;k!=node[lc=node[x].lc].size+1;){
				tran(x);
				if(k<=node[lc].size) x=lc;
				else{ x=node[x].rc,k-=node[lc].size+1;}
			}
			return x;
			int lc=node[x].lc;
			if(k==node[lc].size+1) return x;
			tran(x);
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
		void init(){
			node[root=cnt=1].v=0;
			node[1].fa=0;
			node[1].size=1;
			node[1].rc=++cnt;
			node[cnt].fa=1;
			node[cnt].size=1;
		}
		void settot(int n){
			tot=n;
		}
		void add(int l, int r, int v){
			if(l<=0||r>tot||l>r) return;
			splay(l=find(l),0);
			splay(r=find(r+2),l);
			node[node[r].lc].add(v);
			splay(node[r].lc,0);
		}
		void reverse(int l, int r){
			if(l<=0||r>tot||l>r) return;
			splay(l=find(l),0);
			splay(r=find(r+2),l);
			node[node[r].lc].swap();
			splay(node[r].lc,0);
		}
		void print(int x){
			if(!x) return;
			print(node[x].lc);
			printf("%d ",node[x].v);
			print(node[x].rc);
		}
		void printtree(){
			print(root);
			printf("\n--------------------------------\n");
		}
		void revolve(int a, int c, int b){
			if(a>=c||a<=0||c>tot) return;
			int Mod=c-a+1;
			b=(b%Mod+Mod)%Mod;
			if(!b) return;
			b=c-b;
			splay(c=find(c+2),0);
			splay(a=find(a),c);
			splay(b=find(b+2),a);
			int x=b;
			while(node[x].rc){tran(x); x=node[x].rc;}
			node[x].rc=node[b].lc;
			node[node[x].rc].fa=x;
			node[b].lc=0;
			splay(node[x].rc,0);
		}
		void insert(int x, int p){
		//	printtree();
			if(x<0||x>tot) return;
			++tot;
			int t1,t2,t3;
			splay(t1=find(x+1),0);
			splay(t2=find(x+2),t1);
			t3=node[t2].lc=newnode(p,t2);
			splay(t3,0);
		//	printtree();
		}
		void del(int x){
			if(x<=0||x>tot||!tot) return;
			--tot;
			int t1,t2,t3;
			splay(t1=find(x),0);
			splay(t2=find(x+2),t1);
			node[t2].lc=0;
			splay(t2,0);
		}
		void getmin(int l, int r){
			if(l>r||l<=0||r>tot) return;
			splay(l=find(l),0);
			splay(r=find(r+2),l);
		//	printtree();
			printf("%d\n",node[node[r].lc].minv);
		}
} T;
int main(){
	int n,m;
	scanf("%d\n",&n);
	char str[100];
	T.init();
	for(int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
		T.insert(i-1,x);
	}
	T.settot(n);
	scanf("%d\n",&m);
	for(int i=1;i<=m;++i){
		scanf("%s",str);
		int x,y,t;
		switch(str[0]){
			case 'A':
				scanf("%d %d %d\n",&x,&y,&t);
		//		printf("%d %d %d\n",x,y,t);
				T.add(x,y,t);
				break;
			case 'R':
				if(str[3]=='E'){
					scanf("%d %d\n",&x,&y);
					T.reverse(x,y);
				}else{
					scanf("%d %d %d\n",&x,&y,&t);
					T.revolve(x,y,t);
				}
				break;
			case 'I':
				scanf("%d %d\n",&x,&y);
				T.insert(x,y);
				break;
			case 'D':
				scanf("%d\n",&x);
				T.del(x);
				break;
			case 'M':
				scanf("%d %d\n",&x,&y);
				T.getmin(x,y);
			//	while(1);
				break;
		}	
	//	T.printtree();
	//	printf("%d\n",i);
	//	printf("%d\n",i);for(int H=1;H<=30000000;++H);
	}
	return 0;
}
