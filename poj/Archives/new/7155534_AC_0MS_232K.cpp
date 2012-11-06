#include<iostream>
using namespace std;
int main()
{
    int max=0,day=0,i,a,b,n;
    while(scanf("%d",&n)){
		if(!n) break;
		max=day=0;
	    for(i=1;i<=n;i++)
	    {
	       cin>>a>>b;
	       if(a+b>8) if(a+b>max)
	       {
	          max=a+b;
	          day=i;
	       } 
	    }
	    cout<<day<<endl;
	}
	return 0;
}
