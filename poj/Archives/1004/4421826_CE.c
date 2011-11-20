#include<stdio.h>
using namespace std;
int main()
{
    float sum, n;
    int i;
    for(i=0;i<12;i++)
    {
       scanf("%f",&n);
       sum+=n;
    }
    printf("$%.2f",(float)sum/12);
    return 0;
}