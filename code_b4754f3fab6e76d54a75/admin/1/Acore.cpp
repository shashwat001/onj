//shashwat001

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

#define INF 2147483647
#define LINF 9223372036854775807
#define mp make_pair
#define pb push_back

#define Overflow 2
#define ROW b_len
#define COL a_len+b_len+Overflow

typedef long long int lli;
typedef pair<int,int> pi;

#define  maxW 12 //maximum number of words
#define maxP 5001 //maximum length of a pattern
#define maxS 50001 //maximum size of the songs
#define maxid 10
#define maxNodes maxP*maxW


int AC[maxNodes][maxid];
int tail[maxW], pos = 1;
int fail[maxNodes];
int cnt[maxNodes];

int inDeg[maxNodes];

int w, n;


int getCarry(int num) {
    int carry = 0;
    if(num>=10) {
        while(num!=0) {
            carry = num %10;
            num = num/10;
        }
    }
    else carry = 0;
    return carry;
}
 
int num(char a) {
    return int(a)-48;
}
 
string mult(string a, string b) {
        string ret;
        int a_len = a.length();
        int b_len = b.length();
        int mat[ROW][COL];
        for(int i =0; i<ROW; ++i) {
            for(int j=0; j<COL; ++j) {
                mat[i][j] = 0;
 
            }
        }
 
        int carry=0, n,x=a_len-1,y=b_len-1;
        for(int i=0; i<ROW; ++i) {
            x=a_len-1;
            carry = 0;
            for(int j=(COL-1)-i; j>=0; --j) {
                if((x>=0)&&(y>=0))  {
                    n = (num(a[x])*num(b[y]))+carry;
                    mat[i][j] = n%10;
                    carry = getCarry(n);
                }
                else if((x>=-1)&&(y>=-1)) mat[i][j] = carry;
                x=x-1;
            }
            y=y-1;
        }
 
        carry = 0;
        int sum_arr[COL];
        for(int i =0; i<COL; ++i) sum_arr[i] = 0;
        for(int i=0; i<ROW; ++i) {
            for(int j=COL-1; j>=0; --j) {
                sum_arr[j] += (mat[i][j]);
            }
        }
        int temp;
        for(int i=COL-1; i>=0; --i) {
            sum_arr[i] += carry;
            temp = sum_arr[i];
            sum_arr[i] = sum_arr[i]%10;
            carry = getCarry(temp);
        }
 
        for(int i=0; i<COL; ++i) {
            ret.push_back(char(sum_arr[i]+48));
        }
 
        while(ret[0]=='0'){
            ret = ret.substr(1,ret.length()-1);
        }
        return ret;
}
 


int insert(string s) 
{
    
    int acp = 0, cid;		//acp is the current node which we are at in the AC tree
    
    int slen = s.size();	//slen the string length of the string to be inserted
    
    for(int i=0; i<slen; i++) 
    {
        cid = s[i]-'0';
        
        if(AC[acp][cid] == -1) 		//create a new node, if a child is not already present
        {
            AC[acp][cid] = pos++;	//we are assigning a unique positive number to each node
            
            for(int j=0; j<maxid; j++) //marking the children to the current node as null, -1 is null
            {
                AC[pos][j] = -1;
            }
        }
        
        acp = AC[acp][s[i]-'0'];	//we are pointiong to the current node
    }
    return acp;
}

void init() 
{
    
    fail[0] = 0;		//fail to root is root
    inDeg[0] = 1;		//fail to root is pointing towards root hence indeg is 1
    for(int i=0; i<maxid; i++) 
    {
        if (AC[0][i] != -1) 
        {
            fail[AC[0][i]] = 0;		//make all valid children of root fail to root.
            ++inDeg[0];				//increasing indegree of root by 1
        } 
        else 
        {
            AC[0][i] = 0;
        }
    }
}

//makeAC will basically add the required transitions to the AC trie.
void makeTransitions() 
{
    queue<int> Q;	//initializing the automata
    init();
    
    for(int i=0; i<maxid; i++) 	//all the head nodes in the trie will be added to the queue
    {
        if (AC[0][i] > 0)
            Q.push(AC[0][i]);
    }
    while (!Q.empty()) 
    {
        int cur = Q.front(); Q.pop();
        for(int i=0; i<maxid; i++) 
        {
            if (AC[cur][i] > 0) 	//if the current node exists
            {
                
                fail[AC[cur][i]] = AC[fail[cur]][i]; //if string fails at the current position, it should next point towards where the parents' failure
                										//function was pointing number of fail pointers to AC[fail[cur]][i] are incresed by 1
                ++inDeg[AC[fail[cur]][i]];
                
                Q.push(AC[cur][i]);					//to process the next child
            }
            else 
            {
                AC[cur][i] = AC[fail[cur]][i];		 //make the child point towards the fail of parent
            }
        }
    }
}


int main ()
{
	string s[12];
	s[0]="2";
	int w = 12;
	for(int i = 1;i < 12;i++)
	{
		
		s[i] = mult(s[i-1],s[i-1]);
		//cout<<s[i].size()<<endl;
		
	}
	
	memset(AC, -1, sizeof AC);
    for(int i=0; i<maxid; i++) 
    {
    	AC[0][i] = -1;	//make all roots children as null
    }
    for(int i=0; i<w; i++) 
    {
        //tail[i] is unique for a pattern, it gives the id of the ast character in the inserted pattern in the AC-Trie
        tail[i] = insert(s[i]);
    }
    makeTransitions();
    int t;
    cin>>t;
    assert(t>=1 && t<=100000);
    while(t--)
    {
		string text;
		cin>>text;
		int tlen = text.size();
		assert(t<=100000);
		int cur = 0;
		//refer to insert function to understand what goes on over here
		//we are iterating through the trie
		fill(cnt,cnt+maxNodes,0);
		for(int j=0; j<tlen; j++) 
		{
		    cur = AC[cur][text[j]-'0'];
		    //increasing the frequency of the current node
		    ++cnt[cur];
		}
		
		int tempinDeg[maxNodes];
		queue<int> Q;
		//we are now pushing all the nodes with no failure pointers to them
		//to the queue, we are doing a back track - in a way.
		for(int i=0; i< pos + 1; i++)
		{
		    if(inDeg[i] == 0)
		        Q.push(i);
		    tempinDeg[i] = inDeg[i];
		}
		
		while (!Q.empty()) 
		{
		    int tmp = Q.front(); Q.pop();
		    //if we reach to root we break.
		    if (tmp == 0) break;
		    //we are virtually removing the current node,
		    //so we remove its pointer to the failure function by
		    //reducing indegree to its failure node.
		    --tempinDeg[fail[tmp]];
		    //adding the frequency of the current node to its
		    //failure node
		    cnt[fail[tmp]] += cnt[tmp];
		    //if indeg is 0 pushing the failure node to the queue
		    if (tempinDeg[fail[tmp]] == 0) 
		    {
		        Q.push(fail[tmp]);
		    }
		}
		int sum = 0;
		for(int i=0; i<w; i++) 
		{
		    //now we get to use the unique tail-id we assigned
		    //to each of the patterns, we just print out the
		    //frequency of the pattern
		    sum+=cnt[tail[i]];
		    //printf("%d ", cnt[tail[i]]);
		}
		cout<<sum<<endl;
	}
	return 0;
}
