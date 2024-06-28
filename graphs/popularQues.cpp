#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/course-schedule/description/
class courseSchedule
{
public:
    bool canFinish(int vertices, vector<vector<int>> &prerequisites)
    {
        vector<int> adjList[vertices];
        vector<int> inDegree(vertices, 0); // incoming edges to a node
        for (auto i : prerequisites)
        {
            adjList[i[1]].push_back(i[0]);
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