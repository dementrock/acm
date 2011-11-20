#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
const int inf=100000000;
const double pi=acos(-1.0);
const double eps=1e-8;
const int maxn=500000;
const int a[37]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,500001};
const int b[37]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200,1314521};
template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
inline void fill(int *a,int b,int c){
for (int i=0;i<c/4;i++,a++) *a=b;}
int n,c[maxn+1],next[maxn+1];
char name[maxn+1][11];
bool v[maxn+1];
void add(int x,int p){
    while (x<=maxn)
    {
        c[x]+=p;
        x+=x & -x;
    }
}
int get(int x){
    int s=0;
    while (x)
    {
        s+=c[x];
        x-=x & -x;
    }
    return s;
}
int main(){
    int i,j,k,m,t,l,r,mid,p;
    while (scanf("%d%d\n",&n,&k)!=EOF)
    {
        for (p=0;a[p+1]<=n;p++);
        m=a[p];
        for (i=1;i<=n;i++) c[i]=i & -i;
        for (i=1;i<=n;i++) scanf("%s %d",name[i],&next[i]);
        for (i=1;i<m;i++)
        {
            if (next[k]>0) t=(next[k]+get(k)-1)%(n-i);
            else t=(get(k)+next[k])%(n-i);
            if (t<=0) t+=n-i;
            add(k,-1);
            l=1; r=n;
            while (l<=r)
            {
                mid=(l+r)/2;
                if (get(mid)>=t) r=mid-1;
                else l=mid+1;
            }
            k=l;
        }
        printf("%s %d\n",name[k],b[p]);
    }       
    return 0;
}
