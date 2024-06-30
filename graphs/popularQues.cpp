#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/course-schedule/description/
class courseSchedule
{
public:
    void addEdge(vector<vector<int>> &adjList, int u, int v)
    {
        adjList[u].push_back(v);
    }
    bool canFinish(int vertices, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> adjList(vertices);
        vector<int> inDegree(vertices, 0); // incoming edges to a node
        for (auto i : prerequisites)
        {
            addEdge(adjList, i[1], i[0]);
            inDegree[i[0]]++;
        }

        // store nodes with 0 incoming edges(top of the chain) in a queue
        queue<int> q;
        for (int i = 0; i < vertices; i++)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }
        // pop the top of the chain and reduce the incoming edges of its neighbours
        vector<int> ans;
        while (!q.empty())
        {
            int node = q.front();
            ans.push_back(node);
            q.pop();

            for (auto i : adjList[node])
            {
                inDegree[i]--;
                if (inDegree[i] == 0)
                    q.push(i);
            }
        }
        return ans.size() == vertices;
    }
};

// https://leetcode.com/problems/01-matrix/description/
class matrix01
{
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> ans(rows, vector<int>(cols, INT_MAX));
        queue<pair<int, int>> q;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (matrix[i][j] == 0)
                {
                    ans[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!q.empty())
        {
            pair<int, int> node = q.front();
            q.pop();
            for (auto dir : dirs)
            {
                int x = node.first + dir.first;
                int y = node.second + dir.second;
                if (x < 0 || x >= rows || y < 0 || y >= cols || ans[x][y] <= ans[node.first][node.second] + 1)
                    continue;
                ans[x][y] = ans[node.first][node.second] + 1;
                q.push({x, y});
            }
        }
        return ans;
    }
};

// https://leetcode.com/problems/number-of-provinces/description/
class numberOfProvinces
{
public:
    void dfs(vector<bool> &vis, int startNode, vector<vector<int>> &adjList)
    {
        vis[startNode] = 1;
        for (auto e : adjList[startNode])
        {
            if (!vis[e])
            {
                dfs(vis, e, adjList);
            }
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        vector<vector<int>> adjList(isConnected.size());
        for (int i = 0; i < isConnected.size(); i++)
        {
            for (int j = 0; j < isConnected.size(); j++)
            {
                if (isConnected[i][j])
                    adjList[i].push_back(j);
            }
        }
        vector<bool> vis(isConnected.size(), 0);
        int ans = 0;
        for (int i = 0; i < isConnected.size(); i++)
        {

            if (!vis[i])
            {
                dfs(vis, i, adjList);
                ans++;
            }
        }
        return ans;
    }
};

// https://leetcode.com/problems/find-eventual-safe-states/description/
class eventualSafeStates
{
public:
    bool dfs(vector<vector<int>> &graph, vector<int> &vis, int node)
    {
        if (vis[node] == 1)
            return 1; // cycle detected
        if (vis[node] == 2)
            return 0;
        vis[node] = 1;
        for (auto i : graph[node])
        {
            if (dfs(graph, vis, i))
                return 1;
        }
        vis[node] = 2; // safe node
        return 0;
    }

    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        vector<int> vis(graph.size(), 0);
        vector<int> ans;
        for (int i = 0; i < graph.size(); i++)
        {
            if (!dfs(graph, vis, i))
                ans.push_back(i);
        }
        return ans;
    }
};

// https://leetcode.com/problems/minimum-height-trees/description/
class Solution
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if (n == 1)
            return {0}; // Single node case

        vector<vector<int>> adjList(n);
        vector<int> degree(n, 0);

        for (auto e : edges)
        {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }

        queue<int> leaves;
        for (int i = 0; i < n; i++)
        {
            if (degree[i] == 1)
            {
                leaves.push(i); // Initial leaves
            }
        }

        int remainingNodes = n;
        while (remainingNodes > 2)
        {
            int leavesSize = leaves.size();
            remainingNodes -= leavesSize;

            for (int i = 0; i < leavesSize; i++)
            {
                int leaf = leaves.front();
                leaves.pop();
                for (auto neighbor : adjList[leaf])
                {
                    degree[neighbor]--;
                    if (degree[neighbor] == 1)
                    {
                        leaves.push(neighbor); // New leaf
                    }
                }
            }
        }

        vector<int> ans;
        while (!leaves.empty())
        {
            ans.push_back(leaves.front());
            leaves.pop();
        }

        return ans;
    }
};

// https://leetcode.com/problems/minimum-cost-to-connect-sticks/description/
// You have some number of sticks with positive integer lengths. These lengths are given as an array sticks, where sticks[i] is the length of the ith stick.
// You can connect any two sticks of lengths x and y into one stick by paying a cost of x + y. You must connect all the sticks until there is only one stick remaining.
// Return the minimum cost of connecting all the given sticks into one stick in this way.
class minCostToConnectSticks
{
public:
    int connectSticks(vector<int> &sticks)
    {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (auto i : sticks)
            pq.push(i);
        int ans = 0;
        while (pq.size() > 1)
        {
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            pq.pop();
            ans += a + b;
            pq.push(a + b);
        }
        return ans;
    }
};