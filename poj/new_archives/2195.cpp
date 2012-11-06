#include<stdio.h>
#include<string.h>
#define MAXN 5100
#define MAXE 100001
#define QMAX 5100
#define oo 0x77777777
struct Edge{
	int v,w,p;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE],*fe[MAXN];
struct point {
    int x, y;
} men[1001], house[1001];
int cntmen, cnthouse;
int memnum,S,T,N,K,piS,cost,vis[MAXN],ins[MAXN],ft[MAXN],
dis[MAXN],Closed,Open,Size,Que[QMAX];

inline int abs(int x) {
    return x >= 0 ? x : -x;
}

inline int mandis(point a, point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, int p, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->w=w,x->p=p,x->next=edge[s],edge[s]=x,x->pair=y;
	y->v=s,y->w=0,y->p=-p,y->next=edge[t],edge[t]=y,y->pair=x;
}
int spfa(){
	memset(dis,0x77,sizeof(dis));
	memset(ins,0,sizeof(ins));
	memset(ft,0,sizeof(ft));
	memset(fe,0,sizeof(fe));
	Closed=-1,Open=0,Que[0]=S,dis[S]=0,ins[S]=1,Size=1;
	while (Size){
		Closed=(Closed+1)%QMAX;
		int now=Que[Closed];
		ins[now]=0,--Size;
		for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
			int j=tmp->v;
			if(tmp->w&&dis[now]+tmp->p<dis[j])
			{
				dis[j]=dis[now]+tmp->p;
				ft[j]=now;
				fe[j]=tmp;
				if(!ins[j]){
					ins[j]=1;
					++Size;
					Open=(Open+1)%QMAX;
					Que[Open]=j;
				}
			}
		}
	}
	return dis[T]<oo;
}
void aug()
{
	int delta=oo;
	for(int i=T;i!=S;i=ft[i]){
		if(fe[i]->w<delta){
			delta=fe[i]->w;
		}
	}
	for(int i=T;i!=S;i=ft[i]){
		fe[i]->w-=delta;
		fe[i]->pair->w+=delta;
		cost+=fe[i]->p*delta;
	}
}
int main(){
    freopen("test.in", "r", stdin);
    int n, m;
    char str[1001];
    while(scanf("%d%d", &n, &m) != EOF) {
        if (!n && !m) {
            break;
        }
        cntmen = cnthouse = 0;
        memset(edge, 0, sizeof(edge));
        memset(mempool, 0, sizeof(mempool));
        memnum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            for (int j = 0; j < m; ++j) {
                if (str[j] == 'm') {
                    men[++cntmen].x = i;
                    men[cntmen].y = j;
                } else if (str[j] == 'H') {
                    house[++cnthouse].x = i;
                    house[cnthouse].y = j;
                }
            }
        }
        S = 0, T = cntmen + cnthouse + 1;
        for (int i = 1; i <= cntmen; ++i) {
            for (int j = 1; j <= cnthouse; ++j) {
                add(i, j + cntmen, mandis(men[i], house[j]), 1);
            }
        }
        for (int i = 1; i <= cntmen; ++i) {
            add(S, i, 0, 1);
        }
        for (int j = 1; j <= cnthouse; ++j) {
            add(j + cntmen, T, 0, 1);
        }
        cost = 0;
        while(spfa()){
            aug();
        }
        printf("%d\n",cost);	
    }
	return 0;
}
