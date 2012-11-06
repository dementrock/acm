#include<iostream>
using namespace std;
struct news
{
	int a,b,c;
} e[10001];
int father[10001];
int n,num,ans;
void init()
{
	int tmp;
	memset(f,0,sizeof(f));
	memset(e,0,sizeof(e));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>tmp;
			if(j>i)
			{
				num++;
				e[num].a=i;
				e[num].b=j;
				e[num].c=tmp;
			}
		}
}
void swap(news *a, news *b){ news x=*a;*a=*b;*b=x;}
int partition(int left, int right)
{
	int i=left+right>>1,j;
	swap(&e[i],&e[right]);
	for(j=left,i=left-1;j<right;j++)
		if(e[j].c<e[right].c) swap(&e[++i],&e[j]);
	swap(&e[++i],&e[right]);
	return i;
}
void quicksort(int left, int right)
{
	if(left>=right) return;
	int i=partition(left,right);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
int getfather(int x)
{
	if(father[x]==x) return x;
	return getfather(father[x]);
}
void together(int a, int b, int c)
{
	if(a==b) return;
	father[a]=b;
	ans+=c;
}
void work()
{
	quicksort(1,num);
	for(int i=1;i<=n;i++)
		father[i]=i;
	for(int i=1;i<=num;i++)
		together(getfather(e[i].a),getfather(e[i].b),e[i].c);
}
void print()
{
	cout<<ans<<endl;
}
int main()
{
	while(cin>>n)
	{
		init();
		work();
		print();
	}
	return 0;
}
