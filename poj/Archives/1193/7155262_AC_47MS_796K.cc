#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 10001
struct Mem{
	int start,end;
	Mem *next;
} *memhead,mempool[MAXN];
struct Process{
	int t,p,m,id;
} P[MAXN],wque[MAXN];
struct Heap{
	int t,id,start,end;
} h[MAXN];
int memnum,tot,n,size,oo=(1<<31)-1,head=0,tail=0,anst;

inline Mem *newspace(){
	return &mempool[memnum++];
}

inline int max(int a, int b){
	return a>b?a:b;
}

void init(){
	memhead=newspace();
	memhead->start=tot,memhead->end=tot;
	Mem *tmp=newspace();
	tmp->start=-1,tmp->end=-1;
	tmp->next=memhead;
	memhead=tmp;
}

void getin(){
	int t,m,p;
	scanf("%d",&tot);
	while(scanf("%d%d%d",&t,&m,&p)){
		if(!t&&!m&&!p) break;
		P[++n].t=t;
		P[n].p=p;
		P[n].m=m;
		P[n].id=n;
	}
}

Mem *find(int need){
	for(Mem *tmp=memhead;tmp->next!=NULL;tmp=tmp->next)	{
		if(tmp->next->start-tmp->end-1>=need)
			return tmp;
	}
	return 0;
}

void comb(Mem *start){
	for(Mem *tmp=start;tmp->next!=NULL;tmp=tmp->next){
		if(tmp->next->start==tmp->end+1){
			if(tmp->next->next==NULL) return;
			tmp->end=tmp->next->end;
			tmp->next=tmp->next->next;
		}
		else return;
	}
} 

void swap(Heap &a, Heap &b){
	Heap x=a;
	a=b;
	b=x;
}


void heapup(int now){
	while(now>1&&h[now].t<h[now>>1].t){
		swap(h[now],h[now>>1]);
		now>>=1;
	}
}

void heapdown(int now){
	while(1){
		int l=now<<1,r=l+1,heapmin=now;
		if(l<=size&&h[l].t<h[heapmin].t) heapmin=l;
		if(r<=size&&h[r].t<h[heapmin].t) heapmin=r;
		if(heapmin==now) break;
		swap(h[heapmin],h[now]);
		now=heapmin;
	}
}

void insert(int endtime, int id, int start, int end){
	h[++size].t=endtime;
	h[size].id=id;
	h[size].start=start;
	h[size].end=end;
	heapup(size);
}

void extmin(){
	h[1]=h[size--];
	heapdown(1);
}

void del(int start, int end){
	Mem *tmp=newspace();
	tmp->next=memhead;
	for(tmp->next;tmp->next!=NULL;tmp=tmp->next){
		int tstart=tmp->next->start,tend=tmp->next->end;
		if(tstart<=start&&tend>=end){
			if(tstart==start&&tend==end){ 		  //delete directly
				if(start==-1){
					tmp->next->end=-1;
				}
				else if(end==tot){
					tmp->next->start=tot;
				}
				else
					tmp->next=tmp->next->next;
			}
			else if(tstart==start){ 			  //cut the head
				tmp->next->start=end+1;
			}
			else if(tend==end){					  //cut the tail
				tmp->next->end=start-1;
			}
			else{
				Mem *newmem=newspace();
				tmp->next->end=start-1;
				newmem->start=end+1;
				newmem->end=tend;
				newmem->next=tmp->next->next;
				tmp->next->next=newmem;
			}
			return;
		}
	}
}

void work(){
	P[n+1].t=oo;
	for(int i=1;i<=n;++i){
		Mem *k=find(P[i].m);
		if(k){
			insert(P[i].t+P[i].p,i,k->end+1,k->end+P[i].m);
			k->end+=P[i].m;
			comb(k);
		}
		else{
			++head;
			wque[head]=P[i];
		}
		while(size&&h[1].t<=P[i+1].t){
			int mint=h[1].t;
			anst=max(anst,mint);
			while(h[1].t==mint&&size){
				del(h[1].start,h[1].end);
				extmin();
			}
			while(tail<head){
				Mem *k=find(wque[tail+1].m);
				if(!k) break;
				++tail;
				insert(mint+wque[tail].p,wque[tail].id,k->end+1,k->end+wque[tail].m);
				k->end+=wque[tail].m;
				comb(k);
			}
		}
	}
}

void print()
{
	printf("%d\n%d\n",anst,head);
}

int main(){
	getin();
	init();
	work();
	print();
	return 0;
}
