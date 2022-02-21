mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void sAnnealing(){
	// pseudo-code
	/************* setar isso aqui inicialmente

	S0 = estado inicial
	M = numero maximo de iteracoes
	P = pertubacoes por iteracao
	L = numero maximo de sucessos por iteracoes
	alpha = fator de reducao da temperatura

	******************************************/

	auto S = S0;
	double T0 = tempInicial();
	double T = T0;

	int nSucesso = 1;

	for(int i=0;i<=M && nSucesso > 0;i++){
		nSucesso = 0;

		for(int j=0;j<=P && nSucesso<=L;j++){
			auto Si = getneighborhood(S);
			double delta = score(Si) - score(S);

			// energia negativa -> melhor solucao
			if(delta <= 0.0 || exp(-delta/T) > uniform_real_distribution<double>(0, 1.0)(rng)){
				S = Si;
				nSucesso++;
			}
		}
		T = T*alpha;
	}
}
