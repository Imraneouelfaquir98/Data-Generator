#include "generator.h"

long long int X = 765502822;

Generator::Generator(){
	this->time_window_type = "d1";
}

Generator::Generator(string time_window_type){
	this->time_window_type = time_window_type;
}


long long int Generator::factoriel(int n){
	if(n  < 0) throw runtime_error("Error: n must be n >=0");
	if(n <= 1) return 1;
	else       return n * factoriel(n-1);
}

double Generator::pk(double lambda, int k){
	return exp(-lambda)*pow(lambda, k)/factoriel(k);
}

void Generator::fit(
		vector       <int>     customers_id  ,
		vector       <double>  lambdas       , 
		vector<vector<double>> customer_coors, 
		int                    T             , 
		string                 filename
	){
	fstream data (filename, ios::out | ios::trunc);
	if(!data.is_open()) throw runtime_error("Error: Could not create \""+filename+"\", try later.");
	else{
		data<<"Max_Dist_From_Depot\tTime window type\n";
		data<<to_string(maxDistanceFromDepot(customer_coors)) + "\t\t\t" + time_window_type;
		vector<int> X = {0, (int)customer_coors[0][0], (int)customer_coors[0][1], 0, 0, -1};
		data<<"\nId\tX_Coor\tY_Coor\ttw_start\ttw_end\tArr\n";
		data<<array_to_string(X);

		int req = 1, tw_start, tw_end;
		for(int t=0; t<T; t++){
			for(int customer=1; customer<=(int)lambdas.size(); customer++){
				if(random_uniform() < pk(lambdas[customer-1], 1)){
					setTimeWindow(&tw_start, &tw_end, t);
					X = {
						customer,
						(int)customer_coors[customer][0], 
						(int)customer_coors[customer][1],
						tw_start,
						tw_end,
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

void Generator::setTimeWindow(int * tw_start, int * tw_end, int time_request){
	if(time_window_type == "d2"){
		*tw_start	=	 time_request;
		*tw_end		=	*tw_start + 2*60;
	}else if (time_window_type == "f"){	
		*tw_start	=	 time_request + 60;
		*tw_end		=	*tw_start + 60;
	}else if (time_window_type == "r" ){
		int min 	=	 480 - time_request;
		int max 	=	 480;
		*tw_start 	=	 random_uniform()*(max - min) + min;
		*tw_end		=	*tw_start + 60;
	}else if (time_window_type == "h" ){
		int min 	=	 (time_request + (60 - time_request%60))/60;
		int max 	=	 (time_request - 60*min)/60 + min + 1;
		double u 	=	 random_uniform() * (double)(max - min) + (double)min;
		*tw_start	=	 ((u-(int)u > 0.5)? (int)u + 1 : (int)u) * 60;
		if(*tw_start > 480){
			*tw_start = 480;
		}
		*tw_end		=	*tw_start + 60;
	}else{
		*tw_start	= 	 time_request;
		*tw_end		= 	*tw_start + 60;
	}
}

void Generator::generate(vector<double> lambdas, string inputfile, string outputfile){
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

    fit(
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
	X = (65539*X)%2147483648;
	return (double)X/2147483648;
}

template <typename T> string Generator::array_to_string(vector<T> V){
	string str = "";
	for(int i=0; i<(int)V.size(); i++){
		str += to_string(V[i]) + "\t\t";
	}
	return str + "\n";
}