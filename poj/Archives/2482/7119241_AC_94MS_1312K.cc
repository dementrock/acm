#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN=10010;

int n,w,h;
int tot;
unsigned int y[MAXN*2];                                    //注意要用unsigned int                        2^31+h会超int
int sum[MAXN*8],maxSum[MAXN*8];

struct Point{
    unsigned int x,y;
    int v;
    bool operator<(const Point &p)const{
        return x<p.x;
    }
}points[MAXN*2];

/**//*
    向下找到x所在节点，这一路上都要更新
    注意递归写法，不是x==mid 就return
*/
void insert(int p,int left,int right,int x,int c){
    int mid=(left+right)>>1;
    if(x!=mid){
        if(x<mid)insert(2*p,left,mid-1,x,c);
        else insert(2*p+1,mid+1,right,x,c);
    }
    sum[p]+=c;
    maxSum[p]=maxSum[2*p];
    maxSum[p]=max(maxSum[p],sum[p]-sum[2*p+1]);
    maxSum[p]=max(maxSum[p],sum[p]-sum[2*p+1]+maxSum[2*p+1]);
}
int find(unsigned int x){
    int low=1,high=tot;
    while(high>=low){
        int mid=(high+low)>>1;
        if(y[mid]==x)return mid;
        if(y[mid]>x)high=mid-1;
        else low=mid+1;
    }
}

int main(){
    while(~scanf("%d%d%d",&n,&w,&h)){
        w--;h--;                                  //不含边界
        tot=0;
        for(int i=1;i<=n;i++){
            scanf("%u%u%d",&points[i].x,&points[i].y,&points[i].v);
            y[++tot]=points[i].y;y[++tot]=points[i].y+h+1;
            points[n+i].x=points[i].x,points[n+i].y=points[i].y+h+1,points[n+i].v=-points[i].v;
        }
        sort(y+1,y+1+tot);
        tot=unique(y+1,y+1+tot)-(y+1);
        n=n*2;
        sort(points+1,points+1+n);
        memset(sum,0,sizeof(sum));
        memset(maxSum,0,sizeof(maxSum));
        int ans=0,s=1,t=1;
        while(t<=n){                                //注意不要按x坐标扫，会超时
            int x=points[t].x;
            while(s<=n&&x-points[s].x>w)
                insert(1,1,tot,find(points[s].y),-points[s].v),s++;
            while(t<=n&&points[t].x==x)                //把同一列的加进去
                insert(1,1,tot,find(points[t].y),points[t].v),t++;
            ans=max(ans,maxSum[1]);                    //求连续一段的和
        }
        printf("%d\n",ans);
    }
    return 0;
}
