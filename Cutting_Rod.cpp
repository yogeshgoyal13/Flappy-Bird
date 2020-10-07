#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int CuttingRod(int x,vector<int> &prices,vector<int> &dp){
    if(x==0){
        return 0;
    }
    if(dp[x]!=-1){
        return dp[x];
    }
    int ans=1000000;
    for(int i=1;i<=x;i++){
        ans=min(CuttingRod(x-i,prices,dp)+prices[i],ans);
    }
    dp[x]=ans;
    return dp[x];
}

int main(){
vector<int>prices={0,1,5,8,9,10,17,17,20};
vector<int> dp(prices.size(),-1);
cout<<CuttingRod(prices.size()-1,prices,dp)<<endl;

return 0;
}