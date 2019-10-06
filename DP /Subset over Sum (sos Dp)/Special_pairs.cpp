#include <bits/stdc++.h>
using namespace std;
#define asp ""
#define aps ''
#define one 1
#define two 2
#define dif !=
const int maxn = (one<<20);
typedef long long ll;
vector<int> dp(maxn);
vector<int> g;

void sosdp(){

	int bmask;

	for(int i=0;i<20;i++){
		for(int mask=0;mask<maxn;mask++){
			if(mask & (one<<i)){
				bmask = mask^(one<<i);
				dp[mask] += dp[bmask];
			}
		}
	}
}

int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		g.clear();
		for(int i=0;i<maxn;i++) dp[i] = 0;
		for(int i=0;i<n;i++){
			int a;
			cin >> a;
			g.push_back(a);
			dp[a]++;
		}

		ll total = 0;

		sosdp();

		for(int i=0;i<n;i++){
			int mask = g[i];
			mask = mask^(maxn - one);
			total += dp[mask];
		}

		cout << total << endl;
	}

}
