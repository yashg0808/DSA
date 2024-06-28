#include <bits/stdc++.h>
using namespace std;

// 1. TopoSort with DFS
void dfs(vector<vector<int> >& adjList, int startNode,
         vector<bool>& visited, stack<int> &st)
{
    visited[startNode]=1;
    for(auto i:adjList[startNode]){
        if(!visited[i])dfs(adjList, i, visited, st);
    }
    st.push(startNode);
}

vector<int> topoSort(vector<vector<int> >& adjList, int vertices){
    stack<int> st;
    vector<bool> visited(vertices, 0);
    for(int i=0; i<vertices; i++){
        if(!visited[i]){
            visited[i]=1;
            dfs(adjList, i, visited, st);
        }
    }
    vector<int> ans;
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}

// 2. Toposort with BFS
vector<int> topoSortBFS(vector<vector<int> >& adjList, int vertices){
    vector<int> inDegree(vertices, 0);
    for(int i=0; i<vertices; i++){
        for(auto j:adjList[i]){
            inDegree[j]++;
        }
    }
    queue<int> q;
    for(int i=0; i<vertices; i++){
        if(inDegree[i]==0)q.push(i);
    }
    vector<int> ans;
    while(!q.empty()){
        int node=q.front();
        q.pop();
        ans.push_back(node);
        for(auto i:adjList[node]){
            inDegree[i]--;
            if(inDegree[i]==0)q.push(i);
        }
    }
    return ans;
}

// 3. same as level order traversal (bfs)
void bfs(vector<vector<int> >& adjList, int startNode,
         vector<bool>& visited, vector<int> &min_dist_from_source)
{
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int currentNode = q.front();
        cout << currentNode << " ";
        for (int neighbor : adjList[currentNode]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                min_dist_from_source[neighbor] = min_dist_from_source[currentNode] + 1;
                q.push(neighbor);
            }
        }
        q.pop();
    }
    return;
}

// 4. dijkstra
vector<int> dijkstra(vector<vector<pair<int,int>>> adjList, int s, int V){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V, 1e9);

    dist[s]=0;
    pq.push({0,s});

    while(!pq.empty()){
        int dis=pq.top().first;
        int node=pq.top().second;
        pq.pop();
        for(auto it:adjList[node]){
            int adjNode=it.first;
            int edgeWeight=it.second;
            if(dis+edgeWeight<dist[adjNode]){
                dist[adjNode]=dis+edgeWeight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

// 5. rotten oranges using bfs
int bfs1(vector<vector<int>> &grid){

    int m = grid.size();
    int n = grid[0].size();
    int fresh = 0;
    queue<pair<int, int>> rotten;

    // Count fresh oranges and find initial rotten positions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                fresh++;
            } else if (grid[i][j] == 2) {
                rotten.push({i, j});
            }
        }
    }

    // BFS to spread the rotten oranges
    int minutes = 0;
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!rotten.empty() && fresh > 0) {
        int size = rotten.size();
        for (int i = 0; i < size; i++) {
            int x = rotten.front().first;
            int y = rotten.front().second;
            rotten.pop();
            for (auto& dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    fresh--;
                    rotten.push({nx, ny});
                }
            }
        }
        minutes++;
    }


    // Check if there are still fresh oranges left
    if (fresh > 0) {
        return -1;
    }
    return minutes;
}

// 6. detecting a cycle in an undirected graph using BFS
bool detectCycleInUndirectedGph(vector<vector<int>> &adjList, int startNode, vector<bool> &visited){
    queue<pair<int, int>> q;
    //{node, parent}
    q.push({startNode, -1});
    visited[startNode]=1;

    while(!q.empty()){
        int node=q.front().first;
        int parent=q.front().second;
        q.pop();

        for(auto i:adjList[node]){
            if(!visited[i]){
                visited[i]=1;
                q.push({i, node});
            }
            else if(parent!=i){
                return true;
            }
        }
    }
    return false;
}

// 7. detecting a cycle in a directed graph using DFS
bool detectCycleInDirectedGph(vector<vector<int>> &adjList, int startNode, vector<bool> &visited, vector<bool> &pathVisit){
    visited[startNode]=1;
    pathVisit[startNode]=1;

    for(auto i:adjList[startNode]){
        if(!visited[i]){
            if(detectCycleInDirectedGph(adjList, i, visited, pathVisit))return true;
        }
        else if(pathVisit[i])return true;
    }
    pathVisit[startNode]=0;
    return false;
}

void addEdge(vector<vector<int> >& adjList, int u, int v)
{
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void addWeightedEdge(vector<vector<pair<int,int>>>& adjList, int u, int v, int w){
    adjList[u].push_back(make_pair(v, w));
    adjList[v].push_back(make_pair(u, w));
}

void addDirectedEdge(vector<vector<int> >& adjList, int u, int v){
    adjList[u].push_back(v);
}

int main()
{
//    //BFS{
//    int vertices = 5;
//    vector<int> min_dist_from_source(vertices,0);
//
//    vector<vector<int>> adjList(vertices);
//
//    // Add edges to the graph
//    addEdge(adjList, 0, 1);
//    addEdge(adjList, 0, 2);
//    addEdge(adjList, 1, 3);
//    addEdge(adjList, 1, 2);
//    addEdge(adjList, 2, 4);
//    addEdge(adjList, 3, 4);
//
//    vector<bool> visited(vertices, false);
//    bfs(adjList, 0, visited, min_dist_from_source);
//    cout<<endl<<min_dist_from_source[4]<<endl;
//    //}

//    //DIJKSTRA{
//    vector<vector<pair<int,int>>> adj(9);
//
//    addWeightedEdge(adj, 0, 1, 4);
//    addWeightedEdge(adj, 0, 7, 8);
//    addWeightedEdge(adj, 1, 2, 8);
//    addWeightedEdge(adj, 1, 7, 11);
//    addWeightedEdge(adj, 2, 3, 7);
//    addWeightedEdge(adj, 2, 8, 2);
//    addWeightedEdge(adj, 2, 5, 4);
//    addWeightedEdge(adj, 3, 4, 9);
//    addWeightedEdge(adj, 3, 5, 14);
//    addWeightedEdge(adj, 4, 5, 10);
//    addWeightedEdge(adj, 5, 6, 2);
//    addWeightedEdge(adj, 6, 7, 1);
//    addWeightedEdge(adj, 6, 8, 6);
//    addWeightedEdge(adj, 7, 8, 7);
//
//
//    vector<int> ans = dijkstra(adj, 0, 9);
//
//    // Debug: ensure dijkstra ran successfully
//    cout << "Dijkstra completed. Distances from source:" << endl;
//
//    for (int i = 0; i < ans.size(); ++i) {
//        cout << "Node " << i << " is at distance " << ans[i] << endl;
//    }
//    //}

//    //DFS{
//    int vertices = 5;
//    vector<vector<int>> adjList(vertices);
//    vector<bool> visited(vertices, false);
//    addEdge(adjList, 0, 1);
//    addEdge(adjList, 0, 2);
//    addEdge(adjList, 1, 3);
//    addEdge(adjList, 1, 2);
//    addEdge(adjList, 2, 4);
//    addEdge(adjList, 3, 4);
//    stack<int> st;
//    dfs(adjList, 0, visited, st);
//    //}

// //    TopoSort using DFS{
//    int vertices=6;
//    vector<vector<int>> adjList(vertices);
//    addDirectedEdge(adjList, 5, 0);
//    addDirectedEdge(adjList, 5, 2);
//    addDirectedEdge(adjList, 2, 3);
//    addDirectedEdge(adjList, 3, 1);
//    addDirectedEdge(adjList, 4, 0);
//    addDirectedEdge(adjList, 4, 1);
//    vector<int> ans=topoSort(adjList, vertices);
//    for(auto i:ans){
//        cout<<i<<" ";
//    }
// //  }

//    //TopoSort using BFS{
//    int vertices=6;
//    vector<vector<int>> adjList(vertices);
//    addDirectedEdge(adjList, 5, 0);
//    addDirectedEdge(adjList, 5, 2);
//    addDirectedEdge(adjList, 2, 3);
//    addDirectedEdge(adjList, 3, 1);
//    addDirectedEdge(adjList, 4, 0);
//    addDirectedEdge(adjList, 4, 1);
//    vector<int> ans=topoSortBFS(adjList, vertices);
//    for(auto i:ans){
//        cout<<i<<" ";
//    }
//    //  }

    // //detecting a cycle in an undirected graph using bfs{
    // int vertices = 5;
    // vector<vector<int>> adjList(vertices);
    // vector<bool> visited(vertices, false);
    // addEdge(adjList, 0, 2);
    // addEdge(adjList, 1, 3);
    // addEdge(adjList, 1, 2);
    // addEdge(adjList, 2, 4);
    // cout<<detectCycleInUndirectedGph(adjList, 0, visited);
    // //}

    // //detecting a cycle in a directed graph using dfs{
    // int vertices = 11;
    // vector<vector<int>> adjList(vertices);
    // vector<bool> visited(vertices, false);
    // vector<bool> pathVisit(vertices, false);
    // addDirectedEdge(adjList, 1, 2);
    // addDirectedEdge(adjList, 2, 3);
    // addDirectedEdge(adjList, 3, 4);
    // addDirectedEdge(adjList, 4, 9);
    // addDirectedEdge(adjList, 9, 10);
    // addDirectedEdge(adjList, 3, 8);                  
    // addDirectedEdge(adjList, 8, 9);
    // addDirectedEdge(adjList, 7, 2);
    // addDirectedEdge(adjList, 7, 5);
    // addDirectedEdge(adjList, 5, 6);
    // addDirectedEdge(adjList, 6, 7);
    // for(int i=1; i<vertices; i++){
    //     if(!visited[i]){
    //         cout<<detectCycleInDirectedGph(adjList, i, visited, pathVisit)<<endl;
    //     }
    // }
    // //}
    return 0;
}
