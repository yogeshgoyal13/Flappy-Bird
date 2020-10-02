#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// int kanpsack(vector<int>&cost,vector<int>& weight,int tar){
//     vector<vector<int>>dp(cost.size(),vector<int>(tar+1,0));
//     for(int i=0;i<=tar;i++){
//         for(int j=1;j<cost.size();j++){
//             if(i==0){
//                 dp[i][j]=j-weight[i]<=cost[i]: 0;
//             }
//             else{
//                 int taken=0;
//                 if(j-weight[i]>=0){
//                     taken=dp[i-1][j-weight[i]]+cost[i];
//                 }
//                 dp[i][j]=max(dp[i-1][j],taken);
//             }
//         }
//     }
//     return dp[cost.size()-1][tar];
// }



// #include <bits/stdc++.h>
// using namespace std;

int main() {
	int t;
	cin>>t;
	for(int x=0;x<t;x++)
{	
	int N,M;
	cin>>N>>M;
	int arr[N][M];
	
	long frequency=N*M;
	
	for(int i=0;i<N;i++)
	{			
	     for(int j=0;j<M;j++)
	     cin>>arr[i][j];
	}
	int Maximum_Length=min(N,M);
	for(int length=3;length<=Maximum_Length;length=length+2)
	{
		int j1=length/2;
		//cout<<length<<endl;
		for(	int i1= length/2 ;i1<=N-1-length/2;i1++){
		    for(int j1= length/2;j1<=M-1-length/2;j1++){
                 bool is_true = true;
				 for(int k=length/2; k>0;k--){
					if((arr[i1][j1-k]!=arr[i1][j1+k])||(arr[i1-k][j1]!=arr[i1+k][j1]))
					{
						is_true=false;
						break;
					}
    				
			}
			if(is_true)
			frequency++;
		}
	  }
	}
	//frequency=frequency-(Maximum_Length/2-1);	
	cout<<frequency<<endl;
	}
	return 0;
}