#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> ii;
 
const int MAXV = 10000;
const int INF = 1e9;
 
const int dr[4] = { 0, 1, 0, -1 };
const int dc[4] = { 1, 0, -1, 0 };
 
int R, C, S;
vector<int> length;
vector<vector<bool>> isWormhole;
vector<pair<int, int>> wormholes;
vector<vector<int>> grid;
vector<vector<bool>> occupied;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
void read_input(){
    cin >> C >> R >> S;

    length.resize(S);
    for(int i = 0; i < S; i++)
        cin >> length[i];

    grid.assign(R, vector<int>(C));
    isWormhole.assign(R, vector<bool>(C, false));
    occupied.assign(R, vector<bool>(C, false));

    for(int i = 0; i < R; i++){
        for (int j = 0; j < C; j++) {
            string number; cin >> number;
            if (number != "*") grid[i][j] = stoi(number);
            else grid[i][j] = 0, isWormhole[i][j] = true, wormholes.emplace_back(i, j);
        }
    }
}
 
ll score(vector<ii> &snake){
    ll ret = 0;
 
    for(int i=0;i< (int) snake.size();i++){
        int x = snake[i].first;
        int y = snake[i].second;
 
        ret += ll(grid[x][y]);
    }
 
    return ret;
}
 
ii get_new_random_pos() {
    int row = uniform_int_distribution<int>(0, R - 1)(rng);
    int col = uniform_int_distribution<int>(0, C - 1)(rng);
    return make_pair(row, col);
}
 
bool valid(ii pos) {
    return !occupied[pos.first][pos.second];
}
 
ii get_new_random_wormhole() {
    int size = wormholes.size();
    
    return wormholes[uniform_int_distribution<int>(0, size - 1)(rng)];
}
 
void clear_path(vector<ii> &positions) {
  for(auto auto_p: positions){
    int row = auto_p.first;
    int col = auto_p.second;
    occupied[row][col] = false;
  }
}
 
vector<ii> get_new_random_path(int id) {
    const int max_attempts = 10;
    const double prob_choose = 1.0;
 
    if (uniform_real_distribution<double>(0, 1.0)(rng) > prob_choose)
        return vector<ii>();
 
    int attempts = 0;
    ii initial = get_new_random_pos();
 
    while ((!valid(initial) || isWormhole[initial.first][initial.second]) && attempts < max_attempts)
        initial = get_new_random_pos(), attempts++;
 
    if (!valid(initial) || isWormhole[initial.first][initial.second])
        return vector<ii>();
 
    ii curr = initial;
    vector<ii> positions(1, initial);
    occupied[curr.first][curr.second] = true;
    bool entry = false;
 
    for (int i = 1; i < length[id]; i++) {
        if (isWormhole[curr.first][curr.second] && entry) {
            if ((int) wormholes.size() == 1) {
                clear_path(positions);
                return vector<ii>();
            }
 
            ii newPos;
            do newPos = get_new_random_wormhole();
            while (newPos == curr);
 
            positions.push_back(newPos);
            curr = newPos;
            entry = false;
        } else {
            ii newPos;
            int dir, chosen = 0;

            vector<int> dirs = {0, 1, 2, 3};
            //(dirs.begin(), dirs.end(), rng);

            for(auto dir: dirs){
              newPos = make_pair((curr.first + dr[dir] + R) % R, (curr.second + dc[dir] + C) % C);
              if(valid(newPos)) break;
            }
 
            /*do {
                dir = uniform_int_distribution<int>(0, 3)(rng);
                newPos = make_pair((curr.first + dr[dir] + R) % R, (curr.second + dc[dir] + C) % C);
                chosen |= (1 << dir);
            } while (!valid(newPos) && chosen != 15*/

            if (!valid(newPos)) {
                clear_path(positions);
                return vector<ii>();
            }
 
            if (isWormhole[newPos.first][newPos.second]) entry = true;
            else occupied[newPos.first][newPos.second] = true;
 
            positions.push_back(newPos);
            curr = newPos;
        }
    }
 
    if (isWormhole[curr.first][curr.second]) {
        clear_path(positions);
        return vector<ii>();
    }
 
    return positions;
}
 
vector<vector<ii>> get_initial_paths() {
    vector<vector<ii>> paths;
    paths.resize(S);
    return paths;

    vector<int> ids;
    for(int i=0;i<S;i++){
      ids.push_back(i);
    }

    shuffle(ids.begin(), ids.end(), rng);
    paths.resize(S);

    for (int i = 0; i < S; i++){
      auto s = get_new_random_path(ids[i]);
      paths[ids[i]] = s;
    }
 
    return paths;
}
 
void mark_snake_path(const vector<ii>& snake_path) {
    for(auto& auto_p : snake_path) {
        int x = auto_p.first;
        int y = auto_p.second;
        if(isWormhole[x][y]) continue;
        occupied[x][y] = true;
    }
}
 
ll solution_score(const vector<vector<ii>>& S) {
    ll ret = 0;
    for(auto snake_path : S) {
        ret += score(snake_path);
    }
    return ret;
}
 
void undo_snake_path(const vector<ii>& snake_path) {
    for(auto& auto_p : snake_path) {
      auto x = auto_p.first;
      auto y = auto_p.second;
        if(isWormhole[x][y]) continue;
        occupied[x][y] = false;
    }
}
pair<int, vector<ii>> get_neighborhood(const vector<vector<ii>>& snakes) {
    int S = (int)snakes.size();
    int id = uniform_int_distribution<int>(0, S - 1)(rng);
    undo_snake_path(snakes[id]);
    auto new_path = get_new_random_path(id);
    undo_snake_path(new_path);
    return make_pair(id, new_path);
}
 
map<pair<int, int>, char> direction;
 
void init_directions() {
  direction[{1, 0}] = 'D';
  direction[{0, 1}] = 'R';
  direction[{R - 1, 0}] = 'U';
  direction[{0, C - 1}] = 'L';
}
 
void print_solution(const vector<vector<ii>>& S) {
    cout << "#####################\n";
    for(const auto& snake_path : S) {
        if(snake_path.empty()) {
            cout << '\n';
            continue;
        }
        cout << snake_path[0].second << ' ' << snake_path[0].first << ' ';
        int len = (int)snake_path.size();
        bool entry = false;

        for(int i = 1; i < len; ++i) {
            int dx = (snake_path[i].first - snake_path[i - 1].first + R) % R;
            int dy = (snake_path[i].second - snake_path[i - 1].second + C) % C;

            if (isWormhole[snake_path[i].first][snake_path[i].second] && !entry) {
                if (isWormhole[snake_path[i - 1].first][snake_path[i - 1].second]) {
                    entry = true;
                    cout << snake_path[i].second << " " << snake_path[i].first << " ";
                    continue;
                }
            }

            cout << direction[{dx, dy}] << ' ';
            entry = false;
        }
        cout << '\n';
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
    double TEMP_INICIAL = 1000000.0;
    double alpha = 0.995;
    int M = 50000;
    int P = 10000;
    int print_per_iterations = M / 100;
    double barreira = 1e-5;
 
    vector<vector<ii>> S = get_initial_paths();
    ll total_score = solution_score(S);
    double T0 = TEMP_INICIAL;
    double T = T0;

    ll last = 1;
    int stoped = 0;
 
    for(int i=0;i<=M;i++){
        int failed_state = 0;
        int negatives_deltas = 0;
        int negative_paths = 0;
        int null_paths = 0;

        for(int j=0;j<=P;j++){
            auto auto_p = get_neighborhood(S);
            auto snake_id = auto_p.first;
            auto new_path = auto_p.second;

            ll score_new_path = score(new_path);
            if(score_new_path < 0){
              score_new_path = 0;
              new_path.clear();
            }
 
            ll delta = score(S[snake_id]) - score_new_path;

            if(score_new_path < 0) negative_paths++;
            if(new_path.size() == 0) null_paths++;

            if(delta > 0) negatives_deltas++;
 
            // energia negativa -> melhor solucao
            if(delta <= 0.0 || exp(-delta/T) > uniform_real_distribution<double>(0, 1.0)(rng)){
                mark_snake_path(new_path);
                S[snake_id].swap(new_path);
                total_score -= delta;
                if(delta > 0) failed_state++;
            } else {
                mark_snake_path(S[snake_id]);
            }
        }
        T = T*alpha;
        if (T < barreira) {
            print_solution(S);
            break;
        }
 
        cerr << "----------------------------------------------------" << '\n';
        cerr << "total_score: " << total_score << '\n';
        cerr << "temperatura: " << T << '\n';
        cerr << "iteracoes: " << i << "/" << M << "\n";
        if(negatives_deltas == 0) negatives_deltas++;
        cerr << "max_local factor: " << (double)failed_state/negatives_deltas << '\n';

        double aux = (double) negative_paths / (P+1);
        cerr << "negative_paths = " << aux << '\n';
        aux = (double) null_paths / (P+1);
        cerr << "null_paths = " << aux << '\n';

        if(last == total_score){
          stoped++;
        }
        else{
          stoped = 0;
        }

        if(stoped >= 25) break;

        double perc = (double) total_score / last - 1.0;
        perc *= 100;
        cerr << "crescimento = " << perc << "%\n";
        last = total_score;
 
        if (i % print_per_iterations == 0){
            print_solution(S);
        }
    }
    print_solution(S);
}
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    read_input();
    init_directions();
    sAnnealing();
}
