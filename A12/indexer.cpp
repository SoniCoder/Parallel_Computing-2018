#include <fstream>
#include <iostream>
#include <mpi.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char * argv[]){
	MPI_Init(&argc,&argv);
	
	ios::sync_with_stdio(false);//For faster IO

	const int docwlen = 10000; //Desired Document Word Length
        const int docn = 10; //Desired Number of Documents

	unordered_map<string, vector<pair<int, int>>> index;

	for (int doc_i=0; doc_i<docn; ++doc_i){
		ifstream document("doc-"+to_string(doc_i));
		string s;
		while(document >> s){
			unordered_map<string, vector<pair<int, int>>>::const_iterator got = index.find(s);
			if (got == index.end()){
				index[s] = vector<pair<int, int>>(docn, make_pair(doc_i, 0));
				index[s][doc_i].second = 1;
			}
			else ++index[s][doc_i].second;
		}
		document.close();
	}

	printf("%d", index.size());

	
	MPI_Finalize();
	return 0;
}
