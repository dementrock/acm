#include <stdio.h>
#include <string.h>
typedef struct
{
        long num[35];
}DATA;
DATA list[100011];
long n;
long cmp(long a[],long b[])
{
     long i;
     for(i=1;i<=7;i++)
     {
      if(a[i]>b[i]) return 1;
      else if(a[i]<b[i]) return -1;
     }
     return 0;
}
void read()
{
     char s[1000];
     long i,j,len,tmp;
     scanf("%ld",&n);
     memset(list[0].num,0,sizeof(list[0].num));
     memset(list[n+1].num,0,sizeof(list[n+1].num));
     for(i=1;i<=n;i++)
     {
      scanf("%s",s+1);
      len=strlen(s+1);
      memset(list[i].num,0,sizeof(list[i].num));
      for(j=1;j<=len;j++)
      {
       if(s[j]=='-') continue;
       list[i].num[0]++;
       if(s[j]=='A'||s[j]=='B'||s[j]=='C') tmp=2;
       if(s[j]=='D'||s[j]=='E'||s[j]=='F') tmp=3;
       if(s[j]=='G'||s[j]=='H'||s[j]=='I') tmp=4;
       if(s[j]=='J'||s[j]=='K'||s[j]=='L') tmp=5;
       if(s[j]=='M'||s[j]=='N'||s[j]=='O') tmp=6;
       if(s[j]=='P'||s[j]=='R'||s[j]=='S') tmp=7;
       if(s[j]=='T'||s[j]=='U'||s[j]=='V') tmp=8;
       if(s[j]=='W'||s[j]=='X'||s[j]=='Y') tmp=9;
       if('0'<=s[j]&&s[j]<='9') tmp=s[j]-'0';
       list[i].num[list[i].num[0]]=tmp;
      }
     }
}
void shift(long x)
{
     long i=x,j=x*2;
     DATA tmp;
     while(j<=n)
     {
      if(j<n) if(cmp(list[j].num,list[j+1].num)==-1) j++;
      if(cmp(list[i].num,list[j].num)==-1) 
      {
       tmp=list[i];
       list[i]=list[j];
       list[j]=tmp;
      }
      else break;
      i=j; j*=2;
     }
}
void sort()
{
     long i;
     long kk=n;
     DATA tmp;
     for(i=n/2;i>=1;i--) shift(i);
     for(i=n;i>=1;i--)
     {
       tmp=list[1]; list[1]=list[n]; list[n]=tmp;
       n--;
       shift(1);
     }
     n=kk;
}
void work()
{
     long i,j;
     long ans=0;
     long tmp=1;
     list[0].num[1]=-1;
     list[n+1].num[1]=-1;
     for(i=1;i<=n+1;i++)
     {
       if(cmp(list[i].num,list[i-1].num)==0) tmp++;
       else
       {
         if(tmp>1)
         {
          printf("%ld%ld%ld-%ld%ld%ld%ld %ld\n",
          list[i-1].num[1],list[i-1].num[2],list[i-1].num[3],list[i-1].num[4],
          list[i-1].num[5],list[i-1].num[6],list[i-1].num[7],tmp);
          ans++;
         }
         tmp=1;
       }
     }
     if(ans==0)
      printf("No duplicates.\n");
}
int main()
{
    read();
    sort();
    work();
    return 0;
}
