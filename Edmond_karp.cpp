#include<bits/stdc++.h>
using namespace std;

class Graph
{
	int V;
	int E;
public:
	Graph(int v, int e)
	{
		V = v;
		E = e;
	}

	bool bfs(int **residualCapacity, int src, int sink, int *parent)
	{
		
		vector<bool> visited(V,0);

		queue<int> q;
		q.push(src);
		bool augmentedPath = false;
		visited[src] = true;
		
		while(!q.empty())
		{
			int u = q.front();
			q.pop();

			for(int v=0;v<V;v++)
			{
				
				if(visited[v] == false && residualCapacity[u][v] > 0) 	// checking condition for augmented path
				{
					
					parent[v] = u;
					visited[v] = true;
					q.push(v);
					if(v == sink) 	// checking if path lead to sink or not
					{
						augmentedPath = true;
						break;
					}
				}
			}
		}
		
		return augmentedPath;
	}

	void print(vector<vector<int>> augmentedPath)
	{
		for(int i=0;i<augmentedPath.size();i++)
		{
			for(int j=0;j<augmentedPath[i].size();j++)
			{
				cout<<augmentedPath[i][j]<<"->";
			}
			cout<<endl;
		}
	}

	int maxFlowGraph(int **capacity, int src, int sink)
	{
		int *parent = new int [V];	//To store the parent in each path for backtracking
		int **residualCapacity = new int*[V];	//Copy of adjacency matrix to store values after modification

		for(int i=0;i<V;i++)
		{
			residualCapacity[i] = new int[V];
		}

		for(int i=0;i<V;i++)
		{
			for(int j=0;j<V;j++)
			{
				residualCapacity[i][j] = capacity[i][j];
			}
		}
		vector<vector<int>> augmentedPath;	//for storing all the possible augmented paths

		int maxFlow = 0;
		
		while(bfs(residualCapacity,src,sink,parent))
		{
			
			vector<int> currentPath;
			int flow = INT_MAX;

			int v = sink;	//aqssign sink to v and trace the path till source
			while(v != src)
			{
				currentPath.push_back(v);
				int u = parent[v];

				if(flow > residualCapacity[u][v])	// finding maximum flow of augmented path
				{
					flow = residualCapacity[u][v];
				}
				v = u;
			}
			currentPath.push_back(src);	//adding source to current path
			reverse(currentPath.begin(),currentPath.end());	// reversing the path as it is determined from sink to src
			augmentedPath.push_back(currentPath);
			maxFlow += flow;	// adding flow to max values
			v = sink;
			while(v != src)
			{
				int u = parent[v];
				residualCapacity[u][v] -= flow;	// subtracting flow from all forward edges
				residualCapacity[v][u] += flow;	// adding flow to all backward edges
				v = u;
			}
		}
		
		print(augmentedPath);
		return maxFlow;
	}

};

int main()
{
/* 
INPUT
5 7
0 2 100
0 3 50
2 3 50
2 4 50
2 1 50
3 4 100
4 1 125
0 1
OUTPUT
0->2->1->
0->2->4->1->
0->3->4->1->
150
*/
	int v,e;
	cin>>v>>e;
	
	Graph g(v,e);

	int **capacity = new int*[v];	//Creating adjacency matrix dynamically

	for(int i=0;i<v;i++)
	{
		capacity[i] = new int[v];
	}

	for(int i=0;i<v;i++)
	{
		for(int j=0;j<v;j++)
		{
			capacity[i][j] = 0;	//Assigning 0 to all the values of adjacency matrix
		}
	}

	for(int i=0;i<e;i++)
	{
		int v1,v2,c;	//u v w
		cin>>v1>>v2>>c;
		capacity[v1][v2] = c;
	}
	 int source, sink;
	 cin>>source>>sink;

	
	cout<<g.maxFlowGraph(capacity,source,sink);

	return 0;
}
