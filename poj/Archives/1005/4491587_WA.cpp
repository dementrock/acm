#include<stdio.h>
#include<iostream>
using namespace std;
const float pi=3.14159;
int main()
{
    int n,i,z;
    float x,y,max;
    cin>>n;
    for(i=0;i<n;i++)
    {
       scanf("%f%f",&x,&y);
       max=x;
       if(y>max) max=y;
       z=(int)(pi*max*max/100)+1;
       printf("Property %d: This property will begin eroding in year %d.\n",i+1,z);
    }
    printf("END OF OUTPUT.\n");
    return 0;
}