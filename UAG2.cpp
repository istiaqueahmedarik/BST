#include <bits/stdc++.h>
using namespace std;
const int white = 0;
const int gray = 1;
const int black = 2;
map<int, int> color;
map<int, vector<int>> adjList;
bool isCycle(int u)
{
    color[u] = gray;
    for (int v : adjList[u])
    {
        if (color[v] == white)
        {
            if (isCycle(v) == true)
                return true;
        }
        else if (color[v] == gray)
            return true;
    }
    color[u] = black;
    return false;
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
        color[u] = white;
        color[v] = white;
    }
    int src;
    cin >> src;
    if (isCycle(src))
    {

        cout << "YES!!" << endl;
    }
    else
        cout << "NO!!" << endl;
}