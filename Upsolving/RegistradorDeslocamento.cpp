#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define asp ""
#define aps ''
#define one 1
#define two 2
#define dif !=

int matrix[35][35];
int help[35][35];

string s;
vector<pair<ll,ll>> dp;
vector<int> torneira;

void input(int n,int t){

	torneira.clear();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j] = 0;
		}
	}
	for(int i=0;i<n-one;i++){
		matrix[i+one][i] = one;
	}

	for(int i=0;i<t;i++){
		int a;
		cin >> a;
		torneira.push_back(a);
		a = (n-one)-a;
		if((n-one) == a) continue;
		matrix[a+one][n-one] = one;
	}
	matrix[0][n-one] = one;
}

ll toNumber(){

	ll ret = 0;

	for(int i=0;i<s.size();i++){
		ret *= 16;
		if(s[i] >= '0' && s[i] <= '9'){
			ret += (ll)(s[i] - 48);
		}
		else{
			ret += (ll)(10 + (s[i]-'a'));
		}
	}

	return ret;
}

void preProcess(ll part,ll start,int n){

	dp.clear();
	dp.push_back({start,0});

	for(ll i=one;i<=part;i++){
		int cont = 0;
		for(int j=0;j<torneira.size();j++){
			ll mask;
			mask = start&(ll(one) << torneira[j]);
			if(mask dif 0) cont++;
		}

		cont %= two;
		start = (start >> one);
		if(cont) start += (pow(two,n-one));

		dp.push_back({start,i});
	}

	sort(dp.begin(),dp.end());
}

ll busca(ll find){

	int s = 0;
	int e = dp.size()-one;
	int p = (s+e)/two;

	while(s <= e){

		if(dp[p].first == find) return dp[p].second;
		else if(dp[p].first > find){
			e = p-one;
			p = (s+e)/two;
		}
		else{
			s = p+one;
			p = (s+e)/two;
		}
	}

	return -one;
}

ll calc(ll end, ll part, int n){

	vector<int> value;

	for(int i=n-one;i>=0;i--){
		ll mask;
		mask = end&(ll(one) << i);
		if(mask) value.push_back(one);
		else value.push_back(0);
	}

	vector<int> resp;

	for(int i=0;i<n;i++){
		int cont = 0;
		for(int j=0;j<n;j++){
			cont += (matrix[j][i] * value[j]);
		}
		resp.push_back(cont%two);
	}
	end = 0;
	for(int i=0;i<n;i++){
		end *= two;
		end += resp[i];
	}

	return end;
}

ll solve(ll part, ll pivo, int n){

	//printf("part -> %lld\n",part);
	for(ll i =0;i<part;i++){
		//printf("pivo -> %lld\n",pivo);
		ll ret = busca(pivo);
		if(ret > -one){
			return (i*part + ret);
		}

		pivo = calc(pivo,part,n);
	}

	return -one;
}

void mult(int n){

	int temp[n][n];

	int cont = 0;
	for(int i=0;i<n;i++){
		cont = 0;
		for(int k=0;k<n;k++){
			cont = 0;
			for(int j=0;j<n;j++){
				cont += (matrix[i][j] * help[j][k]);
			}
			temp[i][k] = cont%two;
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			help[i][j] = temp[i][j];
		}
	}
}

void autoMult(int n){

	int temp[n][n];

	int cont = 0;
	for(int i=0;i<n;i++){
		cont = 0;
		for(int k=0;k<n;k++){
			cont = 0;
			for(int j=0;j<n;j++){
				cont += (matrix[i][j] * matrix[j][k]);
			}
			temp[i][k] = cont%two;
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j] = temp[i][j];
		}
	}
}

void fastExp(ll part, int n){

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			help[i][j] = matrix[i][j];
		}
	}

	part--;

	while(part>0){
		if((part&(ll(one)))){
			mult(n);
		}
		autoMult(n);
		part = (part >> one);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j] = help[i][j];
		}
	}
}

int main(){

	int n,t;
	ll start,end;

	cin >> n >> t;
	while(n dif 0 || t dif 0){

		input(n,t);
		cin >> s;
		start = toNumber();
		//printf("start = %lld\n",start);
		cin >> s;
		end = toNumber();
		//printf("end = %lld\n",end);

		ll part;
		part = sqrt(pow(two,n));
		if(part*part < pow(two,n)) part++;
		preProcess(part,start,n);
		fastExp(part,n);
		ll ans = solve(part,end,n);

		if(ans == -one) printf("*\n");
		else printf("%lld\n",ans);
		cin >> n >> t;
	}
}


