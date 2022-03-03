#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stack>
#include <list>

class GraphAdjMat {
public:
       GraphAdjMat(int V);

        int V() const { return m_V; }
        int E() const { return m_E; }
        void print() const;
	void insert(int v, int w);
	int connected_components(std::vector<int> &ids);
	//returns the list of the nth elements' adjacent vertices 
	std::list<int> getAdjacentVertices(int n);
        int shortest_path(int src, int dst, std::stack<int>& path);

private:
        int m_V;
        int m_E;
	std::vector<std::vector<int>> adjMatrix;
};

#endif
