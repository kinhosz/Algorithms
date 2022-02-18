struct eertree {
	vector<vector<int>> t;
	int n, last, sz;
	vector<int> s, len, link;
	vector<ll> qt;

	eertree(int N) {
		t.resize(N+2, vector<int>(26));
		s = len = link = vector<int>(N+2);
		qt = vector<ll>(N+2);
		s[0] = -1;
		link[0] = 1, len[0] = 0, link[1] = 1, len[1] = -1;
		sz = 2, last = 0, n = 1;
	}

	void add(char c) {
		s[n++] = c -= 'a';
		while (s[n-len[last]-2] != c) last = link[last];
		if (!t[last][c]) {
			int prev = link[last];
			while (s[n-len[prev]-2] != c) prev = link[prev];
			link[sz] = t[prev][c];
			len[sz] = len[last]+2;
			t[last][c] = sz++;
		}
		qt[last = t[last][c]]++;
	}
	int size() { return sz-2; }
	ll propagate() {
		ll ret = 0;
		for (int i = n; i > 1; i--) {
			qt[link[i]] += qt[i];
			ret += qt[i];
		}
		return ret;
	}
};
