#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int tree[N];

int query(int x){

	int s = 0;

	while(x > 0){
		s += tree[x];
		x -= (x & -x);
	}

	return s;
}

void update(int x,int v){

	while(x < N){
		tree[x] += v;
		x += (x & -x);
	}
}