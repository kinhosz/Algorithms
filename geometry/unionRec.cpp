#include <bits/stdc++.h>
using namespace std;
#define asp ""
#define aps ''
#define one 1
#define two 2
#define dif !=
using namespace std;
const int maxn = 10004;
struct Node{

	int cover = 0;
	int score = 0;
};

vector<Node> tree(4*maxn);

// build o*(n*log n)
void build(int pos,int i,int j){

	int esq = two*pos;
	int dir = two*pos + one;
	int mid = (i+j)/two;

	tree[pos].cover = 0;
	tree[pos].score = 0;

	if(i == j) return ;
	build(esq,i,mid);
	build(dir,mid+one,j);	
}

int update(int pos,int i,int j,int l,int r,int op){

	int esq = two*pos;
	int dir = two*pos + one;
	int mid = (i+j)/two;
	int score = 0;

	if(i > r || j < l) return tree[pos].score;
	else if(i >= l && j <= r){

		tree[pos].cover += op;
		if(tree[pos].cover == 0 && i dif j){
			tree[pos].score = tree[esq].score + tree[dir].score;
		}
		else if(tree[pos].cover == 0){
			tree[pos].score = 0;
		}
		else tree[pos].score = (j-i +one);
	}
	else{
		tree[pos].score = update(esq,i,mid,l,r,op);
		tree[pos].score += update(dir,mid+one,j,l,r,op);

		if(tree[pos].cover > 0) tree[pos].score = (j-i + one);
	}

	return tree[pos].score;
}

int main(){

	int q;
	cin >> q;
	build(one,0,9);
	q *= two;
	while(q--){
		int x,y;
		string mod;
		cin >> x >> y >> mod;
		if(mod == "add"){
			cout << update(one,0,9,x,y,one) << endl;
		}
		else{
			cout << update(one,0,9,x,y,-one) << endl;
		}
	}
}