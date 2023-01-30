class MergeSortTree{
  struct Node{
    vector<int> vs;

    void add(int v){
      this->vs.push_back(v);
    }

    void build(){
      sort(vs.begin(), vs.end());
    }
  };
  vector<Node> nodes;

  int N;

  void add(int p, int l, int r, int x, int v){
    int m = (l+r)/2;
    int pl = p*2;
    int pr = p*2 + 1;

    nodes[p].add(v);
    if(l == r) return;

    if(x <= m) add(pl, l, m, x, v);
    else add(pr, m+1, r, x, v);
  }

  void build(int p){
    if(p >= nodes.size()) return;
    nodes[p].build();
    build(2*p);
    build(2*p + 1);
  }

public:
  MergeSortTree(int n){
    N = n;
    nodes.resize(4*n);
  }

  void add(int x, int v){
    add(1, 0, N-1, x, v);
  }

  void build(){
    build(1);
  }
};
