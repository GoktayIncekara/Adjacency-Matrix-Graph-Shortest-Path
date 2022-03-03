#include "graph.hpp"

#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

//Fills in a V x V matrix with zeros.
GraphAdjMat::GraphAdjMat(int V)
	: m_V(V),
          m_E(0)
{
	adjMatrix = std::vector<std::vector<int>> (V, vector<int>(V,0));
}


void GraphAdjMat::print() const
{

	cout<<  setw(4) << " " ;
	for (int row = 0; row <V(); ++row){
		cout << setw(3) << row << "|";
	}
	cout<< endl;

	for (int col = 0; col < V(); col++){
		cout << setw(3) << col << "|";
		for (int i = 0; i < V(); ++i) {
			cout<< setw(2) << adjMatrix[col][i]<< "  ";
		}
		cout<< endl;
	}
	
}


//changes the element indexes of an adjacency matrix from 0 to 1 for both combinations.	 
void GraphAdjMat::insert(int v, int w)
{
	 if (v >= V() || w >= V() || v < 0 || w < 0) {
                cerr << "Error: vertex indices for insertion must be in the 		range [0, " << (V()-1) << "]!" << endl;
                return;
        }

        if (v == w) {
                cerr << "Error: skipping self loop insertion!" << endl;
                return;
        }
        adjMatrix[v][w] = 1;
	adjMatrix[w][v] = 1;
	m_E++;
}


int GraphAdjMat::connected_components(std::vector<int> &ids)
{
        ids.resize(V());
        if (V() == 0)
                return 0;

        vector<bool> marked(V(), false);
        int cc_id = 0;
	queue<int> bfs_queue;
	
	for (int i = 0; i < V(); ++i) {
                if (!marked[i]) {
                        bfs_queue.push(i);
                        while (!bfs_queue.empty()) {
                                int n = bfs_queue.front();
                                bfs_queue.pop();
                                ids[n] = cc_id;
				//gets the adjacent vertices list with the 					help of the getAdjacentVertices method. 				Then, iterates the elements of the list just 					like graphadjlist did.
				list<int> adjVertices= 			                getAdjacentVertices(n);
				if (!adjVertices.empty())
				{
					list<int>::iterator it;
					for (it=adjVertices.begin(); 
						it !=adjVertices.end(); it++)
					{
						if (!marked[*it])
						{
							marked[*it] = true;
					        	bfs_queue.push(*it);
						}
					}
				}
			}
                        cc_id++;
                }
        }
        return cc_id;
}

//returns a list, which has vertices adjacent to n inside it.
//returns empty list if n is not between 0 and vertice number. 
list<int> GraphAdjMat::getAdjacentVertices(int n)
{
	list<int> adjVertices;
	if(n < 0 || n >= V())
		return adjVertices;
	
	for ( int i = 0; i < V(); ++i){
		if(adjMatrix[n][i] != 0)
			adjVertices.push_front(i);
	}
	return adjVertices;
}



int GraphAdjMat::shortest_path(int src, int dst, std::stack<int>& path)
{
        queue<int> bfs_queue;
        vector<bool> marked(V(), false);
        vector<int> edge_to(V(), -1);

        marked[src] = true;
        bfs_queue.push(src);

        while (!bfs_queue.empty()) {
                int n = bfs_queue.front();
                bfs_queue.pop();

		//gets the adjacent vertices list with the help of 			the getAdjacentVertices method. Then, iterates 			the elements of the list just like graphadjlist did. 
		list<int> adjVertices= getAdjacentVertices(n);
		if (!adjVertices.empty())
		{
			list<int>::iterator it;
			for (it = adjVertices.begin(); 
					it != adjVertices.end(); it++)
			{
				if (!marked[*it])
				{
					edge_to[*it] = n;
					marked[*it] = true;
					bfs_queue.push(*it);
				}
			}
		}
        }
	
        while (!path.empty())
                path.pop();


        if (!marked[dst])
                return -1;

        for (int n = dst; n != src; n = edge_to[n])
                path.push(n);
        path.push(src);

        return path.size();
}

