#include<iostream>
#include <algorithm>   
#include <vector>
#include <climits>
using namespace std;
#define MaxL 200000//dont know
int N,K;
int ldsi;
vector<int> salaries,dpu(MaxL, 0),dplu(MaxL, 0),dpb(MaxL, 0),dplb(MaxL, 0),taild(MaxL, 0),D(MaxL,0);


int CeilIndex(vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}
int FloorIndex(vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] <= key)
            r = m;
        else
            l = m;
    }

    return r;
}


int LIS(vector<int>& v)
{   int maxpoint = 0;
    if (v.size() == 0)
        return 0;

    vector<int> tail(v.size(), 0);
    int length = 1; 

    tail[0] = v[0];
    dpu[0]=v[0];
    dplu[0]=1;


    for (size_t i = 1; i < v.size(); i++) {


        if (v[i] < tail[0]){

            tail[0] = v[i];
            dpu[i] = tail[length-1];


        }

        else if (v[i] > tail[length - 1]){
            tail[length++] = v[i];
            dpu[i] = v[i];
            dplu[i]= length;
            maxpoint = i;


        }


        else{

          
            tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];

            dpu[i] = tail[length-1];
            dplu[i]= length;
        }

    }

    ldsi = length;
    return maxpoint;
}


int LDS(vector<int>& v)
{
    if (v.size() == 0)
        return 0;


    int length = 1; 
    int minpoint = 0;
    taild[0] = v[0];
    dpb[0]=v[0];
    dplb[0]=1;

    D[0] = v[0];

    for (size_t i = 1; i < v.size(); i++) {
        D[FloorIndex(D, 0, length, v[i])] = v[i];

        if (v[i] >= taild[0]){
            taild[0] = v[i];
            dpb[i] = taild[length-1];
            dplb[i]= length;

        }


        else if (v[i] < taild[length - 1]){


            taild[length++] = v[i];

            dpb[i] = v[i];
            dplb[i]= length;
            minpoint = i;

        }

        else{


            taild[FloorIndex(taild, -1, length - 1, v[i])] = v[i];
  
            dpb[i] = taild[length-1];
            dplb[i]= length;

            


        }
     if (dpu[N-i-2]>dpb[i] ){

        int t = length;
        while(t >= 0 && i != N - 1&& dpu[N-i-2]> D[t]){
            t--;
        }
        dpb[i]=D[t];
        dplb[i]=t;

     }
    }

    return minpoint;
}

void addk (vector<int>&v,int k){
    for(size_t i = 0; i < v.size(); i++){
        v[i]+=k;
    }
}
 
int main(){

    cin >> N >> K;
    for (int i =0; i< N; i++){
        int tmp;
        cin >> tmp;
        salaries.push_back(tmp);
    }

    int lisp = LIS (salaries);
    addk(salaries,K);
    reverse(salaries.begin(),salaries.end());
    int ldsp = LDS (salaries);
    int maxl = 0;

    for (int i = 0; i < N-1; i++){
        if (dpu[i]<dpb[N-i-2]){
            if (dplu[i]+dplb[N-i-2] > maxl){
                maxl = dplu[i]+dplb[N-i-2];
            }
            else maxl = max(maxl,dplu[i]);
        }
        

    }


        cout << max(maxl,dplu[N-1]) << endl;
}