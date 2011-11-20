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
     int i;
     for(i=1;i<7;i++)
     {
        if(a[i]<b[i]) return -1;
        else if(a[i]>b[i]) return 1;
     }
     return 0;
}
void swap(DATA* a,DATA* b)
{
     DATA x=*a;*a=*b;*b=x;
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
void quicksort (DATA r[], int s, int t)
{
     int i=s, j=t;
     if (s<t)
     do
     {
          r[0] =r[s];  /*r[0]暂存选出的数据*/
          while( j>1 && (cmp(r[j].num,r[0].num)==1||cmp(r[j].num,r[0].num)==0))
               j--;
          if (i<j)
          {
                   r[i]=r[j]; 
                   i++; 
           }
       while (i<j && (cmp(r[i].num,r[0].num)==-1||cmp(r[i].num,r[0].num)==0))
               i++;
        if (i<j)
        {
              r[j]=r[i];
               j--;
          }
     }while (i<j);
     r[i]=r[0];
     quicksort(r,s,j-1);  /*递归处理前一部分*/
     quicksort(r,j+1,t);  /*递归处理后一部分*/
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
    quicksort(list,1,n);
    work();
    return 0;
}