#include <iostream>

using namespace std;

#define MAX_NUM	1000000
int universe[MAX_NUM][3]; // 0 -> morty, 1 -> parent , 2 -> depth 
int portal[MAX_NUM][3];   // 0 , 1 -> universes , 3 -> width

long N, M;
int Find(int i) {
    if (universe[i][1] != i) universe[i][1] = Find(universe[i][1]);
    return universe[i][1] ; 
}

void Union(int i, int j) {
    int par_of_i = Find(i);
    int par_of_j = Find(j);

    if(par_of_i != par_of_j){
        if(universe[par_of_i][1]<universe[par_of_j][1]){
            universe[par_of_i][1] = par_of_j;
            universe[par_of_i][2]++;

        }
        else{
            universe[par_of_j][1] = par_of_i;
            universe[par_of_j][2]++;

        }
    }

}



bool final(){
    for(int i = 1; i < N; i++){
        if(Find(i)!= Find(universe[i][0])){
            return false;
        }
    }
    return true;
}

int Search(int low, int high){
    if (low == high) return high;

    int mid = low + (high - low)/2;
    for (int i = mid;i <= high; i++){
        if(Find(portal[i][0]) != Find(portal[i][1]))  Union(portal[i][0], portal[i][1]);
    }
    if (final()){
        for(int i = 1; i <= N; i++){
            universe[i][1] = i;
            universe[i][2] = 0;
        }
        return Search(mid+1,M);
    }
    else return Search(low,mid);
}

int comp ( const void *p1, const void *p2 )
{
int *q1 = (int *)p1;
int *q2 = (int *)p2;
if ( q1[2] > q2[2] ) { return 1; }
else if ( q1[2] < q2[2] ) { return -1; }
else { return 0; }
}
int main(){
    cin >> N >> M ;
    universe[0][0] = 0;
    universe[0][1] = 0;

    for(int i = 1; i <= N; i++){
        cin >> universe[i][0];
        universe[i][1] = i;
        universe[i][2] = 0;
    }

    for (int i = 0; i < M ; i++){
        cin >> portal[i][0] >> portal[i][1] >> portal[i][2];
    }
  qsort(portal,M,3*sizeof(int),comp);

    int res = Search(0,M);
    cout << portal[res-1][2]<<"\n";

}
