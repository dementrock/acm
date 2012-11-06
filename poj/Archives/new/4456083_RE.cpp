#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int A[100000],B[100000],C[100000];
int number[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,0,7,7,8,8,8,9,9,9,0};
int cmp ( const void *a , const void *b ) 
{ 
return *(int *)a - *(int *)b; 
} 
int main()
{
    char s[100];
    int i,j,count,n,tmp[7],p,t;
    bool flag;
    scanf("&d",&n);
    for(i=0;i<n;i++)
    {
       A[i]=0;
       cin>>s;
       t=1000000;
       count=0;
       for(j=0;j<100;j++)
       {
           if(s[j]!='-')
           {
              if(s[j]>='0'&&s[j]<='9')
              {
                  A[i]+=(s[j]-'0')*t;
                  t/=10;
              }
              else if(s[j]>='A'&&s[j]<='Z')
              {
                  A[i]+=number[s[j]-'A']*t;
                  t/=10;
              }
              count++;
           }
           if(count==7) break;
       }
    }
    qsort(A,n,sizeof(A[0]),cmp);
    B[0]=1;
    C[0]=1;
    count=0;
    flag=false;
    for(i=1;i<=n;i++)
    {
        if(A[i]==A[i-1]) B[count]++;
        else
        {
            if(B[count]>1)
            {
               int a=(int)A[i-1]/10000;
               int b=A[i-1]%10000;
               if(a<100) printf("0");
               if(a<10) printf("0");
               printf("%d-",a);
               if(b<1000) printf("0");
               if(b<100) printf("0");
               if(b<10) printf("0");
               printf("%d %d\n",b,B[count]);
               flag=true;
            }
            count++;
            B[count]=1;
        }
    }
    if(!flag) printf("No duplicates.\n");
    return 0;
}
