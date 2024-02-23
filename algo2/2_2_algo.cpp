#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

void addEdge(vector<int> adj[], int u, int v,int distance, map<pair<int,int>, int> &edges)
{
    adj[u].push_back(v);
    adj[v].push_back(u);

    edges[{u,v}] = distance;
    edges[{v,u}] = distance;
}

void DFS(int *prev,int v, bool *visited, vector<int> adj[],map<pair<int,int>,int> &edges, int *distance_to,int total_d){
    visited[v] = true;

    vector<int>::iterator it;
    
    for(it = adj[v].begin(); it != adj[v].end(); ++it){
        if(!visited[*it]){
            prev[*it] = v;
            distance_to[*it] = total_d + edges[{v,*it}];
            DFS(prev, *it, visited, adj, edges, distance_to, distance_to[*it]);
        }  
    }
}


void DFS_final(int *prev, int v, bool *visited, vector<int> adj[], map<pair<int,int>,int> &edges, int *distance_to, int *prep, int *speed, int *minimum_time){
    visited[v] = true;
    
    //minimum time to reach root
    int min_time;
    vector<int>::iterator it;

    //skip root
    if(v == 0){
        min_time = 0;
    }
    else{
        //default time to reach root
        min_time = prep[v] + (speed[v] * distance_to[v]);
        
        int cost = edges[{v, prev[v]}];



        int node = prev[v];

        while(prev[node] != -1){
            int temp = prep[v] + cost * speed[v] + minimum_time[node];

            cost += edges[{node,prev[node]}];

            if(temp < min_time){
                min_time = temp;
            }

            node = prev[node];

        }
    }
    // cout << min_time << '\n';
    minimum_time[v] = min_time;
    for(it = adj[v].begin(); it != adj[v].end(); ++it){
        if(!visited[*it]){
            DFS_final(prev, *it, visited, adj, edges, distance_to, prep, speed, minimum_time);
        }
    }
}


int main(){
    int n;
    cin >> n;

    //adjacency list
    vector<int> adj[n];
   
    //previous node array
    int *prev = new int[n];
    prev[0] = -1;
    
    int *prep = new int[n];
    int *speed = new int[n];
    
    bool *visited = new bool[n];
    visited[n-1] = false;
    
    //dictionary to quickly access length of edge(road)
    map<pair<int,int> , int> edges;
    
    for(int i = 0; i < n-1; i++){
        int r,c,d;
        cin >> r >> c >> d;
        r -= 1;
        c -= 1;
        addEdge(adj, r, c, d, edges);
    }
    for(int i = 0; i < n-1; i++){
        int r,c;
        cin >> r >> c;
        prep[i+1] = r;
        speed[i+1] = c;
        visited[i] = false;
    }
    
    int *distance_to = new int[n];
    distance_to[0] = 0;
    
    // Calculate distance to initial node for every node and the previous node array
    DFS(prev,0,visited,adj, edges, distance_to, 0);
    

    int *minimum_time = new int[n];
    minimum_time[0] = 0;

    // reset visited array
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }
    DFS_final(prev, 0, visited, adj, edges, distance_to, prep, speed, minimum_time);
    cout << minimum_time[1];
    for(int i = 2; i < n; i++){
        cout << ' ' << minimum_time[i];
    }
    cout << '\n';
    return 0;
}