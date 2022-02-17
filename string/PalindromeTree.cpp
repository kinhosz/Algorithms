class pTree{
private:
	int MAXN;
	int SIGMA;

	void init(){
		s.resize(MAXN);
		Link.resize(MAXN);
		Len.resize(MAXN);
		Edge.resize(MAXN, vector<int>(SIGMA, 0));
		cnt.resize(MAXN, 0);
		n = 0;
		cursor = 0;

		s[n++] = -2; // empty string
		s[n++]=-1; // imaginary string
		Link[0]=1; Len[0]=0;
		Link[1]=1; Len[1]=-1;
		node=2;
	}

	int getLink(int v){
		while(v != 1 && s[n-Len[v]-2]!=s[n-1]) v=Link[v];
		return v;
	}

public:

	vector<int> s, Link, Len;
	vector<vector<int>> Edge;
	int node, cursor, n;
	vector<ll> cnt;

	pTree(int maxn, int sigma){
		MAXN = maxn + 3;
		SIGMA = sigma;

		this->init();
	}

	void addLetter(int c){
		s[n++]=c;
		cursor=getLink(cursor);

		if(!Edge[cursor][c]){
			Len[node]=Len[cursor]+2;
			Link[node]=Edge[getLink(Link[cursor])][c];
			cnt[node]++;
			Edge[cursor][c]=node++;
		}
		else{
			cnt[Edge[cursor][c]]++;
		}

		cursor=Edge[cursor][c];
	}

	ll propagate(){
		ll ans = 0;

		for(int i=node-1;i>=2;i--){
			ll x = cnt[i];
			int link = Link[i];
			if(link > 1) cnt[link] += x;

			ans += x;
		}

		return ans;
	}
};
