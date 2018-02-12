#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char * argv[]){
	srand(static_cast <unsigned int> (time(0)));//Initialize Pseudo-Random Seed

	ios::sync_with_stdio(false);//For faster IO

	MPI_Init(&argc,&argv);

	const int wlslen = 69903; //Known Wordlist Length
	const int stlslen = 174; //Known Stopword List Length
	
	const int docwlen = 10000; //Desired Document Word Length
        const int docn = 10; //Desired Number of Documents

	printf("Wordlist Length: %d Stopword List Length: %d\n",wlslen, stlslen);
	//char* wlist[] = (char**)calloc(wlistlength, sizeof(char*));
	
	string wlist[wlslen];	
	string stls[stlslen];

	ifstream wfile("wordlist");

	string s;
	int i = 0;
	while (wfile >> s){
		wlist[i] = s;
		++i;
	}

	ifstream sfile("stopwords");

	i = 0;
	while (sfile >> s){
		stls[i] = s;	++i;
	}

	ofstream out;

	for(int cur_doc=0; cur_doc < docn; ++cur_doc){
		out.open("doc-"+to_string(cur_doc));
		for(int w_i=0; w_i<docwlen; ++w_i){
			int w_index = rand() % wlslen;
			out << wlist[w_index] << " ";
		}
		out << endl;
		out.close();
	}


	MPI_Finalize();
	return 0;
}
