#include<stdio.h>
int main()
{
    float sum, n;
    int i;
    sum=0;
    for(i=0;i<12;i++)
    {
       scanf("%f",&n);
       sum+=n;
    }
    printf("$%.2f",(float)sum/12);
    return 0;
}
    
