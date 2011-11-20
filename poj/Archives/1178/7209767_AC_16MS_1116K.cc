/*
ID: dementr1
PROG: camelot
LANG: C++
*/
#include<stdio.h>
struct news
{
	int x,y;
} knight[1000];
int move[8][2]={{-2,-1},{-2,1},{2,1},{2,-1},
                {-1,-2},{-1,2},{1,-2},{1,2}};
int kingmove[8][2]={{-1,-1},{-1,1},{1,-1},{1,1},{-1,0},{0,-1},{1,0},{0,1}};
int step[35][35][35][35]={};
int kingstep[35][35][35][35]={};
int R,C,kingx,kingy,length=0;
bool canmove[35][35][35][35]={false};
bool canuse[35][35]={true};
inline int max(int a, int b){
	return a>b?a:b;
}
inline int min(int a, int b){
	return a<b?a:b;
}
void bfs(int startx, int starty)
{
	int i,tmpx,tmpy,closed,open;
	news list[1000];
	bool vis[27][31]={false};
	vis[startx][starty]=true;
	list[0].x=startx;
	list[0].y=starty;
	closed=-1;
	open=0;
	while(closed<open)
	{
		closed++;
		for(i=0;i<8;i++)
		{
			tmpx=list[closed].x+move[i][0];
			tmpy=list[closed].y+move[i][1];
			if(0<tmpx&&tmpx<=R&&0<tmpy&&tmpy<=C)
			{
				if(!vis[tmpx][tmpy])
				{
					vis[tmpx][tmpy]=true;
					list[++open].x=tmpx;
					list[open].y=tmpy;
					step[startx][starty][tmpx][tmpy]=step[startx][starty][list[closed].x][list[closed].y]+1;
				}
			}
		}
	}
}
void kingbfs(int startx, int starty)
{
	int i,tmpx,tmpy,closed,open;
	news list[1000];
	bool vis[27][31]={false};
	vis[startx][starty]=true;
	list[0].x=startx;
	list[0].y=starty;
	closed=-1;
	open=0;
	while(closed<open)
	{
		closed++;
		for(i=0;i<8;i++)
		{
			tmpx=list[closed].x+kingmove[i][0];
			tmpy=list[closed].y+kingmove[i][1];
			if(0<tmpx&&tmpx<=R&&0<tmpy&&tmpy<=C)
			{
				if(!vis[tmpx][tmpy])
				{
					vis[tmpx][tmpy]=true;
					list[++open].x=tmpx;
					list[open].y=tmpy;
					kingstep[startx][starty][tmpx][tmpy]=kingstep[startx][starty][list[closed].x][list[closed].y]+1;
				}
			}
		}
	}
}
void work()
{
	int ans=0,chose,endx,endy,carryx,carryy;
	int i,j,k,l;
	for(i=1;i<=R;i++)
		for(j=1;j<=C;j++)
		{
			bfs(i,j);
			kingbfs(i,j);
		}
	for(i=1;i<=R;i++)
		for(j=1;j<=C;j++)
			for(k=1;k<=R;k++)
				for(l=1;l<=C;l++)
					if((i==k&&j==l)||(step[i][j][k][l]>0))
						canmove[i][j][k][l]=true;
	for(i=1;i<=R;i++)
		for(j=1;j<=C;j++)
			canuse[i][j]=true;
	for(k=1;k<=length;k++)
		for(i=1;i<=R;i++)
			for(j=1;j<=C;j++)
				if((knight[k].x!=i||knight[k].y!=j)&&(step[knight[k].x][knight[k].y][i][j]<=0))
				{
					canuse[i][j]=false;
				}
	for(endx=1;endx<=R;endx++)
		for(endy=1;endy<=C;endy++)
		{
			if(!canuse[endx][endy]) continue;
			int sum=0;
			for(i=1;i<=length;i++)
				 sum+=step[knight[i].x][knight[i].y][endx][endy];
			if(ans!=0&&sum>ans) continue;
			for(chose=1;chose<=length;chose++)
				for(carryx=max(kingx-1,1);carryx<=min(kingx+1,R);carryx++)
					for(carryy=max(kingy-1,1);carryy<=min(kingy+1,C);carryy++)
					{
						if(!canmove[knight[chose].x][knight[chose].y][carryx][carryy]) continue;
						if(!canmove[carryx][carryy][endx][endy]) continue;
						int tmp=sum;
						tmp-=step[knight[chose].x][knight[chose].y][endx][endy];
						int stepking=1;
						if(carryx==kingx&&carryy==kingy) stepking=0;
						tmp+=step[knight[chose].x][knight[chose].y][carryx][carryy]+stepking+step[carryx][carryy][endx][endy];
						if(ans==0||tmp<ans)
						{
							ans=tmp;
						}
					}
			if(sum+kingstep[kingx][kingy][endx][endy]<ans) ans=sum+kingstep[kingx][kingy][endx][endy];
		}
	printf("%d\n",ans);
}
void init()
{
	char c;
	R=C=8;
	c=getchar();
	kingx=c-'A'+1;
	c=getchar();
	kingy=c-'0';
	while(1){
		c=getchar();
		if(!('A'<=c&&c<='Z')&&!('0'<=c&&c<='9')) break;
		++length;
		knight[length].x=c-'A'+1;
		c=getchar();
		knight[length].y=c-'0';
	}
}
int main()
{
	init();
	work();
	return 0;
}
