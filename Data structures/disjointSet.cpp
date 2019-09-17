#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

class DSU{

private: vi p,rank;
public:
	void create(int N){
		rank.assign(N,1);
		p.resize(N);
		for(int i=0;i<N;i++) p[i] = i;
	}
	int find(int i){
		return (p[i] == i?i:(p[i] = find(p[i])));
	}
	bool isSameSet(int u,int v){

		return (find(p[u]) == find(p[v]));
	}
	void unionSet(int u,int v){
		u = find(p[u]);
		v = find(p[v]);
		if(!isSameSet(u,v)){
			if(rank[u] > rank[v]) swap(u,v);
			p[u] = v;
			rank[v]+= rank[u];
		}
	}
};
