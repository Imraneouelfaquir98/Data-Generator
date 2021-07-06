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

	string time_window_type;

	long long int 	factoriel     (int n);
	double        	pk            (double lambda, int k);
	double        	random_uniform();
	double 			maxDistanceFromDepot(vector<vector<double>> customer_coors);
	void 			setTimeWindow(int * tw_start, int * tw_end, int time_request);
	void 			generate (vector<double> lambdas, string inputfile, string outputfile);
	int				timeWindowIndex();
	template <typename T> string array_to_string(vector<T> V);
	void fit (
			vector       <int>     customers_id  ,
			vector       <double>  lambdas       , 
			vector<vector<double>> customer_coors, 
			int                    T             , 
			string                 filename
		);
	Generator();
	Generator(string time_window_type);
};