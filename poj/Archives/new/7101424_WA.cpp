#include<iostream>
#include<string>
using namespace std;
string haab[]={"pop", "no", "zip", "zotz", "tzec", 
"xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", 
"mac", "kankin", "muan", "pax", "koyab", "cumhu"};
string tzolkin[]={"imix", "ik", "akbal", "kan", 
"chicchan", "cimi", "manik", "lamat", "muluk", 
"ok", "chuen", "eb", "ben", "ix", "mem", "cib", 
"caban", "eznab", "canac", "ahau"};
int n;
void work()
{
	int t=0,days=0,year2=0,year1=0;
	string sday,smon;
	cin>>sday>>smon>>year1;
//	cout<<sday<<" "<<smon<<" "<<year1<<endl;
//	cout<<"y";
	for(int i=0;i<19;++i)
		if(smon==haab[i])
		{
			days+=i*20;
			break;
		}
//	cout<<days<<endl;
	for(int i=0;i<sday.length()-1;++i)
		t=t*10+sday[i]-'0';
//	cout<<t<<endl;
	days+=t+year1*365;
	year2=(days-1)/260;
	days=days-year2*260;
//	cout<<days<<endl;
	++days;
	int t1=-1,t2=-1;
	for(int i=1;i<=days;++i)
		t1=(t1+1)%13,t2=(t2+1)%20;
	cout<<t1+1<<" "<<tzolkin[t2]<<" "<<year2<<endl;
}
int main()
{
	cin>>n;
	cout<<n<<endl;
	for(int i=1;i<=n;++i)
	{
		work();
	}
	return 0;
}
