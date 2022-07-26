class Tetrix{
  private:

  struct Range{
    int l, r;
    int id;
    bool active;

    Range(int l, int r, int id): l(l), r(r), id(id), active(true) {}
  };

  int MAXN;
  vector<stack<int>> st;
  vector<Range> ranges;
  vector<int> tree;

  bool isCovered(int i, int j, int l, int r){
    return (l <= i && r >= j);
  }

  bool isDisjoint(int i, int j, int l, int r){
    return (l > j || r < i);
  }

  int lazyTop(int pos){
    return (st[pos].empty()? -1 : st[pos].top());
  }

  void lazy(int pos){
    while(!st[pos].empty()){
      int id = st[pos].top();
      if(!ranges[id].active) st[pos].pop();
      else break;
    }
  }

  int add(int pos, int i, int j, Range &range){
    int esq = 2*pos;
    int dir = 2*pos + 1;
    int mid = (i+j)/2;

    lazy(pos);

    if(isDisjoint(i, j, range.l, range.r));
    else if(isCovered(i, j, range.l, range.r)){
      st[pos].push(range.id);
    }
    else{
      tree[pos] = max(add(esq, i, mid, range), add(dir, mid+1, j, range));
    }

    return max(tree[pos], lazyTop(pos));
  }

  int remove(int pos, int i, int j, Range &range){
    int esq = 2*pos;
    int dir = 2*pos + 1;
    int mid = (i+j)/2;

    lazy(pos);

    if(isDisjoint(i, j, range.l, range.r) || isCovered(i, j, range.l, range.r));
    else{
      tree[pos] = max(remove(esq, i, mid, range), remove(dir, mid+1, j, range));
    }

    return max(tree[pos], lazyTop(pos));
  }

  int query(int pos, int i, int j, int l, int r){
    int esq = 2*pos;
    int dir = 2*pos + 1;
    int mid = (i+j)/2;

    if(isDisjoint(i, j, l, r)) return -1;
    else if(isCovered(i, j, l, r)) return max(tree[pos], lazyTop(pos));
    else{
      return max({query(esq, i, mid, l, r), query(dir, mid+1, j, l, r), lazyTop(pos)});
    }
  }

  public:
  
  Tetrix(int maxn){
    MAXN = maxn;
    tree.resize(4*MAXN + 3, -1);
    st.resize(4*MAXN + 3);
  }

  void push(int l, int r, int id){
    Range range(l, r, id);
    ranges.push_back(range);
    add(1, 0, MAXN-1, range);
  }

  void pop(int id){
    Range range = ranges[id];
    ranges[id].active = false;
    remove(1, 0, MAXN-1, range);
  }

  int get(int l, int r){
    int id = query(1, 0, MAXN-1, l, r);
    return id;
  }  
};
