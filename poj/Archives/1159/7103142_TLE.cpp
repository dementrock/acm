#include<iostream>
#include<string>
using namespace std;
short f[5001][5001],n;
string s,ts;
inline short max(short x, short y){return x>y?x:y;}
void dp(int x, int y)
{
	f[x][y]=0;
	if(!x||!y) return;
	if(f[x][y-1]==-1) dp(x,y-1);
	if(f[x-1][y]==-1) dp(x-1,y);
	f[x][y]=max(f[x][y-1],f[x-1][y]);
	if(s[x-1]==ts[y-1])
	{
		if(f[x-1][y-1]==-1) dp(x-1,y-1);
		f[x][y]=max(f[x][y],f[x-1][y-1]+1);
	}
}
int main()
{
	cin>>n>>s;
	for(int i=s.length()-1;i>=0;--i) ts+=s[i];
	memset(f,0xff,sizeof(f));
	f[0][0]=0;
	dp(s.length(),s.length());
	cout<<s.length()-f[s.length()][s.length()]<<endl;
	return 0;
}
