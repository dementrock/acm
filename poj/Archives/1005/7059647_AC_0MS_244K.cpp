#include<iostream>
using namespace std;
int main()
{
	int n;
	float a,b,pi=3.1415926;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a>>b;
		cout<<"Property "<<i<<": This property will begin eroding in year ";
		cout<<(int)(pi*(a*a+b*b)*0.01)+1<<"."<<endl;
	}
	cout<<"END OF OUTPUT."<<endl;
	return 0;
}
