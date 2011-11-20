#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int N=20001,M=10001;
int f[10000001];
int pp[M];
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
struct Node
{
       int l,r,mid;
       int p;
}seg[4*N];
void create(int l,int r,int num)
{   
     seg[num].l=l;
     seg[num].r=r;
     seg[num].mid=(l+r)>>1;
     seg[num].p=0;
     if(l==r) return ;
     create(l,l+r>>1,2*num);
     create((l+r>>1)+1,r,2*num+1);    
}
void insert(int a,int b,int num,int p)
{
     if(seg[num].l==seg[num].r||(a==seg[num].l&&b==seg[num].r))
     {
           seg[num].p=p;
           return ;
     }
     int x=seg[num].p;
     if(x)
     seg[2*num].p=seg[num*2+1].p=x;
     seg[num].p=0;
     if(seg[num].mid<a) insert(a,b,2*num+1,p);
     else if(seg[num].mid>=b) insert(a,b,2*num,p);
     else
     {
          insert(a,seg[num].mid,2*num,p);
          insert(seg[num].mid+1,b,2*num+1,p);
     }
}
void poster(int num)
{
     if(seg[num].p) {pp[seg[num].p]=1;return ;}
     if(seg[num].r==seg[num].l) return ;
     poster(2*num);
     poster(2*num+1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("ooo.txt","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
         int n,a[N],b[N],num[2*N]={0};
         create(1,N,1);
         scanf("%d",&n);
         for(int i=1;i<=n;i++)
         {
             scanf("%d%d",&a[i],&b[i]);
             num[2*(i-1)]=a[i];
             num[2*(i-1)+1]=b[i];
             f[a[i]]=f[b[i]]=0;
         }
         qsort(num,2*n,sizeof(num[0]),cmp);
         int j=0;
         f[num[0]]=++j;
         for(int i=1;i<2*n;i++)
             if(num[i]!=num[i-1]) f[num[i]]=++j;
        
         for(int i=1;i<=n;i++)
              insert(f[a[i]],f[b[i]],1,i);
         memset(pp,0,sizeof(pp));
         poster(1);
         int ans=0;
         for(int i=1;i<=n;i++) ans+=pp[i];
         printf("%d\n",ans);
    }
}