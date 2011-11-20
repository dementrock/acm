#include <stdio.h>
#include <string.h>
using namespace std;
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
int partition(DATA A[],int left, int right)
{
    int i=(int)(left+right)/2,j;
    swap(&A[i],&A[right]);
    i=left-1;
    for(j=left;j<right;j++)
    {
        if(cmp(A[j].num,A[right].num)==-1)
        {
            i++;
            swap(&A[i],&A[j]);
        }
    }
    i++;
    swap(&A[i],&A[right]);
    return i;
}
void quicksort(DATA A[], int left, int right)
{
     int i;
     if(left<right)
     {
        i=partition(A,left,right);
        quicksort(A,left,i-1);
        quicksort(A,i+1,right);
     }
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