#include   <iostream>   
#include   <stdlib.h>   
using namespace std;
int   Int(char   s);   
int   Square(int   k);   
int   cmp(const   void   *t1,const   void   *t2)   
{   
int   *a,*b;         
      a=(int   *)t1;   b=(int   *)t2;         
if   (*a>*b)   return   1;         
if   (*a<*b)   return   -1;         
      return   0;         
}  
int   main()   
{   
int   n,i,j,k,p,a[100000],temp;   
char   s;   

cin>>n;   
if   (n==1)   cout<<"No   duplicates."<<endl;   
else   
{   
for   (i=0;i<n;i++)   
{   
k=0;   
temp=0;   
while   (k<7)   
{   
cin>>s;   
if   ((s>='A')   &&   (s<='Z'))   
{   
temp=temp*10+Int(s);   
k++;   
}   
else   if   ((s>='0')   &&   (s<='9'))   
{   
temp=temp*10+s-'0';   
k++;   
}   
}   
a[i]=temp;   
}   
}   

qsort(a,n,sizeof(int),cmp);   

p=0;     j=0;   
while   (p<n)   
{   
i=p+1;   
while   (a[i]==a[p])   i++;   
if   (i-1>p)   
{   
k=7;   
while   (k-->0)   
{   
cout<<a[p]/Square(k);   
a[p]=a[p]%Square(k);   
if   (k==4)   cout<<'-';   
}   
cout<<' '<<(i-p)<<endl;   
p=i;     j=1;   
}   
else   p++;   
}   
if   (j==0)   cout<<"No   duplicates."<<endl;   
return 0;
}   

int   Int(char   s)   
{   
int   t;   
t=s-'A'+6;   
if   (s>'Q')   t--;   
return   (t/3);   
}   

int   Square(int   k)   
{   
int   i,temp=1;   
for   (i=0;i<k;i++)   temp*=10;   
return(temp);   
}
