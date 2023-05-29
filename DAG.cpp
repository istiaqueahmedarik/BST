#include <bits/stdc++.h>
using namespace std;
const int white = 0;
const int gray = 1;
const int black = 2;
map<int, int> color;
map<int, vector<int>> adjList;
vector<int> temp;
bool isCycle(int u, int parent)
{
    color[u] = gray;
    temp.push_back(u);
    for (int v : adjList[u])
    {
        if (color[v] == white)
        {
            if (isCycle(v, u))
                return true;
        }
        else if (v != parent)
        {
            temp.push_back(v);
            return true;
        }
    }
    color[u] = black;
    temp.pop_back();
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
    if (isCycle(src, -1))
    {

        cout << "YES!!" << endl;
        int last = temp.back();
        int n = temp.size();
        cout << last << " ";
        for (int i = n - 2; temp[i] != last; i--)
        {
            cout << temp[i] << " ";
        }
        cout << last << endl;
    }
    else
        cout << "NO!!" << endl;
}