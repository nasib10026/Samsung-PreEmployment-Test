#include<iostream>
#include<map>
#include<set>
#include<algorithm>
#include<cmath>
#include<queue>
#include<tuple>
#include<vector>

using namespace std;

typedef pair<int, int> PII;
typedef tuple<PII, PII, int> wormHole;

int manhattan(PII a,PII b)
{
    return abs(a.first-b.first) + abs(a.second - b.second);
}
int solve(int n,PII src,PII dest,vector<wormHole>& wormholes){
    vector<PII>points;
    points.push_back(src);
    points.push_back(dest);
    for(auto& wh:wormholes){
        PII p1 = get<0>(wh);
        PII p2 = get<1>(wh);
        points.push_back(p1);
        points.push_back(p2);
    }

    int nodes = points.size();
    vector<vector<PII>>adj(nodes);
    for(int i = 0;i<nodes;i++){
        for(int j = i+1;j<nodes;j++){
             int cost = manhattan(points[i], points[j]);
             adj[i].push_back(make_pair(j,cost));
             adj[j].push_back(make_pair(i,cost));
        }
    }

    for(int i = 0;i<n;i++)
    {
        int idx1 = 2 + 2 * i;
        int idx2 = 2 + 2 * i+1;
        int cost = get<2>(wormholes[i]);
        adj[idx1].push_back(make_pair(idx2, cost));
        adj[idx2].push_back(make_pair(idx1,cost));
    }

    vector<int>dist(nodes, 1e9);
    dist[0] = 0;
    priority_queue<PII,vector<PII>, greater<PII>>pq;
    pq.push(make_pair(0, 0)); 

    while(!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        for(auto& nbr: adj[u])
        {
            int nbrDist = nbr.second;
            int v = nbr.first;
            if(dist[v] > dist[u] + nbrDist)
            {
                dist[v] = dist[u] + nbrDist;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist[1];
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        int sx,sy,dx,dy;
        cin>>sx>>sy>>dx>>dy;
        PII src = make_pair(sx, sy);
        PII dest = make_pair(dx, dy);
        vector<wormHole> wormholes;
        for(int i = 0; i < n; i++) {
            int x1, y1, x2, y2,cost;
            cin>>x1>>y1>>x2>>y2>>cost;
            wormholes.push_back( make_tuple(make_pair(x1, y1), make_pair(x2, y2), cost));
        }
        int result = solve(n, src, dest, wormholes);
        cout << result << endl;
    }

}