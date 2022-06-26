
#include<bits/stdc++.h>
using namespace std;


typedef pair<int, int> iPair;
int  cities[3000][3000];
vector<int> vectorr[3001], stackk;
int maximum = 0;

void adEdge(vector<int> v[],
             int x,
             int y)
{
    v[x].push_back(y);
    v[y].push_back(x);
}
 

void printPath(vector<int> stack)
{
    for (int i = 0; i < (int)stack.size() - 1; i++) {
		if( cities[stack[i]][stack[i+1]] > maximum)
			maximum =  cities[stack[i]][stack[i+1]];

    }
;
}

void DFS(vector<int> v[],bool vis[],int x,int y,vector<int> stack)
{
    stack.push_back(x);
    if (x == y) {
 

        printPath(stack);
        return;
    }
    vis[x] = true;
 
    // if backtracking is taking place
    if (!v[x].empty()) {
        for (int j = 0; j < v[x].size(); j++) {
            // if the node is not visited
            if (vis[v[x][j]] == false)
                DFS(v, vis, v[x][j], y, stack);
        }
    }
 
    stack.pop_back();
}
 

void DFSCall(int x,int y, vector<int> v[],int n,vector<int> stack)
{

    bool vis[n + 1];
 
    memset(vis, false, sizeof(vis));
 

    DFS(v, vis, x, y, stack);
}






struct Graph{
	int V, E;
	vector< pair<int, iPair> > edges;

	Graph(int V, int E)	{
		this->V = V;
		this->E = E;
	}


	void addEdge(int u, int v, int w)	{
		edges.push_back({w, {u, v}});
	}
	int kruskalMST();
};


struct DisjointSets{
	int *parent, *rnk;
	int n;

	DisjointSets(int n)	{

		this->n = n;
		parent = new int[n+1];
		rnk = new int[n+1];

		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}

	int find(int u)	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// Union by rank
	void merge(int x, int y){
		x = find(x), y = find(y);

		if (rnk[x] > rnk[y])
			parent[y] = x;
		else 
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};


int Graph::kruskalMST(){
	int mst_wt = 0;

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector< pair<int, iPair> >::iterator it;
	for (it=edges.begin(); it!=edges.end(); it++)	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);
		if (set_u != set_v)		{
			 cities[u][v] = it->first;
			 cities[v][u] = it->first;
			adEdge(vectorr,u,v);
			mst_wt += it->first;
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}




int main(){
	int V,E,a,b,c,cnt;
	cin >> V >> E;

	Graph g(V, E);

	for (int i=0; i<E; i++){
		cin >> a >> b >> c;
		g.addEdge(a-1, b-1, c);
	}

	int mst_wt = g.kruskalMST();
	cin >> cnt;
	int  dist[cnt];
	for(int i=0; i<cnt; i++){
		cin >> a >> b;
		DFSCall(a-1, b-1, vectorr, V, stackk);
		 dist[i] = maximum;
		maximum = 0;
	}
	for(int i=0; i<cnt; i++){
		cout <<  dist[i] << '\n';
	}
	return 0;
}
