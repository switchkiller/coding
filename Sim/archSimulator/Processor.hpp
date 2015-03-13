#define EOR 0
#define ROR 1
#define LOR 2
#define SAF 3
#define EAR 7
#define RAR 8
#define LAR 9
#define ERG 10
#define SRG 11
#define LRG 15
#define MRG 16
#define SFL 17
#define MFL 20
#define EFL 21
#define MFE 22
#define RMS 24
#define LMS 23
#define LIR 25
#define LSP 29
#define DSP 28
#define ISP 27
#define ESP 26
#define LPC 32
#define IPC 31
#define EPC 30
#define LMR 33
#define LWR 34
#define ERD 35
#define LIO 36

#define TRUE	 1
#define FALSE	 0

#define FREE 'F'
#define BUSY 'B'


#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#include<iterator>
#include<map>
#include<vector>
#include<list>
#include<set>
#include<queue>
#include<cassert>
#include<deque>
#include<stack>
#include<bitset>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iomanip>
#include<string>
#include<cmath>
#include<cerrno>
#include<ctime>
#include<fstream>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
priority_queue<ii,vector<ii>, greater<ii> > QG; //ascending order
priority_queue<ii> QL;//normal descending order
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define present(c,x) ((c).find(x) != (c).end())
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define debug 0
#define REP(i,n) for(i=0;i<n;i++)





// WIDTH denotes the maximum length of an instruction

#define WIDTH 8

int  START = 0;

bool 	FOUT; 		//File output
bool 	COUT=true; 	//Console output
FILE 	*fout;
char 	FLAG = '0';
int 	PageID = -1999;

set<int> pages;

bool EXECUTE( int );

bool Print(string & , int , int , string ,bool &);

bool SetBreakPoints();

void SelectOperations(string &, bool &);

void ChangeRegisterValue();

void ChangeBreakPointState(bool &);

void PrintFlagValues();

void ChangeExecutionModeValue(string &);


// This function gives the integer value of a given input char *
int Value(const char str1[])
{
	int result =0 , l = strlen(str1) , k = WIDTH - l;
	bool neg = false ;
	string str="";
	if (k>0)
	{
		while (k--)  // Add extra 0s to make the result upto the WIDTH of data bus.
			str = str + "0";
	}
	str = str + str1 ;
	if (str[0]=='1')
		neg = true ;
	for (int i=0;i<WIDTH;i++)
	{
		result+=((int)pow(2.0,i*1.0)*(str[WIDTH-i-1]-'0'));
	}
	return  ( (neg==true)?result-256:result );
}

// This function converts Binary number to signed number only
int SignedValue(const char *bin)
{
	int ret = 0;
	for (int i=0;i< WIDTH ;i++)
		ret|= (bin[WIDTH -i - 1] == '1')?(1<<i):0;
	return ret;
}

//This function gives the binary string representing the given input number
string ToStr(int result)
{
	string Result="";
	for (int i=WIDTH-1;i>=0;i--)
	{
		Result = Result + ((1<<i&result)?'1':'0');
	}
	return Result;
}

//This function gives the hexadecimal string representing the given input in char *

std::string val(std::string t)
{
	std::string tmp = "0000" + t;
	int l = Value(tmp.c_str());
	switch (l)
	{
		case 0:
			return "0";
		case 1:
			return "1";
		case 2:
			return "2";
		case 3:
			return "3";
		case 4:
			return "4";
		case 5:
			return "5";
		case 6:
			return "6";
		case 7:
			return "7";
		case 8:
			return "8";
		case 9:
			return "9";
		case 10:
			return "A";
		case 11:
			return "B";
		case 12:
			return "C";
		case 13:
			return "D";
		case 14:
			return "E";
		case 15:
			return "F";
	}
	return "  ";
}

std::string toHex(const char str[]) // Returns Hex representation of the given binary number ... in char *
{
	if (strlen(str)<4)
		return "";
	std::string tmp = str;
	std::string tmp1 = tmp.substr(0,4) , tmp2 = tmp.substr(4,4);
	std::string ret = "";
	ret = ret + val(tmp1) + val(tmp2);
	return ret;
}

std::string toHexS(std::string input)
{
	if (input.length()==0)
		return "  ";
	char var[100];
	strcpy(var,input.c_str());
	return toHex(var);
}


bool CheckHex(string s)
{
	int l = s.length();
	for (int i=0;i<l;i++)
	{
		if (isxdigit(s[i])==0)
			return false;
	}
	return true;
}

// Lookup table

map<string , int > lookup;

map<string , string > flag_lookup;

map<string , int > label_lookup;  //Label is on which line (starting from 0)

set<string> labels;

set<int> breaks;

map<string , int > inst_len;
/*
bool label_create(string fname)
{
	ifstream fin(fname.c_str());
	string str1="" , str2="" , str3="";
	int line = 0  , l = 0;
	while (TRUE)
	{
		fin >> str1; // Always a new instruction
		if (fin.eof()) // Code end
		{
			break;
		}
		if (str1=="brk")
		{
			breaks.insert(line);
			continue;
		}
		l = str1.length();
		if (str1[l-1]==':')
		{
			//Label Handle
			if (labels.find(str1)!=labels.end())
			{
				cout << "Error : Redefinition of label  : " <<str1<<"\n";
				return false ;
			}
			if (CheckHex(str1) == true )
			{
				cout << "The labels cannot be valid Hexadecimal numbers. Please change the label " << str1<<"\n\n";
				return false ;
			}
			labels.insert(str1);
			label_lookup[str1]=line;
			continue ;
		}
		if (str1[0]=='r') // Return Statement
		{
			line++;
			continue;
		}
		if (inst_len[str1] == 4)
		{
			fin >> str2;// Register Value is scanned
			line++;
		}
		if (inst_len[str1] == 8 )
		{
			line++;
		}
                if (str1[0]=='j' || (str1[0]=='c' && (str1[1]=='d' || str1[1]=='r'))) // Jump or Call instruction
                {
                    line++;
                    if (str1[l-2]=='d' || str1[l-3]=='d')
                    {
                        line++;
                        fin >> str2;
                    }
                }
		if (str1[l-1] == 'i') // Immediate Instruction
		{
			int j;fin >>j;//Integer Scan
			line++;
		}
	}
	fin.close();
	return true ;
}
*/

string HexToBin(string s)
{
	int l = s.length();
	string ret="";
	for (int i=0;i<l;i++)
	{
		if (s[i]=='0')
			ret=ret+"0000";
		if (s[i]=='1')
			ret=ret+"0001";
		if (s[i]=='2')
			ret=ret+"0010";
		if (s[i]=='3')
			ret=ret+"0011";
		if (s[i]=='4')
			ret=ret+"0100";
		if (s[i]=='5')
			ret=ret+"0101";
		if (s[i]=='6')
			ret=ret+"0110";
		if (s[i]=='7')
			ret=ret+"0111";
		if (s[i]=='8')
			ret=ret+"1000";
		if (s[i]=='9')
			ret=ret+"1001";
		if (s[i]=='A' || s[i] == 'a')
			ret=ret+"1010";
		if (s[i]=='B' || s[i] == 'b')
			ret=ret+"1011";
		if (s[i]=='C' || s[i] == 'c')
			ret=ret+"1100";
		if (s[i]=='D' || s[i] == 'd')
			ret=ret+"1101";
		if (s[i]=='E' || s[i] == 'e')
			ret=ret+"1110";
		if (s[i]=='F' || s[i] == 'f')
			ret=ret+"1111";
	}
	return ret;
}
