#include <stdio.h>
#include <iostream>
using namespace std;

bool recalculate_mid(int stock[], int &N, int &K, int &median){
    int prefix[N];                                                             //in this function we use prefix sum method. We use -1 if for number smaller than mid and 1 for bigger(or equal)
    for(int i = 0; i < N; i++){                                                //That way if a prefix sum of an element(we make sure at least K subarray) is more than 0 then it is a likely candidate(or a number bigger than this)
        if(stock[i] >= median){
            prefix[i] = 1;
        }
        else{
            prefix[i] = -1;
        }
        if(i > 0){
            prefix[i] += prefix[i-1];
        }
    } 
    int max_dif = prefix[K-1];
    int min_dif = 0;
    
    for(int i = K; i < N; i++){
        min_dif = min(min_dif, prefix[i-K]);
        max_dif = max(max_dif, prefix[i] - min_dif);
    }
    if(max_dif > 0){
        return true;
    }
    return false;
}


int findMedian(int stock[], int &N, int &K){        
    int left = 1;                                              //we use binary search algorithm to determine the largest median
    int right = N+1;                                           //begin by taking the middlemost element in the array and call
    int max_median = -1;                                       //a function to check where the median is going to be located(left or right) 
                                                               //so after we shift the search field we go until it left surpasses right 
    while(left <= right){
        int mid = (left+right)/2;
        if(recalculate_mid(stock, N, K, mid)){
            max_median = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return max_median;
}


int main(){
    int N,K;
    cin >> N >> K;
    int *c = new int[N];                     //get N,K then for loop to fill c (stock values)
    for(int i = 0; i < N; i++){             
        cin >> c[i];
    }

    cout << findMedian(c, N, K) << '\n'; 
    delete []c;
    return 0;
  
}