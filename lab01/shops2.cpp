
#include <iostream>  
#include <bits/stdc++.h>  
using namespace std;  
  
  
unordered_multimap <int,pair<int,int>> Sets;  
int buildings[20000];  
set <long> res;  
long N,K;  
  
  
void preprocess (int N){  
    for (int i = 0; i<N; i++){  
        int sum = 0;  
        for (int j = i; j<N; j++){  
  
            sum += buildings[j];  
              
            Sets.insert (pair<int,pair<int,int>>(sum, make_pair(i,j)));  
        }  
    }  
}  

int Search(int n){  
          
 
        unordered_multimap<int,pair<int,int>> :: iterator itr;  
        for( itr = Sets.begin(); itr!= Sets.end(); itr++ ){  
  
            if (itr->first == K) {res.insert( itr->second.second - itr->second.first +1); ;}  

            auto range = Sets.equal_range(K-itr->first);  
            if (range.first != range.second){  
               
                for(auto i = range.first; i != range.second; i++){  

                    if (i->second.first > itr->second.second || itr->second.first > i->second.second){  
  
                        res.insert(itr->second.second - itr->second.first + i->second.second - i->second.first +2);  

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
  
    int r;  

        r = Search(1) ;  

  
    if (*res.begin() == 0) cout << -1 <<'\n';  
    else  
    cout << *res.begin() <<'\n';  

  
}  