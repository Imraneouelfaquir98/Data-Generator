#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;
long long int factoriel     (int n);
double        pk            (double lambda, int k);
double        random_uniform();

void generator(
		vector       <double>  lambdas       , 
		vector<vector<double>> customer_coors, 
		int                    T             , 
		string                 filename
	);

template <typename T> void   print(vector<vector<T>> X);
template <typename T> string array_to_string(vector<T> V);

int main(int argc, char const *argv[])
{
	vector<vector<double>> customer_coors = {
		{88 , 90},
		{83 , 55},
		{10 , 26},
		{80 , 47},
		{10 , 55},
		{82 , 53},
		{80 , 50},
		{40 , 40},
		{80 , 47},
		{83 , 56},
	};
	vector<double> lambdas = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02};
	generator(lambdas, customer_coors, 480, "data.txt");
	return 0;
}

long long int factoriel(int n){
	if(n  < 0) throw runtime_error("Error: n must be n >=0");
	if(n <= 1) return 1;
	else       return n * factoriel(n-1);
}

double pk(double lambda, int k){
	return exp(-lambda)*pow(lambda, k)/factoriel(k);
}

void generator(
		vector       <double>  lambdas       , 
		vector<vector<double>> customer_coors, 
		int                    T             , 
		string                 filename
	){
	fstream data (filename, ios::out | ios::trunc);
	if(!data.is_open()) throw runtime_error("Error: Could not create \""+filename+"\", try later.");
	else{
		vector<int> X = {0, 70, 70,-1};
		data<<"Req\tX_Coor\tY_Coor\tArr\n";
		data<<array_to_string(X);
		int req = 1;
		for(int t=0; t<T; t++){
			for(int customer=0; customer<(int)lambdas.size(); customer++){
				if(random_uniform() < pk(lambdas[customer], 1)){
					X = {req, (int)customer_coors[customer][0], (int)customer_coors[customer][1], t};
					data<<array_to_string(X);
					req++;
				}
			}
		}
		data.close();
	}
}

double random_uniform(){

    fstream generator(".x0", ios::in);

    if(!generator.is_open()){
    	fstream x_0(".x0", ios::out);
    	x_0<<to_string(765502822);
    	x_0.close();
    	generator.open(".x0", ios::in);
    }
    long long int x0;
	generator>>x0;
	x0 = (x0 > 0)?x0:765502822;
	generator.close();
	generator.open(".x0", ios::out | ios::trunc);
	generator<<to_string((65539*x0)%2147483648);
	generator.close();
	return (double)x0/2147483648;

}

template <typename T> void print(vector<vector<T>> X){
    for(int i=0; i<X.size(); i++){
        for (int j = 0; j < X[i].size(); ++j)
            cout<<"\t"<<X[i][j];
        cout<<endl;
    }
}

template <typename T> string array_to_string(vector<T> V){
	string str = "";
	for(int i=0; i<(int)V.size(); i++){
		str += to_string(V[i]) + "\t";
	}
	return str + "\n";
}