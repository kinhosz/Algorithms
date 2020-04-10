const ll INF = 1e9 + 7;

class Dinic{

	int source;
	int sink;
	int N;
	vector<ll> level;
	
public:
	struct Edge{
		int v;
		ll flow;
		ll cap;
	};

	vector<vector<Edge>> g;

	Dinic(int n){
		g.resize(n);
		N = n;
		level.resize(n);
	}

	void setInit(int u,int v){
		source = u;
		sink = v;
	}

	void addEdge(int u,int v,ll cap){
		Edge at;
		at.v = v;
		at.flow = 0;
		at.cap = cap;
		g[u].push_back(at);
	}
private:
	void residual(){

		vector<vector<Edge>> aux;
		aux.resize(N);

		for(int i=0;i<N;i++){
			for(auto at: g[i]){
				int v;
				if(at.flow < at.cap){
					aux[i].push_back(at);
				}

				if(at.flow > 0){
					v = at.v;
					at.v = i;
					at.cap = at.flow;
					at.flow = 0;
					aux[v].push_back(at);
				}
			}
		}
		g.clear();
		swap(g,aux);
	}

	bool BFS(){

		level[source] = 0;
		for(int i=0;i<N;i++) level[i] = INF;
		queue<int> q;
		q.push(source);

		while(!q.empty()){

			int u = q.front();
			q.pop();

			if(u == sink) return true;

			for(auto at: g[u]){
				if(level[at.v] == INF){
					level[at.v] = level[u] + 1;
					q.push(at.v);
				}
			}
		}

		return false;
	}

	ll maxflow(int u,ll flow){

		ll ret = 0;
		ll f = 0;
		if(u == sink) return flow;

		for(auto &at: g[u]){
			if(level[at.v] != level[u] + 1) continue;
			f = maxflow(at.v,min(flow,at.cap - at.flow));
			flow -= f;
			at.flow += f;
			ret += f;
		}
		return ret;
	}
public:
	ll run(){

		ll flow = 0;
		residual();
		while(BFS()){
			flow += maxflow(source,INF);
			residual();
		}

		return flow;
	}
};
