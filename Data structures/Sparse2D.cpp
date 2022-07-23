class Sparse2D{
private:
	struct Node{
		ll c;
		Node *nodes[4];
 
		Node(ll c){
			this->c = c;
			for(int i=0;i<4;i++) this->nodes[i] = NULL;
		}
	};
 
	vector<ll> matrix;
 
	typedef Node* node;
 
	node root = NULL;
	ll default_color = 0;
 
	node create(ll c){
		node t = new Node(c);
		return t;
	}
 
	bool isLeaf(const vector<ll> &grid){
		return grid[0] == grid[1] && grid[2] == grid[3];
	}
 
	bool isInside(const vector<ll> &grid, const vector<ll> &window){
		bool eq = (grid[0] >= window[0] && grid[1] <= window[1]);
		eq = eq & (grid[2] >= window[2] && grid[3] <= window[3]);
 
		return eq;
	}
 
	bool isDisjoint(const vector<ll> &grid, const vector<ll> &window){
		bool eq = (grid[0] > window[1] || grid[1] < window[0]);
		eq = eq | (grid[2] > window[3] || grid[3] < window[2]);
 
		return eq;
	}
 
	void propagate(node t, const vector<ll> &grid){
		if(t->c == default_color) return ;
		if(isLeaf(grid)) return ;
 
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				int id = 2*i + j;
 
				if(!t->nodes[id]) t->nodes[id] = create(t->c);
				else (t->nodes[id])->c = t->c;
 
				if(grid[2] == grid[3]) break;
			}
 
			if(grid[0] == grid[1]) break;
		}
 
		t->c = default_color;
	}
 
	void replace(node &t, ll c, const vector<ll> &grid, const vector<ll> &window){
		if(!t) t = create(default_color);
		propagate(t, grid);
 
		if(isDisjoint(grid, window)) return ;
		if(isInside(grid, window)){
			t->c = c;
			return ;
		}
 
		ll midx = (grid[1] + grid[0])/2;
		ll midy = (grid[2] + grid[3])/2;
 
		for(int i=0;i<2;i++){
			vector<ll> ngrid(4);
 
			if(i == 0){
				ngrid[0] = grid[0];
				ngrid[1] = midx;
			}
			else{
				ngrid[0] = midx+ 1;
				ngrid[1] = grid[1];
			}
 
			for(int j=0;j<2;j++){
				int id = i*2 + j;
 
				if(j == 0){
					ngrid[2] = grid[2];
					ngrid[3] = midy;
				}
				else{
					ngrid[2] = midy + 1;
					ngrid[3] = grid[3];
				}
 
				replace(t->nodes[id], c, ngrid, window);
 
				if(grid[2] == grid[3]) break;
			}
			if(grid[0] == grid[1]) break;
		}
	}
 
	void getDistinctColors(node t, set<ll> &colors){
		if(!t) return ;
 
		if(t->c == default_color){
			for(int i=0;i<4;i++) getDistinctColors(t->nodes[i], colors);
		}
		else colors.insert(t->c);
	}
 
public:
	Sparse2D(ll x0, ll xf, ll y0 = 0, ll yf = 0){
		matrix.resize(4);
		matrix[0] = x0;
		matrix[1] = xf;
		matrix[2] = y0;
		matrix[3] = yf;
	}
 
	void replace(ll c, ll x0, ll xf, ll y0 = 0, ll yf = 0){
		vector<ll> window(4);
		window[0] = x0;
		window[1] = xf;
		window[2] = y0;
		window[3] = yf;
 
		replace(root, c, matrix, window);
	}
 
	int colorsCount(){
		set<ll> colors;
 
		getDistinctColors(root, colors);
 
		return colors.size();
	}
};

#TODO: improve memory management
