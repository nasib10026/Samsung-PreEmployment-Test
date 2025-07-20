
#include<bits/stdc++.h>
bool dfs(int node,vector<vector<int>>&adj,vector<int>&vis,vector<int>&pathVis)
{
  vis[node] = 1;
  pathVis[node] = 1;
  
  for(auto nbr:adj[node]){
    if(!vis[nbr])
    {
      if(dfs(nbr,adj,vis,pathVis))return true;
    }
    else if(pathVis[nbr])return true;
  }
  pathVis[node] = 0;
  return false;
}
int detectCycleInDirectedGraph(int n, vector < pair < int, int >> & edges) {
  // Write your code here.
  vector<vector<int>>adj(n+1);
  for(auto pair: edges)
  {
    int u = pair.first;
    int v = pair.second;
    adj[u].push_back(v);
  }
  vector<int>vis(n+1,0);
  vector<int>pathVis(n+1,0);
  for(int i = 1;i<=n;i++)
  {
    if(!vis[i])
    {
      if(dfs(i,adj,vis,pathVis))return 1;
    }
  }
  return 0;
}
