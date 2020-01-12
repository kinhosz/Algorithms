#include <bits/stdc++.h>
using namespace std;
#define space " " 
#define aps ''
#define one 1
#define two 2
#define dif !=
typedef long long ll;
typedef pair<ll,ll> ii;
vector<vector<ii>> g;
const int maxn = 10005;
int n_sz;
vector<int> pos(maxn);
vector<int> parent(maxn);
vector<ll> tree(4*maxn);
vector<int> sz(maxn);
vector<int> heavy(maxn);
vector<int> level(maxn);
vector<int> head(maxn);

void update(int pos,int i,int j,int x,ll val){

	int esq = two*pos;
	int dir = two*pos + one;
	int mid = (i+j)/two;

	if(i == j){
		tree[pos] = val;
		return ;
	}

	if(x <= mid) update(esq,i,mid,x,val);
	else update(dir,mid+one,j,x,val);

	tree[pos] = max(tree[esq],tree[dir]);
}

ll query(int pos,int i,int j,int l,int r){

	int esq = two*pos;
	int dir = two*pos + one;
	int mid = (i+j)/two;

	if(i>r || j < l) return 0;
	else if(i>= l && j <= r) return tree[pos];
	ll ret = query(esq,i,mid,l,r);
	ret = max(ret,query(dir,mid+one,j,l,r));

	return ret;
}

void dfs(int u,int lv){

	level[u] = lv;
	sz[u] = one;

	for(auto topo: g[u]){
		int v = topo.first;
		if(v == parent[u]) continue;
		parent[v] = u;
		dfs(v,lv+one);
		sz[u] += sz[v];
	}
}

void decompose(int u,int &x,bool keep){

	if(keep){
		head[u] = head[parent[u]];
	}
	else head[u] = u;

	pos[u] = x++;

	heavy[u] = -one;
	for(auto topo: g[u]){
		int v = topo.first;
		if(v == parent[u]) continue;
		if(sz[v] >= (sz[u] + one)/two) heavy[u] = v;
	}

	if(heavy[u] dif -one) decompose(heavy[u],x,true);

	for(auto topo: g[u]){
		int v = topo.first;
		if(v == parent[u] || v == heavy[u]) continue;
		decompose(v,x,0);
	} 
}

void hld_init(int n){

	n_sz = n;
	parent[0] = -one;
	dfs(0,0);
	int x=0;
	decompose(0,x,0);
}

void hld_update(int u,ll val){

	update(one,0,n_sz-one,pos[u],val);
}

int LCA(int u,int v){

	while(head[u] dif head[v]){
		if(level[head[u]] > level[head[v]]) u = parent[head[u]];
		else v = parent[head[v]];
	}

	return (level[u] < level[v]?u:v);
}

ll hld_find(int u,int v){

	if(level[u] < level[v]) swap(u,v);
	ll ret = 0;
	while(head[u] dif head[v]){
		ret = max(ret,query(one,0,n_sz-one,pos[head[u]],pos[u]));
		u = parent[head[u]];
	}

	ret = max(ret,query(one,0,n_sz-one,pos[v]+one,pos[u]));
	return ret;
}

ll hld_query(int u,int v){

	int l = LCA(u,v);

	ll ret = hld_find(u,l);
	ret = max(ret,hld_find(v,l));

	return ret;
}