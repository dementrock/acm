#include<iostream>
using namespace std;
int main()
{
    float n,sum;
    int count;
    while(1)
    {
        cin>>n;
        if(n==0.00) break;
        count=2;
        sum=0;
        while(sum<n)
        {
            sum+=(float)1/count;
            count++;
        }
        cout<<count-2<<" card(s)"<<endl;
    }
    return 0;
}