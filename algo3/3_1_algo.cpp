#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

bool bfs(int &n, unordered_map<int, vector<int> > &graph, int start, int end){
    vector<bool> visited(n, 0);
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        if(curr == end){
            return 1;
        }
        for(auto &node : graph[curr]){
            if(curr == start && node == end){
                continue;
            }
            if(!visited[node]){
                visited[node] = 1;
                q.push(node);
            }
        }
    }
    return false;
}

int fixRoads(map<int, pair<int,int> > &roadsOrdered, unordered_map<int, vector<int> > &graph, int &k, int &n){
    for(auto x : roadsOrdered){
        int node1 = x.second.first;
        int node2 = x.second.second;

        if(bfs(n, graph, node1, node2)){
            graph[node1].erase(remove(graph[node1].begin(), graph[node1].end(), node2), graph[node1].end());
            graph[node2].erase(remove(graph[node2].begin(), graph[node2].end(), node1), graph[node2].end());
        }
        else{
            if(k == 0){
                return x.first;
            }
            k--;
        }
    }

    return -1;
}


int main(){
    int n,m,k;
    cin >> n >> m >> k;
    map<int, pair<int,int> > roadsOrdered;
    unordered_map<int, vector<int> > graph;

    for(int i = 0; i < m; i++){
        int node1, node2, temp;

        cin >> node1 >> node2 >> temp;

        //map them in ascending order based on time
        roadsOrdered[temp] = {node1,node2};

        //also keep the graph in a vector adjacency list for bfs traversal
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);

    }

    int result = fixRoads(roadsOrdered, graph, k, n);
    if(result == -1){
        cout << "infinity" << endl;
    }
    else{
        cout << result << endl;
    }
    return 0;
}