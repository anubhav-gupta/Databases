/*	Karan Dhamele	    */
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>

using namespace std;



#define INF		1000000007
#define LL		long long int
#define SI(n)		scanf("%lld",&n);
#define SC(c)		scanf("%c",&c);
#define SS(s)		scanf("%s",s);
#define FOR(x,a,b)	for(LL x=a;x<b;x++)
#define REP(i,n)	for(LL i=0;i<n;i++)
#define MP		make_pair
#define PB		push_back


/* Container's */

#define	VI		vector<LL>
#define PLL             pair<LL,LL>  /* A Single Pair  */
#define VP		vector<PLL> /* Vector of Pairs */
#define VS		vector<string>
#define VVI		vector<VI>
#define VVS		vector<VS>

template<class T>inline T GCD(T a,T b){return b?GCD(b,a%b):a;}
template<class T> inline T LCM(T a,T b){if(a<0)return LCM(-a,b);if(b<0)return LCM(a,-b);return a*(b/GCD(a,b));}
template<class T>inline T POW1(T a,T b,T m){long long x=1,y=a;while(b > 0){if(b%2 == 1){x=(x*y);if(x>m) x%=m;}y = (y*y);if(y>m) y%=m;b /= 2;}return x;}
template<class T>inline T INV(T n,T m){return POW1(n,m-2,m);}
template<class T>inline T SUB(T a,T b,T m){return (a%m-b%m+m)%m;}
template<class T>inline T ADD(T a,T b,T m){return (a%m+b%m)%m;}
template<class T>inline T MUL(T a,T b,T m){return (a%m*b%m)%m;}
template<class T>inline T DIV(T a,T b,T m){return (a%m*(INV(b,m))%m)%m;}
#include "iterateStatement.h"
string raw_input(istream& stream)
{
	string res;
	getline(stream,res);
	return res;
}
vector<string> split(string x, string d)
{
	vector<string> res;
	int prev = 0, found = x.find(d); // string find returns int
	while(found!=std::string::npos) // special cnstnt returned when not found
	{
		res.push_back(x.substr(prev,found-prev)); // substr : give start    point and length to include
		prev = found+1;
		found = x.find(d, found+1); // find from index >= found+1
	}           
	res.push_back(x.substr(prev,x.size()-prev));
	return res;
}
string inbetween(VS split_query,string a, string b)
{
	string res="";
	LL flg=0;
	REP(i,split_query.size())
	{
		if(split_query[i]==b)
		{
			break;
		}
		else if(flg==1)
			res+=split_query[i];
		if(split_query[i]==a)
			flg=1;
	}
	return res;
}
void createCommand(string query){}
void printtags(string head, VS tags)
{
	cout << head << "";
	LL flg=0;
	if(head=="Columns:")
		flg=1;
	if(tags.size()==0)
	{
		cout << "NA\n";
		return;
	}
	REP(i,tags.size())
	{
	/*	if(flg==1)
		{
			cout << tags[i] << endl;
		}
		if(tags[i].substr(0,9)=="distinct(")
		{
			tags[i]=tags[i].substr(10);
			tags[i]=tags[i].substr(0,tags[i].size()-1);
			fdistinct.push_back(tags[i]);
		
		}*/
		cout << tags[i] <<  " ";
	}
	cout << endl;
}
void selectCommand(string query)
{
	VS split_query=split(query," ");
	func();	
	printtags("Tablename:",ftables);
	printtags("Columns:",fcolumns);
	cout << fdistinct.size() << endl;
	printtags("Distinct:",fdistinct);
	printtags("Condition:",fconditions);
	printtags("Orderby:",forderby);
	printtags("Groupby:",fgroupby);
	printtags("Having:",fhaving);
}
void queryType(string query)
{
	VS split_query = split(query," ");
	if(split_query[0]=="create")
	{
		createCommand(query);
	}
	else if(split_query[0]=="select")
	{
		selectCommand(query);
	}
}
int main()
{
	string query="";
	selectCommand(query);
	
}
