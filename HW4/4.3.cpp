#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;


int getmin(int a, int b)
{
    if (a>b) return b;
    else
    {
        return a;
    }
    
}



vector<int> DQ(const string &x,const string &y);

int cost[4][4] = {
  0 , 1 , 5 , 1
, 1 , 0 , 9 , 1
, 5 , 9 , 0 , 1
, 1 , 1 , 1 , 0};

int mismatch(char a, char b)
{
    int tmp1 = 0;
    int tmp2 = 0;
	if(a == 'A') tmp1 = 0;
	else if(a == 'T') tmp1 = 1;
	else if(a == 'G') tmp1 = 2;
	else if(a == 'C') tmp1 = 3;

	if(b == 'A') tmp2 = 0;
	else if(b == 'T') tmp2 = 1;
	else if(b == 'G') tmp2 = 2;
	else if(b == 'C') tmp2 = 3;
	//cout << cost[tmp1][tmp2];
    return cost[tmp1][tmp2];
}

int gap(char a)
{
    switch (a)
    {
        case 'A': return 1;
        case 'T': return 2;
        case 'C': return 3;
        case 'G': return 1;
        case '-': return 0;
    }
}

int dp(const string &x,const string &y)
{
    int a=x.size(),b=y.size();
    vector<vector<int> > M(a+1,vector<int>(b+1,0));
    for(int i=1;i<a+1;++i)
        M[i][0]+=gap(x[i-1])+M[i-1][0];     
    for(int j=1;j<b+1;++j)
        M[0][j]+=gap(y[j-1])+M[0][j-1];   //n+1*n+1
    for(int i=1;i<a+1;++i)
    {
        for(int j=1;j<b+1;++j)
        {
            M[i][j]=min(mismatch(x[i-1],y[j-1])+M[i-1][j-1],min(M[i-1][j]+gap(x[i-1]),M[i][j-1]+gap(y[j-1])));
        }
    }
    return M[a][b];
}

int Hirschberg(const string &x,const string &y)
{
    string a,b;
    vector<string> ans;
	int res = 0;
    if(x.size()==0) {
        for (int i = 0; i < y.size(); ++i) {
            res  += gap(y[i]);
        }
        return res;
    }
    else if(y.size()==0) {
        for (int i = 0; i < x.size(); ++i) {
            res  += gap(x[i]);
        }
        return res;
    }
    else if(x.size()==1||y.size()==1)
    {
        return dp(x,y);
    }
    else
    {
        vector<int> cost1,cost2,cost;
        int res1, res2;
        string temp1,temp2,temp3,temp4,temp5;

        temp3=y.substr(0,y.size());
        int xmid=x.size()/2,ymid;
        temp1=x.substr(0,xmid);//0 - mid-1
        temp2=x.substr(xmid,x.size()-xmid);//mid - size-1

        reverse(temp2.begin(),temp2.end());
        reverse(temp3.begin(),temp3.end());

        cost1=DQ(temp1,y);
        cost2=DQ(temp2,temp3);
        reverse(cost2.begin(),cost2.end());

        for(int i=0;i<cost1.size();++i)
        {
            cost.push_back(cost1[i]+cost2[i]);
        }
        ymid=min_element(cost.begin(),cost.end())-cost.begin();
        temp4=y.substr(0,ymid);
        temp5=y.substr(ymid);
        temp2=x.substr(xmid);

        res1=Hirschberg(temp1,temp4);
        res2=Hirschberg(temp2,temp5);

        return res1 + res2;
    }
}

vector<int> DQ(const string &x,const string &y)
{
    //cout<<x<<endl<<y<<endl;
    vector<vector<int>> cost(2,vector<int>(y.size()+1,0));  
    //每次只取两列
    int cost1,cost2,cost3;
    for(int i=1;i<y.size()+1;++i)
        cost[0][i]=cost[0][i-1]+gap(y[i-1]);
    for(int i=0;i<x.size();++i)
    {
        cost[1][0]=gap(x[i])+cost[0][0];
        for(int j=1;j<y.size()+1;++j)
        {
            cost1=cost[0][j-1]+mismatch(x[i],y[j-1]);
            cost2=cost[0][j]+gap(x[i]);
            cost3=cost[1][j-1]+gap(y[j-1]);
            cost[1][j]=min(cost1,min(cost2,cost3));
        }
        cost[0].swap(cost[1]); //将原来的1列作为0列，1列重新进行计算
    }
    vector<int> ans(y.size());
    ans.swap(cost[0]);
    return ans;
}


int main()
{
    string A;
    string B;
    //char tmp1;
    //int countA = 0;
    //int countB = 0;
    freopen("Lab05-TestCase/Data-P3a1.txt","r",stdin);
	// while(cin >> tmp1 && tmp1 !='\n')
	// {
	// 	countA++;
	// 	A.push_back(tmp1);
	// }
	cin >> A;
    cin.clear();

    freopen("Lab05-TestCase/Data-P3b1.txt","r",stdin);
    // while(cin >> tmp1 && tmp1 !='\n')
	// {
	// 	countB++;
	// 	B.push_back(tmp1);
	// }
	cin >> B;
    //cout << endl << A.size() << endl << B.size() << endl;
    //int res = Hirschberg(A,B);
	int res = dp(A,B);
    cout << res << endl;
    return 0;
}