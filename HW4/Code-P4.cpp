#include <iostream>
#include <vector>
#include<cstdio>

using namespace std;
vector<vector<int> >dp;
vector<int> res;
vector<int> arr;

int getmin(int a, int b)
{
    if (a>b) return b;
    else
    {
        return a;
    }
    
}


void show(int i, int j, bool flag)
{
    if (i == j+1) return;
    if (dp[i+1][j] <= dp[i][j-1])
    {
        if(flag) {/*cout << arr[i] << " ";*/res.push_back(arr[i]);};
        flag = !flag;
        i++;
    }
    else
    {
        if(flag) {/*cout << arr[j] << " ";*/res.push_back(arr[j]);};
        flag = !flag;
        j--;
    }
    show(i,j,flag);
    
}

int main()
{
    freopen("Lab05-TestCase/Data-P4.txt","r",stdin);
    //freopen("res4.txt","w",stdout);
    //vector <int> arr;
    int tmp;
    int count = 0;
    int sum = 0;
    while(cin >> tmp)
    {
        count++;
        arr.push_back(tmp);
    }
    //vector<vector<int> >dp(count+1);//指定行数
    dp.resize(count+1);
    for(int i=0; i<count+1; i++)
	{
        dp[i].resize(count+1);
    }
    for (int i=count-1; i>=0; i--)
    {
        sum = 0;
        for (int j=0; j<count; j++)
        {
            //if(i == j) dp[i][j] = arr[i];
            if(i > j) 
            {
                dp[i][j] = 0;
            }
            else
            {
                sum  += arr[j];
                dp[i][j] = sum - getmin(dp[i+1][j],dp[i][j-1]);
            }
            
        }
    }  
    /*for (int i=count; i>=0; i--)
    {
        for (int j=0; j<=count; j++)
        {
            cout << dp[i][j] << "\t";
            
        }
        cout << endl;
    }*/
    cout << "choice list: ";
    show(0, count-1, true);
    for (int i=0; i < count - count/2; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl << "final profit: " << dp[0][count-1] << endl;
    return 0;
}