#include<stdio.h>
#include<stdlib.h>
struct news
{
	int x1,y1,x2,y2;
} data[1000001];
int tot,llx,lly,urx,ury,color;
int n,a,b,minc=99999999,maxc=0;
int ans;
inline int max(int a, int b)
{
	return a>b?a:b;
}
inline int min(int a, int b)
{
	return a<b?a:b;
}
bool cross(int x1, int x2, int x3, int x4)
{
	if(x4<x1||x3>x2) return false;
	return true;
}
void add(int x1, int y1, int x2, int y2)
{
	++tot;
	data[tot].x1=x1;
	data[tot].x2=x2;
	data[tot].y1=y1;
	data[tot].y2=y2;
}
void cut(int x1, int y1, int x2, int y2,int type)
{
	if(type==1)
	{
		int k1=max(x1,llx),k2=min(x2,urx);
		if(x1<k1) add(x1,y1,k1,y2);
		if(k2<x2) add(k2,y1,x2,y2);
		cut(k1,y1,k2,y2,type+1);
	}
	else
	{
		int k1=max(y1,lly),k2=min(y2,ury);
		if(y1<k1) add(x1,y1,x2,k1);
		if(k2<y2) add(x1,k2,x2,y2);
	}
}
int main()
{
	scanf("%d\n",&n);
	int a,b,h;
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d %d\n",&a,&b,&h);
		llx=a,lly=0,urx=b,ury=h;
		int t=tot;
		for(int j=1;j<=t;++j)
		{
			if(cross(llx,urx,data[j].x1,data[j].x2)&&
			   cross(lly,ury,data[j].y1,data[j].y2))
			{
				cut(data[j].x1,data[j].y1,data[j].x2,data[j].y2,1);
				data[j]=data[t];
				data[t]=data[tot];
				--t;
				--j;
				--tot;
			}
		}
		add(llx,lly,urx,ury);
	}
	for(int k=1;k<=tot;++k)
		ans+=(data[k].x2-data[k].x1)*(data[k].y2-data[k].y1);
	printf("%d\n",ans);
	return 0;
}
