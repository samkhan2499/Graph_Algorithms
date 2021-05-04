#include<iostream>
#include<map>
#include<queue>
#include<list>

using namespace std;

class Graph{
	map<int , list<int>> adjList;
	
	public:
		void addEdge(int u, int v, bool bidir = true)	// To add edge(biderctional)
		{
			adjList[u].push_back(v);
			if(bidir)
			{
				adjList[v].push_back(u);
			}
		}
		
		void bfs(int src)
		{
			queue<int> q;
			map<int,bool> visited;
			
			q.push(src);
			visited[src] = true;
			
			while(!q.empty())
			{
				int node = q.front();
				cout<<node<<" ";
				q.pop();
				
				for(auto neighbour : adjList[node])
				{
					if(!visited[neighbour])
					{
						q.push(neighbour);
						visited[neighbour] = true;
					}
				}
			}
		}
		
};

int main()
{
	Graph g;
  
 /*  0----------1
     |          |
     |          |
     4----------2-----3------5
     |                |
     |________________|
     
*/
	// Insertion of edges
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,4);
	g.addEdge(4,0);
	g.addEdge(2,3);
	g.addEdge(4,3);
	g.addEdge(3,5);
	
	g.bfs(0);
  // OUTPUT -> 0 1 4 2 3 5
}
