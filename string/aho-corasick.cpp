class Aho{
	vector<map<char, int>> to;
	vector<int> link, term, exit, sobe; 
	int idx = 0;

public:
	Aho(int maxn){
		to.resize(maxn);
		link.resize(maxn, 0);
		term.resize(maxn, 0);
		exit.resize(maxn, 0);
		sobe.resize(maxn, 0);
	}
	
	void insert(string &s){
		int at = 0;
		for(char c: s){
			auto it = to[at].find(c);
			if(it == to[at].end()) to[at][c] = ++idx;
			it = to[at].find(c);
			at = it->second;
		}
		term[at]++, sobe[at]++;
	}

	// nao esquecer de chamar o build dps de inserir
	void build(){
		queue<int> q;
		q.push(0);
		link[0] = exit[0] = -1;
		while(q.size()){
			int i = q.front(); q.pop();
			for(auto p: to[i]){
				int c = p.first, j = p.second;
				int l = link[i];
				while(l != -1 and !to[l].count(c)) l = link[l];
				link[j] = l == -1 ? 0 : to[l][c];
				exit[j] = term[link[j]] ? link[j] : exit[link[j]];
				if(exit[j]+1) sobe[j] += sobe[exit[j]];
				q.push(j);
			}
		}
	}

	// pegando todos os padroes
	int query(string &s){
		int at=0, ans=0;
		for(char c: s){
			while(at != -1 and !to[at].count(c)) at = link[at];
			at = at == -1 ? 0 : to[at][c];
			ans += sobe[at];
		}

		return ans;
	}
};

// link de referencia @brunomaletta: https://github.com/brunomaletta/Biblioteca/tree/master/Codigo
