const ll INF = 1e9 + 7;

class Dinic{
	int N;
	vector<ll> level;
	vector<bool> dead;
	
public:
	struct Edge{
		Edge(int a,ll x){
			v = a;
			cap = x;
		}
		int v;
		ll cap;
	};
	int source;
	int sink;
	vector<Edge> edge;
	vector<vector<int>> g;

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
		g[u].push_back(edge.size());
		edge.push_back(Edge(v,cap));
		g[v].push_back(edge.size());
		edge.push_back(Edge(u,0));
	}
private:

	bool BFS(){
		
		for(int i=0;i<N;i++) level[i] = INF;
		dead.clear();
		dead.resize(N, false);
		level[source] = 0;
		queue<int> q;
		q.push(source);

		while(!q.empty()){

			int u = q.front();
			q.pop();

			if(u == sink) return true;

			for(auto x: g[u]){
				if(level[edge[x].v] == INF && edge[x].cap > 0){
					level[edge[x].v] = level[u] + 1;
					q.push(edge[x].v);
				}
			}
		}
		return false;
	}

	ll maxflow(int u,ll flow){
		
		if(dead[u]) return 0;

		ll ret = 0;
		ll f = 0;
		if(flow == 0) return 0;
		if(u == sink) return flow;

		for(auto i: g[u]){
			if(level[edge[i].v] != level[u] + 1) continue;
			f = maxflow(edge[i].v,min(edge[i].cap,flow));
			int x = (i%2 == 0?i+1:i-1);
			flow -= f;
			ret += f;
			edge[i].cap -= f;
			edge[x].cap += f;
		}
		
		if(ret == 0) dead[u] = true;
		
		return ret;
	}
public:
	ll run(){

		ll flow = 0;
		while(BFS()){
			flow += maxflow(source,INF);
		}

		return flow;
	}
};
