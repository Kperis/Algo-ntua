#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

void dijkstra_algo(vector<vector<pair<int,int> > > &adj, vector<int> &distance_to, vector<int> &predecessor, int src){
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;

    pq.push(make_pair(0, src));
    distance_to[src] = 0;

    //Dijkstra
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        vector<pair<int,int> >::iterator it;
        for(it = adj[u].begin(); it != adj[u].end(); ++it){
            int v = (*it).first;
            int d = (*it).second;

            if(distance_to[v] > distance_to[u] + d){
                distance_to[v] = distance_to[u] + d;
                predecessor[v] = u;
                pq.push(make_pair(distance_to[v], v));
            }
        }
    }
}

int main(){
    int n, m, t, president, source, destination;
    cin >> n >> m;
    cin >> source >> destination >> t >> president;
    vector<vector<pair<int,int> > > adj(n);


    vector<int> distance_to(n, INF);
    vector<int> president_cities;
    
    vector<int> predecessor(n,-1);
    map<pair<int,int>, int> edges;

    for(int i = 0; i < president; i++){
        int x;
        cin >> x;
        president_cities.push_back(x-1);
    }

    for(int i = 0; i < m; i++){
        int u,v,d;
        cin >> u >> v >> d;

        edges[{u-1,v-1}] = d;
        edges[{v-1,u-1}] = d;

        adj[u-1].push_back({v-1, d});
        adj[v-1].push_back({u-1, d});
    }

    dijkstra_algo(adj, distance_to, predecessor, destination-1);
    
    vector<bool> isHere(n,false);
    vector<pair<int, pair<int,int> > > occupied(president);

    vector<int>::iterator x,j;
    x = president_cities.begin();
    j = x+1;
    int l = 0;
    int miniute_counter = 0;

    while(j != president_cities.end()){
        int c1 = *x;
        int c2 = *j;

        occupied[l] = {miniute_counter, {c1,c2}};
        miniute_counter += edges[{c1,c2}];

        x++;
        j++;
        l++;
    }

    occupied[l] = {miniute_counter, {*x, -1}};



    int current_node = source-1;
    int count = t;
    int president_count = 0;
    bool moving = false;
    bool started = false;
    bool pres_moving = true;

    l = 0;
    isHere[occupied[l].second.first] = true;
    isHere[occupied[l].second.second] = true;

    bool reached = false;

    while(current_node != destination-1){
        while(count >= occupied[l].first && count < occupied[l+1].first && !reached){
            if(isHere[current_node] && isHere[predecessor[current_node]]){
                vector<pair<int,int> >::iterator p;
                p = adj[current_node].begin();
                int c, saved_node;
                if(p->first == predecessor[current_node]){
                    p++;
                    if(p == adj[current_node].end()) {
                        count = occupied[l+1].first;
                        count += edges[{current_node, predecessor[current_node]}];
                        current_node = predecessor[current_node];
                        if(current_node == destination-1) reached = true; 
                        continue;
                    }
                    
                }
                c = distance_to[p->first];
                saved_node = p->first;
                while(p != adj[current_node].end()){
                    if(p->first != predecessor[current_node] && c > distance_to[p->first]){
                        c = distance_to[p->first];
                        saved_node = p->first;
                    }
                    p++;
                }
                if(count + c + edges[{saved_node, current_node}] < president_count + distance_to[predecessor[current_node]] + edges[{current_node, predecessor[current_node]}]){
                    count += edges[{saved_node, current_node}];
                    current_node = saved_node;
                    if(current_node == destination - 1) reached = true;
                    continue;
                }
                else{
                    count = occupied[l+1].first;
                    count += edges[{current_node, predecessor[current_node]}];
                    current_node = predecessor[current_node];
                    if(current_node == destination-1) reached = true; 
                    continue;
                }
            }
            else{
                count += edges[{current_node, predecessor[current_node]}];
                current_node = predecessor[current_node];
                if(current_node == destination-1) reached = true;
            }
        }
        if(reached){
            break;
        }
        else{
            isHere[occupied[l].second.first] = false;
            l++;
            isHere[occupied[l].second.second] = true;
            continue;
        }

    }


    if(current_node == destination-1){
        cout << count-t << '\n';
        return 0;
    }
    else{
        while(current_node != destination-1){
            count += edges[{current_node, predecessor[current_node]}];
            current_node = predecessor[current_node];
        }
        cout << count-t << '\n';
        return 0;
    }
    

}