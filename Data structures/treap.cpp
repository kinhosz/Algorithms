typedef long long ll;

class Treap{

	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	struct Node{
		ll key; // key
		ll prior; // randomized
 		ll value; // value of node
 		int cnt;
 		Node *l; // data of left node
 		Node *r; // data of right node
 		Node(){}
 		Node(int key): key(key), prior(uniform_int_distribution<int>(0, 1e9+7)(rng)), l(NULL), r(NULL){}
	};
	typedef Node* node;


	void split(node t, int key, node &l, node &r){
		if(!t){
			r = l = NULL;
		}
		else if(t->key <= key){
			split(t->r, key, t->r, r), l = t;
		}
		else{
			split(t->l, key, l, t->l), r = t;
		}
	}

	void insert(node &t, node it){
		if(!t)
			t = it;
		else if(it->prior > t->prior)
			split(t, it->key,it->l, it->r), t = it;
		else
			insert (t->key <= it->key ? t->r : t->l, it);
	}

	void merge(node &t, node l, node r) {
	    if (!l || !r)
	        t = l ? l : r;
	    else if (l->prior > r->prior)
	        merge (l->r, l->r, r),  t = l;
	    else
	        merge (r->l, l, r->l),  t = r;
	}

	void erase(node &t, int key) {
	    if (t->key == key) {
	        pitem th = t;
	        merge(t, t->l, t->r);
	        delete th;
	    }
	    else
	        erase(key < t->key ? t->l : t->r, key);
	}

	node unite(node l, node r) {
	    if (!l || !r)  return l ? l : r;
	    if (l->prior < r->prior)  swap (l, r);
	    node lt, rt;
	    split(r, l->key, lt, rt);
	    l->l = unite (l->l, lt);
	    l->r = unite (l->r, rt);
	    return l;
	}

	int cnt(node t) {
	    return t ? t->cnt : 0;
	}

	void upd_cnt(node t) {
	    if (t)
	        t->cnt = 1 + cnt(t->l) + cnt (t->r);
	}
}
