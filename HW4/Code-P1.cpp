#include <iostream>
#include <vector>

using namespace std;

int getmax(int a, int b)
{
    if (a>b) return a;
    else
    {
        return b;
    }
    
}

int main()
{
    freopen("Lab05-TestCase/Data-P1.txt","r",stdin);
    vector <int> arr;
    int tmp;
    int count = 0;
    int sum = 0;
    while(cin >> tmp)
    {
        sum += tmp;
        count++;
        arr.push_back(tmp);
    }
    int target = sum / 2;
    vector<vector<int> >dp(count);//指定行数
    for(int i=0; i<dp.size(); i++)
	{
        dp[i].resize(target);
    }

    for (int i = 1; i < count; i++)
    {
        if(1 >= arr[i])
        {
            dp[i][0] = getmax(arr[i],0);
        }//cout << dp[i-1][j-arr[i]];        
    }

    for (int j = 1; j < target; j++)
    {
        if(j+1 >= arr[0])
        {
            dp[0][j] = getmax(arr[0],0);
        }//cout << dp[i-1][j-arr[i]];        
    }

    for (int i = 1; i < count; i++)
    {       
        for (int j = 1; j < target; j++)
        {
            if(j+1 >= arr[i] && j-arr[i] < target)//what if j - arr[i] > target?
            {
                dp[i][j] = getmax(dp[i-1][j],dp[i-1][j-arr[i]] + arr[i]);
            }//cout << dp[i-1][j-arr[i]];
            else
            {
                dp[i][j] = dp[i-1][j];
            }
            
        }
    }
    int max_sum = dp[count-1][target-1];

    cout << sum - 2 * max_sum << endl;

    return 0;
}