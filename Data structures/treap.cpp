#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class Treap{

private:
	struct Node{

		ll key; // key
		ll prior; // randomized
		ll value; // value for this node
		ll tree; // value for this subtree

 		Node *l; // data of l node
 		Node *r; // data of r node
 		Node(){}
 		Node(ll key, ll value): key(key),
 		 value(value), prior(uniform_int_distribution<int>()(rng)), l(NULL), r(NULL){}
	};
	typedef Node* node;

	node root = NULL;

	void split(node t, ll key, node &l, node &r){

		if(!t){
			l = r = NULL;
		}
		else if(t->key <= key){
			split(t->r, key, t->r, r), l = t;
		}
		else{
			split(t->l, key, l, t->l), r = t;
		}

		update(t);
	}

	void insert(node &t, node item){

		if(!t){
			t = item;
		}
		else if(item->prior > t->prior){
			split(t, item->key, item->l, item->r), t = item;
		}
		else if(t->key <= item->key){
			insert(t->r, item);
		}
		else{
			insert(t->l, item);
		}

		update(t);
	}

	void merge(node &t, node l, node r) {
	    if (!l || !r)
	        t = l ? l : r;
	    else if (l->prior > r->prior)
	        merge (l->r, l->r, r),  t = l;
	    else
	        merge (r->l, l, r->l),  t = r;

	    update(t);
	}

	void erase(node &t, ll key){
		node th;

		if(!t) return ;

		if(t->key == key){
			th = t;
			merge(t, t->l, t-> r);
			delete th;
		}
		else if(t->key < key){
			erase(t->r, key);
		}
		else{
			erase(t->l, key);
		}

		update(t);
	}

	ll getValue(node t){

		if(!t) return -1;

		return t->value;
	}

	ll getTree(node t){

		if(!t) return 0;

		return t->tree;
	}

	void update(node t){

		if(!t) return ;
		t->tree = t->value;
		t->tree += getTree(t->l);
		t->tree += getTree(t->r);
	}

	ll prefix(node t, ll key){

		if(!t) return 0;

		if(t->key <= key){
			return getTree(t->l) + prefix(t->r, key) + t->value;
		}
		else{
			return prefix(t->l, key);
		}
	}

	ll suffix(node t, ll key){

		if(!t) return 0;

		if(t->key < key){
			return suffix(t->r, key);
		}
		else{
			return suffix(t->l, key) + getTree(t->r) + t->value;
		}
	}

	ll find(node t, ll key){

		if(!t) return -1;

		if(t->key == key) return t->value;
		if(t->key < key) return find(t->r, key);
		else return find(t->l, key);
	}

public:
	void add(ll key, ll value){
		node t = new Node(key, value);
		insert(root, t);
	}

	void remove(ll key){
		erase(root, key);
	}

	ll prefix(ll key){
		return prefix(root, key);
	}

	ll suffix(ll key){
		return suffix(root, key);
	}

	ll find(ll key){
		return find(root, key);
	}
};

int main(){

}
