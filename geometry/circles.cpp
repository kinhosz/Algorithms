#include <bits/stdc++.h>
using namespace std;
const double PREC = 0.000001;

struct Circle{

	double x;
	double y;
	double r;
};

struct Line{
	double m;
	double b;
};

vector<pair<double,double>> LineCircle(Line L,Circle C){

	vector<pair<double,double>> lista;

	double a = L.m*L.m + 1.0;
	double b = 2.0*(L.m*L.b - L.m*C.y - C.x);
	double c = (L.b*L.b - 2.0*L.b*C.y + C.y*C.y + C.x*C.x - C.r*C.r);

	double delta = b*b - 4.0*a*c;
	if(delta < 0.0) return lista; // nao ha interseccao;

	double x = (-b + sqrt(delta))/(2.0*a);
	double y = L.m * x + L.b;
	lista.push_back(make_pair(x,y));
	x = (-b - sqrt(delta))/(2.0*a);
	y = L.m * x + L.b;
	lista.push_back(make_pair(x,y));

	return lista;
}

vector<pair<double,double>> intersect(Circle A, Circle B){

	vector<pair<double,double>> lista;
	
	B.x -= A.x;
	B.y -= A.y;

	double dist = sqrt(B.x*B.x + B.y*B.y);
	if(A.r + B.r < dist) return lista; // nao ha interseccao

	double resto = dist - B.r;
	resto += (A.r - resto)/2.0;

	double x = resto*B.y/dist;
	double y = resto*B.x/dist;
	double m;

	if(abs(x - B.y) < PREC) m = (y+B.x)/PREC;
	else m = (y+B.x)/(x - B.y);
	
	Line aux;
	aux.m = m;
	aux.b = -m*x + y;
	lista = LineCircle(aux,B);

	for(int i=0;i<lista.size();i++){
		lista[i].first += A.x;
		lista[i].second += A.y;
	}

	return lista;
}


int main(){

	Circle A;
	Circle B;

	cin >> A.x >> A.y >> A.r;
	cin >> B.x >> B.y >> B.r;

	vector<pair<double,double>> ret = intersect(A,B);

	if(ret.size() == 0) cout << "nao existe" << endl;
	else{
		for(int i=0;i<ret.size();i++){
			cout << "(" << ret[i].first << ", " << ret[i].second << ")" << endl;
			double r1,r2;
			r1 = sqrt((ret[i].first - A.x)*(ret[i].first - A.x) + (ret[i].second - A.y)*(ret[i].second - A.y));
			r2 = sqrt((ret[i].first - B.x)*(ret[i].first - B.x) + (ret[i].second - B.y)*(ret[i].second - B.y));
			cout << r1 << " " << r2 << endl;
		}

	}

}
