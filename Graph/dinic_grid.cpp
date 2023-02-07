class Dinic{
	int N, M;
	int MAX_DIST;
	vector<vector<int>> edge;
	vector<vector<int>> sat;
	vector<vector<int>> level;
	vector<vector<bool>> dead;
	vector<bool> isSource;
	vector<bool> isSink;

	bool hasFlow(int x, int y){
		return sat[x][y] != 0;
	}

	int getReverseEdge(int x, int y,  int k){
		int ny = y + (k - MAX_DIST);
		if(x == 0) return -1;
		if(ny < 0 || ny >= M) return -1;

		int b = (1<<(MAX_DIST - (k - MAX_DIST)));
		if(((sat[x-1][ny])&b) == 0) return -1;

		return ny;
	}

	int getNormalEdge(int x, int y, int k){
		int ny = y + (k - MAX_DIST);
		if(x == N-1) return -1;
		if(ny < 0 || ny >= M) return -1;

		int b = (1<<k);
		if(((edge[x][y])&b) == 0) return -1;
		if(((sat[x][y])&b) != 0) return -1;

		return ny; 
	}

	int getEdge(int x, int y, int k, bool rev){
		if(rev) return getReverseEdge(x, y, k);
		else return getNormalEdge(x, y, k);
	}

	void setFlowOnReverse(int x, int y, int k){
		int ny = y + (k - MAX_DIST);
		int b = (1<<(MAX_DIST - (k - MAX_DIST)));

		sat[x-1][ny] ^= b;
	}

	void setFlowOnNormal(int x, int y, int k){
		int ny = y + (k - MAX_DIST);
		int b = (1<<k);

		sat[x][y] ^= b;
	}

	void setFlowOnEdge(int x, int y, int k, bool rev){
		if(rev) setFlowOnReverse(x, y, k);
		else setFlowOnNormal(x, y, k);
	}

	bool BFS(){
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				level[i][j] = -1;
				dead[i][j] = false;
			}
		}

		queue<ii> q;
		for(int j=0;j<M;j++){
			if(hasFlow(0, j)) continue;
			if(!isSource[j]) continue;

			level[0][j] = 0;
			q.push({0, j});
		}

		while(!q.empty()){
			ii tp = q.front();
			q.pop();

			int x = tp.first;
			int y = tp.second;

			if(x == N-1 && isSink[y]) return true;

			for(int i=0;i<2*MAX_DIST + 1; i++){
				for(int k=0;k<2;k++){
					int nx = (k == 0? x+1 : x-1);
					int ny = getEdge(x, y, i, k);

					if(ny == -1) continue;
					if(level[nx][ny] != -1) continue;

					level[nx][ny] = level[x][y] + 1;
					q.push({nx, ny});
				}
			}
		}

		return false;
	}

	int DFS(int x, int y, int flow){
		if(dead[x][y]) return 0;
		if(x == N-1 && isSink[y]) return flow;
		if(flow == 0) return flow;

		int ret = 0;
		int f = 0;

		for(int i=0;i<2*MAX_DIST + 1 && flow;i++){
			for(int k=0;k<2 && flow;k++){
				int nx = (k == 0? x+1 : x-1);
				int ny = getEdge(x, y, i, k);

				if(ny == -1) continue;
				if(level[nx][ny] != level[x][y] + 1) continue;

				f = DFS(nx, ny, min(flow, 1));
				if(f == 0) continue;

				flow--;
				ret++;

				setFlowOnEdge(x, y, i, k);
			}
		}

		if(ret == 0) dead[x][y] = true;
		return ret;
	}

public:
	Dinic(int n, int m, int max_dist=10){
		N = n;
		M = m;
		MAX_DIST = max_dist;
		edge.resize(n);
		sat.resize(n);
		level.resize(n);
		dead.resize(n);

		isSource.resize(m, false);
		isSink.resize(m, false);

		for(int i=0;i<n;i++){
			edge[i].resize(m, 0);
			sat[i].resize(m, 0);
			level[i].resize(m, 0);
			dead[i].resize(m, false);
		}
	}

	void addEdge(int x, int y0, int yf){
		int b = (1<<((yf - y0) + MAX_DIST));
		edge[x][y0] |= b;
	}

	void setAsSource(int y){
		isSource[y] = true;
	}

	void setAsSink(int y){
		isSink[y] = true;
	}

	int maxflow(){
		int flow = 0;
		while(BFS()){
			for(int y=0;y<M;y++){
				if(level[0][y] != 0) continue;
				flow += DFS(0, y, INF);
			}
		}

		return flow;
	}
};

/*
 dinic for grids, flow 1 and edges on range for next row.
*/
