#include<bits/stdc++.h>
const int maxn = 0x3f3f3f3f;
using namespace std;
class Graph {
private:
    int V; // 顶点数
    vector< vector<int> > adj; // 邻接矩阵  

public:
    Graph(int input) : V(input), adj(input) {
		for(int i = 0; i < V; i++)
			for(int j = 0; j < V; j++)
			{
				adj[i].push_back(-1);
			}
	}

    // 添加边
    void add (int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w;
    }
	// 删除边
	void remove(int u, int v){
		adj[u][v] = -1;
	} 
	int scan(int u, int v){
		return adj[u][v];
	}
	void remove(int point) // 未完成版本  
	// 删除点操作  
	{
		V--;
	} 
    // 深度优先遍历
    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < adj[v].size(); ++i) {
            // int u = adj[v][i];
            if (!visited[i] && adj[v][i] != -1) {
                DFS(i, visited);
            }
        }
    }

    void DFS() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
    }

    // 广度优先遍历 
    void BFS(int s, vector<bool>& visited) {
        queue<int> q;
        visited[s] = true;
        q.push(s);
		cout << s << " ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int i = 0; i < adj[v].size(); ++i) {
                // int u = adj[v][i];
                if (!visited[i] && adj[v][i] != -1) {
                	cout << i << " ";
                	visited[i] = true;
                	q.push(i);
            	}
            }
        }
    }
    
    
    void BFS() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                BFS(i, visited);
            }
        }
    }

    // Dijkstra算法 
    void dijkstra(int s, vector<int>& dist) {
        vector<bool> visited(V, false);
        // 最小值优先队列 pair<distance, index>   
        priority_queue< pair<int, int>, vector<pair <int, int> >, greater< pair<int, int> > > pq;

        dist.assign(V, maxn);
        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            int v = pq.top().second;
            pq.pop();

            if (visited[v]) {
                continue;
            }
            visited[v] = true;

            for (int i = 0; i < adj[v].size(); ++i) {
            	if(adj[v][i] != -1){
            		int w = adj[v][i];
                	// int w = 1; // 边权重为 1，可以根据实际需求修改 
                	if (dist[i] > dist[v] + w) {
                 	   dist[i] = dist[v] + w;
                 	   pq.push({dist[i], i});
                	}
				}
                
            }
        }
    }

    // 最小生成树算法  (Prim算法)  
    void primMST() {
        vector<bool> visited(V, false);   
        vector<int> dist(V, maxn);  
        vector<int> parent(V, -1);  
        priority_queue< pair<int, int>, vector< pair <int, int> >, greater< pair<int, int> > > pq;

        int src = 0;
        dist[src] = 0;
        pq.push({0, src}) ;

        while (!pq.empty()) {
            int v = pq.top().second;
            pq.pop();

            if (visited[v]) {
                continue;
            }
            visited[v] = true;

            for (int i = 0; i < adj[v].size(); ++i) {
                if(adj[v][i] != -1)
                {
                	int w = adj[v][i];

                	if (!visited[i] && dist[i] > w) {
                    	dist[i] = w;
                    	parent[i] = v;
                    	pq.push({dist[i], i});
                	}
				}
            }
        }

        // 打印最小生成树
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << endl;
        }
    }
};

