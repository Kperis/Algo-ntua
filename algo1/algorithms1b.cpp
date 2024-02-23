#include<utility>
#include<iostream>
#include<vector>
#include<algorithm> 
#include<stdio.h>
using namespace std; 

typedef vector< pair< pair<int,int>, pair<int,int> > > edge;


// To represent Disjoint Sets 
struct DisjointSets 
{ 
	int *parent, *rnk; 
	int n; 

	// Constructor. 
	DisjointSets(int n) 
	{ 
		// Allocate memory 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		// Initially, all vertices are in 
		// different sets and have rank 0. 
		for (int i = 0; i <= n; i++) 
		{ 
			rnk[i] = 0; 

			//every element is parent of itself 
			parent[i] = i; 
		} 
	} 

	// Find the parent of a node 'u' 
	// Path Compression 
	int find(int u) 
	{ 
		/* Make the parent of the nodes in the path 
		from u--> parent[u] point to parent[u] */
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	// Union by rank 
	void merge(int x, int y) 
	{ 
		x = find(x), y = find(y); 

		/* Make tree with smaller height 
		a subtree of the other tree */
		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else // If rnk[x] <= rnk[y] 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

/* Functions returns weight of the MST*/

double kruskalMST(int &V, int &E, edge &e, double c, int &finalp, int &finalw) 
{ 
	double mst_wt = 0.0; // Initialize result 

	// Create disjoint sets 
	DisjointSets ds(V); 

	// Iterate through all sorted edges 
	edge::iterator it; 
	for (it=e.begin(); it!=e.end(); it++) 
	{ 
    
        int u = it->first.first; 
        int v = it->first.second; 
    
        
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
    

		// Check if the selected edge is creating 
		// a cycle or not (Cycle is created if u 
		// and v belong to same set) 
		if (set_u != set_v) 
		{   
			mst_wt += (double(it->second.first) - c*(double(it->second.second)));
			finalp += it->second.first;
			finalw += it->second.second;
			
			cout << double(it->second.first)/double(it->second.second) << ' ';
			// Merge two sets 
			ds.merge(set_u, set_v); 
		} 
	} 

	cout << ' ' << c << '\n';

	return mst_wt; 
} 

bool CompareBasedOnRatio(const pair<pair<int,int>, pair<int,int> > &e1, const pair<pair<int,int>, pair<int,int> > &e2){
    if(double(e1.second.first)/double(e1.second.second) > double(e2.second.first)/double(e2.second.second)){
        return true;
    }
    return false;
}



int main() 
{ 
	int V, E, finalp = 0,finalw = 0; 
    cin >> V >> E;
    edge arr;
    for(int i = 0; i < E; i++){
        int v1,v2,p,w;
        cin >> v1 >> v2 >> p >> w;

        arr.push_back({{v1,v2},{p,w}});
    }
    
    sort(arr.begin(), arr.end(), CompareBasedOnRatio);


    double max_ratio = double(arr[0].second.first)/double(arr[0].second.second); //we know that the final result is for sure smaller than the edge with the highest ratio

    double left = 0.0;
    double right = max_ratio;
    double mid = (left+right) / 2;

    while(right - left > 0.001){
        mid = (left+right) / 2;
        finalp = 0;
        finalw = 0;
        sort(arr.begin(), arr.end(), [&](const pair<pair<int,int>, pair<int,int> > &e1, const pair<pair<int,int>, pair<int,int> > &e2){
            return (double(e1.second.first)-mid*double(e1.second.second) > double(e2.second.first)-mid*double(e2.second.second));
        });


        if(kruskalMST(V, E, arr, mid, finalp, finalw) > 0){
            left = mid;
        }
        else{
            right = mid;
        }
        
    }

	cout << mid << '\n';
    int k = __gcd(finalp,finalw);
    double temp = double(finalp)/double(finalw);

    cout << finalp/k << ' ' << finalw/k << '\n';
    
    return 0;
    

} 
