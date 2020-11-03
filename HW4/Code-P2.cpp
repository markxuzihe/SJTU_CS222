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

class Item
{
public:
    int val;
    int weight;
    Item(int a, int b)
    {
        val = a;
        weight = b;
    }
    ~Item(){};
};

int main()
{
    freopen("Lab05-TestCase/Data-P2.txt","r",stdin);
    vector <Item> arr;
    int n;
    cin >> n;
    int tmp1,tmp2;
    int T_storage = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> tmp1 >> tmp2;
        T_storage += tmp1;
        arr.push_back(Item(tmp1,tmp1+tmp2));
    }
    //total backpack storage

    vector<vector<int>> dp(n+1);
    for(int i=0; i<dp.size(); i++)
	{
        dp[i].resize(T_storage+1);
    }

    for (int i = 1; i <= n; i++)
    {       
        for (int j = 1; j <= T_storage; j++)
        {
            if (arr[i-1].weight <= j)
            {
                dp[i][j] = getmax(dp[i-1][j],dp[i-1][j-arr[i-1].weight] + arr[i-1].val);
            }
            else
            {
                dp[i][j] = dp[i-1][j];
            }
            
        }
    }
/*
    for (int i = 1; i <= n; i++)
    {       
        for (int j = 1; j <= T_storage; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }  
*/
    cout << T_storage - dp[n][T_storage] << endl;

    return 0;
}