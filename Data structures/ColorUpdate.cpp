class ColorUpdate{

public:
	struct Range{

		Range(int l, int r, int c){
			this->l = l;
			this->r = r;
			this->color = c;
		}

		Range(int l){
			this->l = l;
		}

		int l;
		int r;
		int color;

		bool operator < (const Range &b) const { return l < b.l; }
	};

	bool exists(int x){

		auto it = ranges.upper_bound(Range(x));

		if(it == ranges.begin()) return false;
		it--;

		return it->l <= x && x <= it->r;
	}

	Range get(int x){

		auto it = ranges.upper_bound(Range(x));

		it--; // assuming it always exists

		return *it;
	}

	vector<Range> erase(int l, int r){

		vector<Range> ret;

		auto it = ranges.upper_bound(Range(l));

		if(it != ranges.begin()) it--;

		while(it != ranges.end()){

			if(it->l > r) break;
			else if(it->r >= l) ret.push_back(*it);

			it++;
		}

		if(ret.size() > 0){

			int sz = ret.size();

			auto s = ranges.lower_bound(Range(ret[0].l));
			auto e = ranges.lower_bound(Range(ret[sz-1].l));

			Range ts = *s;
			Range te = *e;

			e++;
			ranges.erase(s, e);

			Range r1 = Range(ts.l, l-1, ts.color);
			Range r2 = Range(r + 1, te.r, te.color);

			ret[0].l = max(ret[0].l, l);
			ret[sz-1].r = min(ret[sz-1].r, r);

			if(r1.l <= r1.r) ranges.insert(r1);
			if(r2.l <= r2.r) ranges.insert(r2);
		}

		return ret;
	}

	vector<Range> upd(int l, int r, int color){

		vector<Range> ret = erase(l, r);

		ranges.insert(Range(l, r, color));

		return ret;
	}

private:
	set<Range> ranges;
};
