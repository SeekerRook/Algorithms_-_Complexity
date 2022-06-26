#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>

using namespace std;

#define dk_max 10001
#define sj_max 1000000001




int N, dk = dk_max;
long Q;
 vector<long> dist, query(dk_max, -1);
 set< pair<long,int>> front;

void Dijkstra() {
    while(!front.empty()) {

         pair<long,int> head = *front.begin();
        long cur = head.second;
        int d_sum = head.first;
        front.erase(head);

        for(auto di : dist) {
            int new_node = (cur+di) % dk;
            int new_dist = d_sum + di;

            if(new_dist < query[new_node] || query[new_node] == -1) {
                front.erase(  make_pair( query[new_node], new_node ) );
                query[new_node] = new_dist;
                front.insert(  make_pair( query[new_node], new_node ) );
            }
        }
    }
}

int main() {
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        long di;
        cin >> di;
        dist.push_back(di);
        if(di < dk)
            dk = di;
    }

    query[0] = 0;
    front.insert(  make_pair(query[0],0) );
    Dijkstra();
    
    for(int i = 0; i < Q; i++) {
        long q;
        cin >> q ;
        (query[q % dk] > q) ? printf("NO\n") : printf("YES\n");
    }
}


