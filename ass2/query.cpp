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
#include<fstream>
#include<stdio.h>
//#include "iterateStatement.h"

using namespace std;

/* Container's */

#define	VI		vector<LL>
#define PLL             pair<LL,LL>  /* A Single Pair  */
#define VP		vector<PLL> /* Vector of Pairs */
#define VS		vector<string>
#define VVI		vector<VI>
#define VVS		vector<VS>
#define LL		long long int
#define SI(n)		scanf("%lld",&n);
#define SC(c)		scanf("%c",&c);
#define SS(s)		scanf("%s",s);
#define FOR(x,a,b)	for(LL x=a;x<b;x++)
#define REP(i,n)	for(LL i=0;i<n;i++)
#define MP		make_pair
#define PB		push_back

/**************************************************/
map <string , string> table_loc;
map <string , vector <string> > table_fields;
vector < string > table;
int page_size,cache_size,return_num;
map<pair<int,int>, int > page_to_pageno;
map<int, fpos_t> pageno_to_file;
vector< pair<int,int> > p;
map<string,vector< pair<int,int> > > table_to_page;
map<pair<int,int>, int > page_to_size;
/**************************************************/
string raw_input(istream& stream)
{
	string res;
	getline(stream,res);
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

void createCommand(string query){
	string firstcheck=query.substr(0,12);
	if(firstcheck!="create table")
	{
		cout<<"Invalid Query";
		return;
	}
	int i,j;
	map <string,string>  table_data;
	int len=query.length();
	int start,end,count;
	string table_name;
	for(i=0;i<query.length();i++)
	{
		if(query[i]=='(')
		{
			start=i;
			count=1;
			i++;
			while(count!=0&&i!=len)
			{
				if(query[i]=='(')
				{
					count++;
				}
				if(query[i]==')')
				{
					count--;
				}
				i++;
			}
			end=i;
			break;
		}
	}
	if(count!=0)
	{
		cout<<"Paranthesess Don't Match"<<endl;
		return;
	}
	string tabledata=query.substr(0,start);
	string datatypes=query.substr(start+1,end-start-2);
	string space=" ";
	string cur_tablename;
	for(i=start-1;query[i]!=' ';i--);

	
	cur_tablename=tabledata.substr(i+1,tabledata.length());
	
	if(find(table.begin(), table.end(), cur_tablename)!=table.end())
	{
		cout<<"Table Already Exists"<<endl;
		return;
	}

	cout<<"Querytype:create"<<endl;
	cout<<"Tablename:"<<cur_tablename<<endl;

	ofstream outfile;
	outfile.open("config.txt", std::ios_base::app);
	outfile<<"BEGIN"<<endl;
	outfile<< cur_tablename<<endl;



	/*Start Parsing The Parantheses*/
	string found_data;
	int x,to_split;
	string comma=",";
	cout<<"Attributes:";
	while(datatypes.find(comma)<datatypes.length())
	{
		x=datatypes.find(comma);
		found_data=datatypes.substr(0,x);
		to_split=found_data.find(space);
		if(to_split>found_data.length())
		{
			cout<<"Incorrect Spacing"<<endl;
			return;
		};
		table_data[found_data.substr(0,to_split)]=found_data.substr(to_split+1,found_data.length());
		cout<<found_data.substr(0,to_split)<<space<<found_data.substr(to_split+1,found_data.length())<<comma;
		outfile<<found_data.substr(0,to_split)<<space<<found_data.substr(to_split+1,found_data.length())<<endl;
		datatypes=datatypes.substr(x+1,datatypes.length());
	}
	found_data=datatypes;
	to_split=found_data.find(space);
	table_data[found_data.substr(0,to_split)]=found_data.substr(to_split+1,found_data.length());
	cout<<found_data.substr(0,to_split)<<space<<found_data.substr(to_split+1,found_data.length())<<endl;
	outfile<<found_data.substr(0,to_split)<<space<<found_data.substr(to_split+1,found_data.length())<<endl;
	
	outfile<<"END"<<endl;
	outfile.close();
	ofstream myfile;
	myfile.open ((cur_tablename+".txt").c_str());
	myfile.close();
	myfile.open ((cur_tablename+".csv").c_str());
	myfile.close();

	/*Start Parsing the Paranthases*/
}

vector<string> split(string x, string delim)
{
	vector<string> result;
	int prev = 0, found = x.find(delim); // string find returns int
	while(found!=std::string::npos) // special cnstnt returned when not found
	{
		result.push_back(x.substr(prev,found-prev)); // substr : give start    point and length to include
		prev = found+1;
		found = x.find(delim, found+1); // find from index >= found+1
	}           
	result.push_back(x.substr(prev,x.size()-prev));
	return result;
}
/*void printtags(string head, VS tags)
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
		if(flg==1)
		{
			cout << tags[i] << endl;
		}
		if(tags[i].substr(0,9)=="distinct(")
		{
			tags[i]=tags[i].substr(10);
			tags[i]=tags[i].substr(0,tags[i].size()-1);
			fdistinct.push_back(tags[i]);

		}
		cout << tags[i] <<  " ";
	}
	cout << endl;
}
void selectCommand(string query)
{
	VS split_query=split(query," ");
	int flag;
	flag=func();	
	if(!flag)
	{
		int invalid_flag=0;
		for(int i=0;i<ftables.size();i++)
		{
			if(find(table.begin(), table.end(), ftables[i])!=table.end())
				continue;
			else
			{
				invalid_flag=1;
				break;
			}
		}
		if(invalid_flag)
			cout<<"Query Invalid\n";
		else
		{
			printtags("Tablename:",ftables);
			printtags("Columns:",fcolumns);
			cout << fdistinct.size() << endl;
			printtags("Distinct:",fdistinct);
			printtags("Condition:",fconditions);
			printtags("Orderby:",forderby);
			printtags("Groupby:",fgroupby);
			printtags("Having:",fhaving);
		}
	}
}
   void queryType(string query)
   {
   string dup;
   dup = query;
   VS split_query = split(query," ");
   if(split_query[0]=="create")
   {
   cout<<"Querytype:create\n";
   createCommand(dup);
   }
   else if(split_query[0]=="select")
   {
   cout<<"Querytype:select\n";
   selectCommand(dup);
   }
   }*/
/***********************/
void readConfig(string configFilePath)
{
	ifstream confile;
	string table_name;
	confile.open(configFilePath.c_str());
	char output[100][100];
	char temp[100],loc[100];
	int i=0,j=0;
	if (confile.is_open()) 
	{
		while (!confile.eof()) 
		{
			confile >> output[i++];
			if(strcmp(output[i-1],"BEGIN")==0)
			{
				confile>>table_name;
				table.push_back(table_name);
				cout<<"table pushed : "<<table_name<<endl;
				table_loc[table_name]=output[5]+table_name+".csv";
				confile>>temp;
				while(strcmp(temp,"END")!=0)
				{
					table_fields[table_name].push_back(temp);
					confile>>temp;
				}
			}
		}
	}
	page_size=atoi(output[1]);
	cache_size=atoi(output[3]);
	//			cout<<page_size<<" "<<cache_size<<endl;
	//			for(i=0;i<table.size();i++)
	//			{	cout<<table_loc[table[i]]<<endl;
	//				for(int j=0;j<table_fields[table[i]].size();j++)
	//					cout<<table_fields[table[i]][j]<<endl;
	//			}
	confile.close();
}

/***********************/
int main()
{
	char inp[10000];
	string query="";
	string a = "config.txt";
	readConfig(a);
	string b;
	getline(cin,b);
//	b="create table courses(subjectid int,subjectname varchar(50),credits int,profname varchar(50))";
	createCommand(b);
	//	DBSystem object;
	//	object.readConfig(a);
	//	string query;
	//	if(query[0]=='s')
//	selectCommand(query);
	//	else if(query[0]=='c')
	//		cout<<"create command\n";
	//	cin>>query;
	//	queryType(query);
}
