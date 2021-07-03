#include "generator.h"

long long int Generator::factoriel(int n){
	if(n  < 0) throw runtime_error("Error: n must be n >=0");
	if(n <= 1) return 1;
	else       return n * factoriel(n-1);
}

double Generator::pk(double lambda, int k){
	return exp(-lambda)*pow(lambda, k)/factoriel(k);
}

void Generator::generate(
		vector       <int>     customers_id  ,
		vector       <double>  lambdas       , 
		vector<vector<double>> customer_coors, 
		int                    T             , 
		string                 filename
	){
	fstream data (filename, ios::out | ios::trunc);
	if(!data.is_open()) throw runtime_error("Error: Could not create \""+filename+"\", try later.");
	else{
		data<<"Max Distance From Depot\n";
		data<<maxDistanceFromDepot(customer_coors);
		vector<int> X = {0, (int)customer_coors[0][0], (int)customer_coors[0][1],-1};
		data<<"\nReq\tX_Coor\tY_Coor\tArr\n";
		data<<array_to_string(X);
		int req = 1;
		for(int t=0; t<T; t++){
			for(int customer=1; customer<=(int)lambdas.size(); customer++){
				if(random_uniform() < pk(lambdas[customer-1], 1)){
					X = {
						req,
						(int)customer_coors[customer][0], 
						(int)customer_coors[customer][1], 
						t
					};
					data<<array_to_string(X);
					req++;
				}
			}
		}
		data.close();
	}
}

void Generator::function(vector<double> lambdas, string inputfile, string outputfile){
	ifstream myFile(inputfile);

    if(!myFile.is_open())
        throw runtime_error("Error: Could not open \""+inputfile+"\" file.");

    string line;
    stringstream ss;

	vector<int>            customers_id;
	vector<vector<double>> customers_coors;

    if(myFile.good())
    {

        for(int i=0; i<9; i++) getline(myFile, line);

        vector<double> coor (2, 0);
    	int            id;

        while(getline(myFile, line))
        {
            ss = stringstream(line);
			ss>>id;
			ss>>coor[0];
			ss>>coor[1];
			customers_coors.push_back(coor);
			customers_id   .push_back(id);
        }
    }   
    myFile.close();

    generate(
		customers_id  ,
		lambdas       , 
		customers_coors, 
		480           , 
		outputfile
	);
}

double Generator::maxDistanceFromDepot(vector<vector<double>> customer_coors){
	double max = 0, current_distance;
	for(int i=1; i<(int)customer_coors.size(); i++){
		current_distance = abs(customer_coors[0][0] - customer_coors[i][0]) 
						 + abs(customer_coors[0][1] - customer_coors[i][1]);
		if(max < current_distance) max = current_distance;
	}
	return max;
}


double Generator::random_uniform(){

    fstream Generator(".x0", ios::in);

    if(!Generator.is_open()){
    	fstream x_0(".x0", ios::out);
    	x_0<<to_string(765502822);
    	x_0.close();
    	Generator.open(".x0", ios::in);
    }
    long long int x0;
	Generator>>x0;
	x0 = (x0 > 0)?x0:765502822;
	Generator.close();
	Generator.open(".x0", ios::out | ios::trunc);
	Generator<<to_string((65539*x0)%2147483648);
	Generator.close();
	return (double)x0/2147483648;

}

template <typename T> string Generator::array_to_string(vector<T> V){
	string str = "";
	for(int i=0; i<(int)V.size(); i++){
		str += to_string(V[i]) + "\t";
	}
	return str + "\n";
}