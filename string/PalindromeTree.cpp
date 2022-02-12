class pTree{
public:

	int s[MAXN], Link[MAXN], Len[MAXN], Edge[MAXN][SIGMA];
	int node, cursor, n;
	ll cnt[MAXN];

	void init(){
		s[n++]=-1;
		Link[0]=1; Len[0]=0;
		Link[1]=1; Len[1]=-1;
		node=2;
	}

	int getLink(int v){
		while(s[n-Len[v]-2]!=s[n-1]) v=Link[v];
		return v;
	}

	void addLetter(int c){
		s[n++]=c;
		cursor=getLink(cursor);

		if(!Edge[cursor][c]){
			Len[node]=Len[cursor]+2;
			Link[node]=Edge[getLink(Link[cursor])][c];
			cnt[node]++;
			Edge[cursor][c]=node++;
		}
		else{
			cnt[Edge[cursor][c]]++;
		}

		cursor=Edge[cursor][c];
	}

	void clear(){
		for(int i=0;i<=node;i++){
			cnt[i]=0;
			memset(Edge[i], 0, sizeof Edge[i]);
		}
		n=0;
		cursor=0;
	}
};
