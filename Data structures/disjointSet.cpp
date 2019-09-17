#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

class DSU{

private: vi p,rank;
public: 
  void create(int N){
    rank.assign(N,0);
    for(int i=0;i<N;i++) p.push_back(i);
  }
  int unionFind(int i){
    if(p[i] == i) return i;
    else{
      rank[i] = 0;
      return (p[i] = unionFind(p[i]));
    }
  }
  bool isSameSet(int i,int j){
    return (unionFind(p[i]) == unionFind(p[j]));
  }
  void unionSet(int u,int v){
    if(rank[u] > rank[v]) swap(u,v);
    if(!isSameSet(u,v)){
      p[u] = unionFind(p[v]);
      rank[u]++;
    }
  }
};