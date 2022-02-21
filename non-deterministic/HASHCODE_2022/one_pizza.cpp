#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int N;

map<string, int> ingr_id;
vector<string> id_ingr;

vector<vector<int>> like;
vector<vector<int>> dlike;

vector<bool> pizza;

void Rinput(){

	cin >> N;

	for(int i=0;i<N;i++){
		int l;
		cin >> l;
		vector<int> aux;
		for(int j=0;j<l;j++){
			string x;
			cin >> x;
			if(ingr_id.count(x) == 0){
				ingr_id[x] = id_ingr.size();
				id_ingr.push_back(x);
			}

			int id = ingr_id[x];
			aux.push_back(id);
		}

		like.push_back(aux);

		int d;
		cin >> d;
		aux.clear();
		for(int j=0;j<d;j++){
			string x;
			cin >> x;
			if(ingr_id.count(x) == 0){
				ingr_id[x] = id_ingr.size();
				id_ingr.push_back(x);
			}

			int id = ingr_id[x];
			aux.push_back(id);
		}

		dlike.push_back(aux);
	}

	pizza.resize(id_ingr.size(), false);
}

void Woutput(int id, string name, vector<bool> &S){
	int ing = 0;
	for(int i=0;i<S.size();i++){
		if(S[i]) ing++;
	}

	cout << ing;

	for(int i=0;i<S.size();i++){
		if(!S[i]) continue;

		cout << " " << id_ingr[i];
	}
	cout << endl;
}

void printinfo(double temp, int it, int sc){
	cerr << "temp: " << temp << ", " << "inter: " << it << ", " << "score: " << sc << endl;
}

int getneighborhood(){

	int id = uniform_int_distribution<int>(0, pizza.size())(rng);
	return id;
}

int score(vector<bool> &S){

	int sc = 0;

	for(int i=0;i<N;i++){
		bool ok = true;
		for(int j=0;j<like[i].size();j++){
			int id = like[i][j];

			if(!S[id]){
				ok = false;
				break;
			}
		}

		if(!ok) continue;

		ok = true;
		for(int j=0;j<dlike[i].size();j++){
			int id = dlike[i][j];

			if(S[id]){
				ok = false;
				break;
			}
		}

		sc += ok;
	}

	return sc;
}

void sAnnealing(){
	// pseudo-code
	/************* setar isso aqui inicialmente

	S0 = estado inicial
	M = numero maximo de iteracoes
	P = pertubacoes por iteracao
	L = numero maximo de sucessos por iteracoes
	alpha = fator de reducao da temperatura

	******************************************/
	string test = "A";

	int M = 1000000;
	int P = 50;
	int L = 100;
	double alpha = 0.9995;

	vector<bool> S = pizza;
	double T0 = 200;
	double T = T0;

	int nSucesso = 1;

	int log_size = 100;

	for(int i=0;i<=M && nSucesso > 0;i++){
		if(i%log_size == 0){
			printinfo(T, i, score(S));
			//Woutput(i/log_size, test, S);
		}

		nSucesso = 0;

		for(int j=0;j<=P && nSucesso<=L;j++){
			double score_s = score(S);
			int peek = getneighborhood();

			S[peek] = !(S[peek]);

			double score_si = score(S);

			double delta = score_s - score_si;

			// energia negativa -> melhor solucao
			if(delta <= 0.0 || exp(-delta/T) > uniform_real_distribution<double>(0, 1.0)(rng)){
				nSucesso++;
			}
			else{
				S[peek] = !(S[peek]);
			}
		}
		T = T*alpha;
	}

	Woutput(M/log_size, test, S);
}

int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Rinput();
	sAnnealing();
}
