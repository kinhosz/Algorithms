#include <bits/stdc++.h>
using namespace std;
#define asp ""
#define aps ''
#define one 1
#define two 2
#define dif !=
const int maxn = (one<<24);
vector<int> dp(maxn);


void sosdp(){

	int bmask = 0;
	for(int i=0;i<24;i++){
		for(int mask=0;mask<maxn;mask++){
			if(mask & (one<<i)){
				bmask = mask^(one<<i);
				dp[mask] += dp[bmask];
			}
		}
	}
}

int solve(int n){

	int ret = 0;
	int aux;
	for(int mask=0;mask<maxn;mask++){
		aux = n-dp[mask];
		aux *= aux;
		ret ^= aux;
	}

	return ret;
}

int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	string s;
	int x;
	int bmask = 0;
	for(int i=0;i<n;i++){
		cin >> s;
		bmask = 0;
		for(int j=0;j<3;j++){
			x = s[j] - 'a';
			bmask = bmask|(one<<x);
		}
		dp[bmask]++;
	}	

	sosdp();

	cout << solve(n) << endl;
}
