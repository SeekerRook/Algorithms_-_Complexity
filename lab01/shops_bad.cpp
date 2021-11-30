// This code is worse complexity than the other one submitted, but the other has a bug I could not find in time for the deadline.
#include <iostream>  
#include <bits/stdc++.h>  

using namespace std;  
  
unordered_multimap <int,pair<int,int>> Sets [20000];  
int buildings[20000];  
  
long N,K;  
  
void preprocess (int N){  
    for (int i = 0; i<N; i++){  
        int sum = 0;  
        for (int j = i; j<N; j++){  
  
            sum += buildings[j];  
              
            Sets[j-i].insert (pair<int,pair<int,int>>(sum, make_pair(i,j)));  
        }  
    }  
}  
  
int Search(int n){  
  
        for (int i = 0; i<n; i++){  
         //   cout << i << "\n";  
        unordered_multimap<int,pair<int,int>> :: iterator itr;  
        for( itr = Sets[i].begin(); itr!= Sets[i].end(); itr++ ){  
  
            if (itr->first == K) return itr->second.second - itr->second.first +1;  
            unordered_multimap<int,pair<int,int>> :: iterator f = Sets[n-i-1].find(K - itr->first) ;  
            if( f != Sets[n-i-1].end()){  
                if (f->second.first > itr->second.second ) {  
                    return itr->second.second - itr->second.first + f->second.second - f->second.first +2;  
                }  
            }  
        }  
  
    }  
    return -1;  
}  
int main(){  
     cin >> N >> K ;  
  
    for(int i = 0; i < N; i++){  
        cin >> buildings[i];  
    }  
    preprocess(N);  
  
    int res;  
    for (int i = 1 ; i<= N; i++){  
        res = Search(i) ;  
        if (res != -1)break;  
    }  
  
      
    cout << res <<'\n';  
  
}  