class CHTPersistent{
  struct Line{
    ll m;
    ll c;
    Line(){}
    Line(ll _m, ll _c): m(_m), c(_c){}
  };

  vector<vector<Line>> hull;
  int SZ = 0;
  vector<int> version_idx;
  vector<int> version_sz;

  double inter(Line t1, Line t2){
    double ret;
    ret = (double)(t2.c - t1.c)/(t1.m - t2.m);
    return ret;
  }

  void add(Line curr){
    Line temp, temp2;
    version_sz.push_back(SZ);

    if(SZ > 1){
      int s = 0;
      int e = SZ-1;

      while(s < e){
        int p = (s+e)/2;

        temp = hull[p+1].back();
        temp2 = hull[p].back();

        double point = inter(temp, temp2);
        double point2 = inter(temp, curr);

        if(point < point2){
          s = p+1;
        }
        else{
          e = p;
        }
      }
      SZ = s+1;
    }

    if(hull.size() == SZ){
      vector<Line> x;
      hull.push_back(x);
    }

    hull[SZ].push_back(curr);
    version_idx.push_back(SZ);
    SZ++;
  }

public:
  void add(ll m, ll c){
    add(Line(m, c));
  }

  ll query(ll find){
    int s = 0;
    int e = SZ-1;

    while(s < e){
      int p = (s+e)/2;

      double point = inter(hull[p].back(), hull[p+1].back());
      if(point < find){
        s = p+1;
      }
      else{
        e = p;
      }
    }

    ll ret = (hull[s].back().m * find) + hull[s].back().c;
    return ret;
  }

  void rollback(){
    SZ = version_sz.back();
    version_sz.pop_back();
    hull[version_idx.back()].pop_back();
    version_idx.pop_back();
  }

  int size(){
    return SZ;
  }
};

// log(n) for query & add. O(1) for rollback. All lines should be added in crescent angular coef order
