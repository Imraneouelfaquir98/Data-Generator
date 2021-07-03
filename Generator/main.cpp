#include <iostream>
#include <dirent.h>
#include "generator.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Generator generator = Generator();

	DIR *dir; struct dirent *diread;
    vector<string> files;

    if((dir = opendir("./solomon-100")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) files.push_back(diread->d_name);
        closedir (dir);
    }
    else {
        perror ("opendir");
        return EXIT_FAILURE;
    }

    for (int i=0; i<(int)files.size(); i++){
        if(files[i].length() > 4 and files[i].substr(files[i].length()-4, 4) == ".txt"){
            generator.function(
                    vector<double>(100, 0.002), 
                    "./solomon-100/"+files[i], 
                    "./imrane/data_" + to_string(i+1) + ".txt"
                );
            cout<<i+1<<endl;;
        }
    }
	return 0;
}