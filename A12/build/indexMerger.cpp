#include <fstream>
#include <iostream>
#include <mpi.h>
#include <cmath>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <vector>

int main(int argc, char * argv[]){
	MPI_Init(&argc,&argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	ios::sync_with_stdio(false);//For faster IO

	cout << "Index Merger Started for Rank " << rank << endl;
	
	int steps = ceil(log2(size)); 
	int gap = 1;
	bool jobdone = false;
	for(int step_i=0; step_i<steps; ++step_i){
		int divisor = gap*2;
		if (rank%divisor == 0 && !jobdone){
			if (rank + gap < size){
				rename("index", "index.old");
				ifstream oldindex("index.old");
				unordered_map<string, vector<tuple<int, int, int>>> index;
				string indexline;
				while(getline(oldindex, indexline)){
					istringstream line(indexline);			
					string word;
					line >> word;
					index[token] = vector<tuple<int, int, int>>();
					int freq, doc;
					while(line){
						line >> freq >> doc;
						if (!line) break;
						index[token].push_back(make_tuple(freq, rank, doc));
					}
					
				}
		




			}	
		}else if(!jobdone){
			ifstream index("index");
			string indexstr((istreambuf_iterator<char>(index)), istreambuf_iterator<char>());	
			MPI_Send(indexstr.c_str(), indexstr.size(), MPI_CHAR, rank - gap, 0, MPI_COMM_WORLD);
			jobdone = true;
		}

		MPI_Barrier(MPI_COMM_WORLD);//Synchronizing point
		gap *= 2;
	}

	cout << "Index Merger Finished for Rank " << rank << endl; 

	MPI_Finalize();
	return 0;
}
