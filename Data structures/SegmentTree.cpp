/*
add: add a value to current node on tree
join: join a query on lazy node
merge: combine two nodes into one */
class SegTree{
	int N;
	vector<ll> tree;
	vector<ll> lazy;

	ll add(ll curr, int i, int j, ll v){
		return curr + v * ll(j - i + 1);
	}

	ll join(ll curr, ll v){
		return curr + v;
	}

	ll merge(ll v1, ll v2){
		return v1 + v2;
	}

	void propagate(int pos, int i, int j){
		int esq = 2*pos;
		int dir = 2*pos + 1;

		if(lazy[pos]){
			tree[pos] = add(tree[pos], i, j, lazy[pos]);
			if(i < j){
				lazy[esq] = join(lazy[esq], lazy[pos]);
				lazy[dir] = join(lazy[dir], lazy[pos]);
			}
			lazy[pos] = 0;
		}
	}

	void upd(int pos, int i, int j, int l, int r, ll v){
		int esq = 2*pos;
		int dir = 2*pos + 1;
		int mid = (i+j)/2;

		propagate(pos, i, j);

		if(i > r || j < l) return;
		else if(i >= l && j <= r){
			tree[pos] = add(tree[pos], i, j, v);
			if(i < j){
				lazy[esq] = join(lazy[esq], v);
				lazy[dir] = join(lazy[dir], v);
			}
		}
		else{
			upd(esq, i, mid, l, r, v);
			upd(dir, mid+1, j, l, r, v);
			tree[pos] = merge(tree[esq], tree[dir]);
		}
	}

	ll qry(int pos, int i, int j, int l, int r){
		int esq = 2*pos;
		int dir = 2*pos + 1;
		int mid = (i+j)/2;

		propagate(pos, i, j);

		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[pos];
		else return merge(qry(esq, i, mid, l, r), qry(dir, mid+1, j, l, r));
	}

public:
	SegTree(int n){
		N = n;
		tree.resize(4*N + 3);
		lazy.resize(4*N + 3);
	}

	void upd(int l, int r, ll v){
		upd(1, 0, N-1, l, r, v);
	}

	ll qry(int l, int r){
		return qry(1, 0, N-1, l, r);
	}
};
