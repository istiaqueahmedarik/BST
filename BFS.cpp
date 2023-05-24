#include <bits/stdc++.h>
using namespace std;
#define white 0
#define grey 1
#define black 2
const int N = 1e5 + 5;
vector<int> adjList[N];
int nodeList[N];
int color[N];
int main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    for (int i = 0; i <= nodes; i++)
        nodeList[i] = i;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        color[u] = white;
        color[v] = white;
    }
    int source;
    cin >> source;
    queue<int> q;
    q.push(source);
    color[source] = grey;
    while (!q.empty())
    {
        int node = q.front();
        cout << node << " " << endl;
        q.pop();
        for (int i = 0; i < adjList[node].size(); i++)
        {
            if (color[adjList[node][i]] == black)
                continue;
            q.push(adjList[node][i]);
            color[adjList[node][i]] = grey;
        }
        color[node] = black;
    }
}