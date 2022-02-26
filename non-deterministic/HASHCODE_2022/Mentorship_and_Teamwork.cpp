#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef pair<int,int> ii;
typedef pair<int, vector<int>> iv;

int C, P;

vector<string> id_name;
vector<string> id_project;

map<string, int> skill_id;
vector<string> id_skill;

vector<vector<ii>> skills;
vector<vector<ii>> roles;

vector<int> pj_duration;
vector<int> pj_score;
vector<int> pj_deadline;

void readInput(){

	cin >> C >> P;

	for(int i=0;i<C;i++){
		string name;
		cin >> name;

		id_name.push_back(name);

		int n;
		cin >> n;

		vector<ii> skill_contrib;

		for(int j=0;j<n;j++){
			string skill_name;
			cin >> skill_name;
			int l;
			cin >> l;

			if(skill_id.count(skill_name) == 0){
				skill_id[skill_name] = id_skill.size();
				id_skill.push_back(skill_name);
			}

			int id = skill_id[skill_name];

			skill_contrib.push_back({id, l});
		}

		skills.push_back(skill_contrib);
	}

	for(int i=0;i<P;i++){
		string name;
		cin >> name;

		id_project.push_back(name);

		int d;
		cin >> d;
		pj_duration.push_back(d);

		int s;
		cin >> s;
		pj_score.push_back(s);

		int bbefore;
		cin >> bbefore;
		pj_deadline.push_back(bbefore);

		int r;
		cin >> r;

		vector<ii> roles_pj;

		for(int j=0;j<r;j++){
			string name;
			cin >> name;

			int l;
			cin >> l;

			if(skill_id.count(name) == 0){
				skill_id[name] = id_skill.size();
				id_skill.push_back(name);
			}

			int id = skill_id[name];

			roles_pj.push_back({id, l});
		}

		roles.push_back(roles_pj);
	}
}

vector<iv> naive(){

	vector<iv> ret;

	for(int i=0;i<P;i++){
		cerr << "naive -> " << P-1-i << endl;
		vector<int> assignes;

		set<int> all;

		for(int j=0;j<roles[i].size();j++){
			int id = uniform_int_distribution<int>(0, C-1)(rng);

			if(all.find(id) != all.end()){
				j--;
				continue;
			}
			all.insert(id);
			assignes.push_back(id);
		}

		ret.push_back({i, assignes});
	}

	shuffle(ret.begin(), ret.end(), rng);

	return ret;
}

bool change_project;
int p_id;
int c_pos;
int old_id;
int p_id1;
int p_id2;

void reverseState(vector<iv> &S){

	if(change_project == false){
		S[p_id].second[c_pos] = old_id;
	}
	else{
		swap(S[p_id1], S[p_id2]);
	}
}

void getneighborhood(vector<iv> &S){

	double choice = uniform_real_distribution<double>(0, 1.0)(rng);
	double rate = 0.5;

	if(choice < rate){
		change_project = false;
		p_id = uniform_int_distribution<int>(0, P-1)(rng);

		c_pos = uniform_int_distribution<int>(0, (int)S[p_id].second.size() - 1)(rng);
		old_id = S[p_id].second[c_pos];
		int nw_id = uniform_int_distribution<int>(0, C-1)(rng);

		S[p_id].second[c_pos] = nw_id;
	}
	else{
		change_project = true;
		p_id1 = uniform_int_distribution<int>(0, P-1)(rng);
		p_id2 = uniform_int_distribution<int>(0, P-1)(rng);

		swap(S[p_id1], S[p_id2]);
	}
}

long long score(vector<iv> &S){

	long long ret = 0;
	map<ii, int> add;
	map<int, int> freeDay;

	for(iv &project: S){
		int pid = project.first;

		map<int,int> team;

		bool canDo = true;

		vector<ii> needHelp;
		vector<ii> improveSkill;

		int start_at = 0;

		for(int i=0;i<project.second.size();i++){
			int id = project.second[i];
			start_at = max(start_at, freeDay[id]);

			int myl = 0;
			int curr_sk = roles[pid][i].first;
			int curr_l = roles[pid][i].second;
			
			for(int j=0;j<skills[id].size();j++){
				int sk = skills[id][j].first; 
				int l = skills[id][j].second + add[{id, sk}];

				team[sk] = max(team[sk], l);

				if(sk == curr_sk) myl = max(myl, l);
			}

			if(myl < curr_l - 1){
				canDo = false;
				break;
			}

			if(myl == curr_l) improveSkill.push_back({id, curr_sk});
			if(myl == curr_l-1){
				improveSkill.push_back({id, curr_sk});
				needHelp.push_back({curr_sk, curr_l});
			}
		}

		if(!canDo) continue;

		for(ii &par: needHelp){
			if(team[par.first] < par.second){
				canDo = false;
				break;
			}
		}

		if(!canDo) continue;

		for(ii &par: improveSkill){
			add[{par.first, par.second}]++;
		}

		int end_at = start_at + pj_duration[pid] - 1;

		for(int i=0;i<project.second.size();i++){
			int id = project.second[i];
			freeDay[id] = end_at + 1;
		}

		ret += (end_at <= pj_deadline[pid] ? pj_score[pid] : max(0, pj_score[pid] - (end_at + 1 - pj_deadline[pid])));
	}

	return ret;
}

void printSolution(vector<iv> &S){

	map<ii, int> add;
	map<int, int> freeDay;

	int total = 0;

	for(iv &project: S){
		int pid = project.first;

		map<int,int> team;

		bool canDo = true;

		vector<ii> needHelp;
		vector<ii> improveSkill;

		int start_at = 0;

		for(int i=0;i<project.second.size();i++){
			int id = project.second[i];
			start_at = max(start_at, freeDay[id]);

			int myl = 0;
			int curr_sk = roles[pid][i].first;
			int curr_l = roles[pid][i].second;
			
			for(int j=0;j<skills[id].size();j++){
				int sk = skills[id][j].first; 
				int l = skills[id][j].second + add[{id, sk}];

				team[sk] = max(team[sk], l);

				if(sk == curr_sk) myl = max(myl, l);
			}

			if(myl < curr_l - 1){
				canDo = false;
				break;
			}

			if(myl == curr_l) improveSkill.push_back({id, curr_sk});
			if(myl == curr_l-1){
				improveSkill.push_back({id, curr_sk});
				needHelp.push_back({curr_sk, curr_l});
			}
		}

		if(!canDo) continue;

		for(ii &par: needHelp){
			if(team[par.first] < par.second){
				canDo = false;
				break;
			}
		}

		if(!canDo) continue;

		for(ii &par: improveSkill){
			add[{par.first, par.second}]++;
		}

		int end_at = start_at + pj_duration[pid] - 1;

		for(int i=0;i<project.second.size();i++){
			int id = project.second[i];
			freeDay[id] = end_at + 1;
		}

		total++;
	}

	// print total
	cout << total << endl;

	add.clear();
	freeDay.clear();

	for(iv &project: S){
		int pid = project.first;

		map<int,int> team;

		bool canDo = true;

		vector<ii> needHelp;
		vector<ii> improveSkill;

		int start_at = 0;

		for(int i=0;i<project.second.size();i++){
			int id = project.second[i];
			start_at = max(start_at, freeDay[id]);

			int myl = 0;
			int curr_sk = roles[pid][i].first;
			int curr_l = roles[pid][i].second;
			
			for(int j=0;j<skills[id].size();j++){
				int sk = skills[id][j].first; 
				int l = skills[id][j].second + add[{id, sk}];

				team[sk] = max(team[sk], l);

				if(sk == curr_sk) myl = max(myl, l);
			}

			if(myl < curr_l - 1){
				canDo = false;
				break;
			}

			if(myl == curr_l) improveSkill.push_back({id, curr_sk});
			if(myl == curr_l-1){
				improveSkill.push_back({id, curr_sk});
				needHelp.push_back({curr_sk, curr_l});
			}
		}

		if(!canDo) continue;

		for(ii &par: needHelp){
			if(team[par.first] < par.second){
				canDo = false;
				break;
			}
		}

		if(!canDo) continue;

		for(ii &par: improveSkill){
			add[{par.first, par.second}]++;
		}

		int end_at = start_at + pj_duration[pid] - 1;

		for(int i=0;i<project.second.size();i++){
			int id = project.second[i];
			freeDay[id] = end_at + 1;
		}

		// print project
		cout << id_project[pid] << endl;
		for(int &id: project.second){
			cout << id_name[id] << " ";
		}
		cout << endl;
	}
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

	vector<iv> S0 = naive();
	int M = 10000;
	int P = 1000;
	int L = 100;
	double alpha = 0.995;

	vector<iv> S = S0;
	double T0 = 100000.0;
	double T = T0;

	int nSucesso = 1;

	long long score_s = score(S);

	for(int i=0;i<=M && nSucesso > 0;i++){
		nSucesso = 0;

		cerr << "iter: " << i << "/" << M << endl;
		cerr << "temp: " << T << endl;
		cerr << "score: " << score_s << endl;
		cerr << "-------------------------" << endl;

		for(int j=0;j<=P && nSucesso<=L;j++){
			getneighborhood(S);
			long long score_si = score(S);
			long long delta = score_s - score_si;

			// energia negativa -> melhor solucao
			if(delta <= 0.0 || exp(-delta/T) > uniform_real_distribution<double>(0, 1.0)(rng)){
				score_s = score_si;
				nSucesso++;
			}
			else{
				reverseState(S);
			}
		}
		T = T*alpha;
	}

	cerr << "Final Score: " << score_s << endl;
	printSolution(S);
}

int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cerr << "reading input..." << endl;
	readInput();
	cerr << "call sAnnealing..." << endl;
	sAnnealing();
}
