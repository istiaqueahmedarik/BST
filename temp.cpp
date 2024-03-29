#include <bits/stdc++.h>
using namespace std;
const int white = 0;
const int gray = 1;
const int black = 2;
map<int, vector<int>> adjList;
map<int, int> color;
void dfs(int node)
{
    color[node] = gray;
    cout << node << " ";
    for (int adjacent : adjList[node])
    {
        if (color[adjacent] == white)
            dfs(adjacent);
    }
    color[node] = black;
}
int main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        color[u] = white;
        color[v] = white;
    }
    int src;
    cin >> src;
    dfs(src);
}