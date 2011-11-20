/*
ID: dementr1
PROG: ditch
LANG: C++
*/
#include<iostream>
//#include<fstream>
using namespace std;
//ifstream fin("ditch.in");
//ofstream fout("ditch.out");
int leave[201][201]={},v[201][201]={},N,M,level[201]={},newpic[201][201]={};
void init()
{
	int i,a,b,tmp;
	cin>>N>>M;
	for(i=0;i<N;i++)
	{
		cin>>a>>b>>tmp;
		v[a][b]+=tmp;
		leave[a][b]=v[a][b];
	}
}
void createlevel()
{
	int save[201]={},closed=-1,open=0,now,i;
	memset(level,0,sizeof(level));
	level[1]=0;
	save[0]=1;
	while(closed<open)
	{
		closed++;
		now=save[closed];
		for(i=now+1;i<=M;i++)
		{
			if(leave[now][i]>0)
			{
				if(level[i]==0)
				{
					open++;
					save[open]=i;
					level[i]=level[now]+1;
				}
				else if(level[i]>level[now+1]) level[i]=level[now]+1;
			}
		}
	}
}
/*void print(int p[])
{
	int i;
	for(i=0;i<p[0];i++)
		cout<<p[i+1]<<" ";
	cout<<endl;
}
void print(int l[][201])
{
	int i,j;
	for(i=1;i<=M;i++)
	{
		for(j=1;j<=M;j++)
			cout<<l[i][j]<<" ";
		cout<<endl;
	}
}*/
void dinic()
{
	int p[201]={},u,i,min;
	p[0]=1;
	p[1]=1;
	while(1)
	{
		createlevel();
		if(level[M]==0) break;
	//	cout<<"YYYes"<<endl;
		while(1)
		{
			u=p[p[0]];
			if(u!=M)
			{
				bool flag=false;
				for(i=1;i<=M;i++)
					if(level[i]==level[u]+1)
					{
						p[0]++;
						p[p[0]]=i;
						flag=true;
						//print(p);
			//			cout<<u<<" "<<"Yes3"<<endl<<p[0]<<endl;
						break;
					}
				if(!flag)
				{
			//		cout<<u<<endl;
					//level[u]=0;
					p[0]--;
					for(i=1;i<=M;i++)
					{
						if(level[i]==level[u]+1)
							level[i]=0;
			//			cout<<level[i]<<" ";
					}
					level[u]=0;
			//		cout<<endl;
				}
			//	cout<<"Yes1"<<endl;
			//	cout<<p[0]<<endl;
			}
			if(u!=M&&p[0]==0) break;
			if(u==M)
			{
				min=leave[p[1]][p[2]];
				for(i=2;i<p[0];i++)
					if(leave[p[i]][p[i+1]]<min) min=leave[p[i]][p[i+1]];
				for(i=1;i<p[0];i++)
					leave[p[i]][p[i+1]]-=min;
				for(i=1;i<p[0];i++)
					if(leave[p[i]][p[i+1]]==0)
					{
						p[0]=i;
						break;
					}
			//	print(leave);
				break;
			//	cout<<"Yes2"<<endl;
			}
			//system("pause");
		}
	}
	int max=-1,ans=0;
	for(i=1;i<M;i++)
		if(v[i][M]-leave[i][M]>0) ans+=v[i][M]-leave[i][M];
	cout<<ans<<endl;
}	
int main()
{
	int i;
	init();
	createlevel();
	dinic();
	return 0;
}
