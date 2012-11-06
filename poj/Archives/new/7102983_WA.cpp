#include<string>
#include<iostream>
#include<string.h>
using namespace std;
int frac[10]={1,1,2,6,24,120,720,5040,40320,362880};
struct eight
{
	int x,y,a[4][4],former,step;
} list[300001];
int Closed=-1,Open=0,hash[400000],move[4][2]={{-1,0},{1,0},{0,-1},{0,1}},endhash;
char movestep[4]={'l','r','d','u'};
int contor(int a[4][4])
{
	int t[10]={},tmp=0,vis[10]={},sum=0,ans=0;
	for(int i=1;i<=3;++i) for(int j=1;j<=3;++j) t[++tmp]=a[i][j];
	for(int i=1;i<=9;++i)
	{
		sum=0;
		for(int j=0;j<t[i];++j) sum+=1-vis[j];
		ans+=sum*frac[9-i];
		vis[t[i]]=1;
	}
	return ans;
}
void init()
{
	char c;
	int ta[4][4]={};
	for(int i=1;i<=3;++i)
		for(int j=1;j<=3;++j) ta[i][j]=(i-1)*3+j;
	ta[3][3]=0;
	endhash=contor(ta);
	for(int i=1;i<=9;++i)
	{
		cin>>c;
		if(c=='x')
		{
			list[0].x=(i-1)/3+1;
			list[0].y=(i-1)%3+1;
		}
		else
			list[0].a[(i-1)/3+1][(i-1)%3+1]=c-'0';
	}
	hash[contor(list[0].a)]=1;
}
int check(int x)
{
	return 1<=x&&x<=3;
}
void work()
{
	int x,y,nowx,nowy,ta[4][4]={};
	while(Closed!=Open)
	{
		++Closed;
		x=list[Closed].x,y=list[Closed].y;
		for(int i=0;i<4;++i)
		{
			nowx=x+move[i][0],nowy=y+move[i][1];
			if(check(nowx)&&check(nowy))
			{
				memcpy(ta,list[Closed].a,sizeof(list[Closed].a));
				swap(ta[nowx][nowy],ta[x][y]);
				int nowhash=contor(ta);
				if(!hash[nowhash])
				{
					++Open;
					list[Open].x=nowx;
					list[Open].y=nowy;
					memcpy(list[Open].a,ta,sizeof(ta));
					list[Open].former=Closed;
					list[Open].step=i;
					hash[nowhash]=1;
				}
				if(nowhash==endhash)
					return;
			}
		}
	}
	cout<<"unsolvable"<<endl;
	exit(0);
}
void print()
{
	string ans;
	int now=Open;
	while(now!=0)
	{
		ans+=movestep[list[now].step];
		now=list[now].former;
	}
	for(int i=ans.length()-1;i>=0;--i) cout<<ans[i];
	cout<<endl;
}
int main()
{
	init();
	work();
	print();
	return 0;
}
