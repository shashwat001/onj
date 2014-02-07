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
 
void computeLPSArray(string &pat, int M, int *lps);
 
int KMPSearch(string &pat, char *txt)
{
    int M = pat.size();
    int N = strlen(txt);
 
    // create lps[] that will hold the longest prefix suffix values for pattern
    int *lps = (int *)malloc(sizeof(int)*M);
    int j  = 0;  // index for pat[]
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 	int count = 0;
    int i = 0;  // index for txt[]
    while(i < N)
    {
      if(pat[j] == txt[i])
      {
        j++;
        i++;
      }
 
      if (j == M)
      {
        count++;
        j = lps[j-1];
      }
 
      // mismatch after j matches
      else if(pat[j] != txt[i])
      {
        // Do not match lps[0..lps[j-1]] characters,
        // they will match anyway
        if(j != 0)
         j = lps[j-1];
        else
         i = i+1;
      }
    }
    free(lps); // to avoid memory leak
    return count;
}
 
void computeLPSArray(string &pat, int M, int *lps)
{
    int len = 0;  // lenght of the previous longest prefix suffix
    int i;
 
    lps[0] = 0; // lps[0] is always 0
    i = 1;
 
    // the loop calculates lps[i] for i = 1 to M-1
    while(i < M)
    {
       if(pat[i] == pat[len])
       {
         len++;
         lps[i] = len;
         i++;
       }
       else // (pat[i] != pat[len])
       {
         if( len != 0 )
         {
           // This is tricky. Consider the example AAACAAAA and i = 7.
           len = lps[len-1];
 
           // Also, note that we do not increment i here
         }
         else // if (len == 0)
         {
           lps[i] = 0;
           i++;
         }
       }
    }
}
 

int n,i;
char str[100004];
int main ()
{

	string s[12];
	s[0]="2";
	int w = 12;
	for(int i = 1;i < 12;i++)
	{
		s[i] = mult(s[i-1],s[i-1]);		
	}
	
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int count=0;
		 scanf("%s",str);
		 for(int i = 0;i < 12;i++)
		 {
		 	count+=KMPSearch(s[i], str);
		 }
		 printf("%d\n",count);	 
	}
	return 0;
}
