#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

class Generator
{
public:

	long long int factoriel     (int n);
	double        pk            (double lambda, int k);
	double        random_uniform();
	double maxDistanceFromDepot(vector<vector<double>> customer_coors);
	template <typename T> string array_to_string(vector<T> V);
	void function (vector<double> lambdas, string inputfile, string outputfile);
	void generate(
			vector       <int>     customers_id  ,
			vector       <double>  lambdas       , 
			vector<vector<double>> customer_coors, 
			int                    T             , 
			string                 filename
		);
};