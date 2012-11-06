#include<iostream>
#include<string>
using namespace std;
const int MAXN=999999;
int prime[80000],size=0,size2=1,num[80000],final[80000],point,tmp[80000];
bool flag[MAXN+1];
int len(int a[])
{
    int i;
    for(i=80000;i>0;i--) if(a[i-1]!=0) return i;
    return 0;
}
void produce()
{
    int i,j;
    memset(flag,true,sizeof(flag));
    for(i=2;i<=(int)MAXN/2;i++)
        if(flag[i])
            for(j=i<<1;j<=MAXN;j+=i)
                flag[j]=false;
    for(i=2;i<=MAXN;i++) if(flag[i]) prime[size++]=i;
}
void divide(int a, int num[])
{
     int tmp=a,i;
     while(tmp>1)
         for(i=0;i<80000;i++)
            if(tmp%prime[i]==0)
            {
                num[i]++;
                tmp=tmp/prime[i];
                break;
            }
}
void calc(int num[], int n, int final[])
{
     int i,j,k,t;
     for(i=0;i<80000;i++) num[i]*=n;
     for(i=0;i<80000;i++)
        if(num[i]!=0)
        {
           for(j=0;j<num[i];j++)
           {
              t=0;
              for(k=0;k<size2;k++)
              {
                 final[k]=final[k]*prime[i]+t;
                 t=final[k]/10;
                 final[k]=final[k]%10;
              }
              if(t>0)
              {
                 while(t>0)
                 {
                    final[size2]=t%10;
                    size2++;
                    t=(int)t/10;
                 }
              }
           }
        }
}
void print(int a[])
{
    int lena=size2,i;
    int start=-1;
    for(i=lena-1;i>=lena-point;i--)
    {
        if(a[i]!=0)
        {
            start=i;
            break;
        }
    }
    if(start==-1)
    {
        for(i=0;i<lena-point;i++) cout<<a[i];
        cout<<endl;
    }
    else if(lena<=point)
    {
        cout<<".";
        for(i=point-lena-1;i>=0;i--) cout<<"0";
        for(i=0;i<=start;i++) cout<<a[i];
        cout<<endl;
    }
    else
    {
        for(i=0;i<lena-point;i++)
            cout<<a[i];
        cout<<".";
        for(i=lena-point;i<=start;i++) cout<<a[i];
        cout<<endl;
    }
}
int main()
{
    string ss;
    int s;
    int n,t,i;
    produce();
    while(cin>>ss>>n)
    {
        point=0;
        t=1;
        s=0;
        for(i=ss.length()-1;i>=0;i--)
        {
           if(ss[i]!='.')
           {
              s+=(ss[i]-'0')*t;
              t*=10;
           }
           else point=(ss.length()-i-1)*n;
        }
        memset(num,0,sizeof(num));
        memset(final,0,sizeof(final));
        memset(tmp,0,sizeof(tmp));
        final[0]=1;
        divide(s,num);
        calc(num,n,final);
        size2=len(final);
        for(i=0;i<len(final);i++) tmp[i]=final[len(final)-i-1];
        print(tmp);
    }
    return 0;
}
