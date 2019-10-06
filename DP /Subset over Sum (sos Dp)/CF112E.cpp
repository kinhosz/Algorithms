#include <bits/stdc++.h>
using namespace std;
#define asp ""
#define aps ''
#define one 1
#define two 2
#define dif !=
const int maxn = (one<<22);
typedef long long ll;
vector<int> dp(maxn);
vector<int> g;

void sosdp(){

	int bmask;

	for(int i=0;i<22;i++){
		for(int mask=0;mask<maxn;mask++){
			if(mask & (one<<i)){
				bmask = mask^(one<<i);
				dp[mask] = max(dp[mask],dp[bmask]);
			}
		}
	}
}

int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie();

	int n;
	cin >> n;
	g.clear();
	//for(int i=0;i<maxn;i++) dp[i] = 0;
	for(int i=0;i<n;i++){
		int a;
		cin >> a;
		g.push_back(a);
		dp[a] = a;
	}

	ll total = 0;

	sosdp();

	for(int i=0;i<g.size();i++){
		int mask = g[i];
		mask = mask^(maxn-one);
		if(dp[mask] dif 0) cout<<dp[mask]<<" ";
		else cout << -one << " ";
	}
	cout << endl;
}
