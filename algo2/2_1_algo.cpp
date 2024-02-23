#include <iostream>
#include <vector>

using namespace std;


int main(){
    
    int n,k;
    cin >> n >> k;
    vector<int> chocolate;
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        chocolate.push_back(temp);
    }
    if(n == 1){
        cout << 0 << '\n';
        return 0;
    }

    if(2*k > chocolate.size()){
        int max_profit = 0;
        for(int i = 1; i < chocolate.size(); i++){
            max_profit += max(0, chocolate[i]-chocolate[i-1]);
        }
        cout << max_profit << '\n';
        return 0;
    }

    vector< vector<int> > arr(chocolate.size()+1, vector<int>(k+1));

    for(int i = 0; i <= n; i++){
        arr[i][0] = 0;
    }

    for(int i=1; i <= k; i++){
        arr[n-1][i] = 0;
        arr[n][i] = 0;
    }

    for(int i = 1; i <= k; i++){
        int l = 0; 
        int max_i = arr[n-1][i];
        int temp = chocolate[n-1] + arr[n][i-1];

        for(int z = n-2; z >= 0; z--){
            l = max(l, max(max_i, temp - chocolate[z]));
            max_i = max(max_i, arr[z][i]);
            temp = max(temp, chocolate[z] + arr[z+1][i-1]);

            arr[z][i] = l;
        }
    }

    cout << arr[0][k] << '\n';

    return 0;

}
