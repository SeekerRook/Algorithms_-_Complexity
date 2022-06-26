#include <iostream>
#include <vector>
using namespace std;
#define MaxPrice 999999999

const int Nmax = 5001;
const int Mmax = 5001;//1500

struct offer {
    int quantity;
    int price;
};
// void print_offer(offer off){
//     cout << "######\n" << off.seller <<'\n'<< off.type<<'\n'<<off.price<< off.price<<"\n#####\n";
// }

int N/*# of required sets*/, M/*# offers*/;
vector <offer> A1, B1, C1, A2, B2, C2, A3, B3, C3;
int A[Nmax] = {0},B[Nmax] = {0},C[Nmax] = {0};



void knapsack (int* dp, vector <offer> In){//Ο(N*In.size)
    // static int dp [Nmax] = {0};    
    int totalQ = 0;
    for (int i = 1; i <= N; i++) dp[i] = MaxPrice;

    for (unsigned long i = 0; i < In.size(); i++){
        int currQ = In[i].quantity, currP= In[i].price;
        totalQ += currQ;
        for (int j = min(N, totalQ); j >= 1; j--) 
            dp[j] = min(dp[j], dp[max(j - currQ, 0)] + currP);
    }


    // return dp;
}
void Complete_Sets(int Set[],int*A,int*B,int*C){//O(N)
    // static int Set [Nmax]= {0};
    for (int i = 0; i<= N; i++){
        if(A[i]==MaxPrice || B[i]==MaxPrice || C[i] == MaxPrice)Set[i]=MaxPrice;
        else Set[i] = A[i]+B[i]+C[i];
    }
   // return Set;
}
int combine(int Set1[], int Set2[], int Set3[]){//O(N^2)
    int min_price = MaxPrice;
    for (int i = 0; i <= N ; i++){

        for (int j = N-i;j>=0;j--){
            // cout << min_price<< '\n';

             if (Set1[i] == MaxPrice || Set2[j] == MaxPrice || Set3[N - j - i] == MaxPrice) continue;
             if (min_price > Set1[i] + Set2[j] + Set3[N - j - i]) min_price = Set1[i] + Set2[j] + Set3[N - j - i];
        }
    }
    return min_price;
}
// void print_v(vector<offer>V){
//    for (int i = 0; i < V.size(); i++ )cout<< "q: " << V[i].quantity<<" p: "<<V[i].price << "\n";
// 
// 
// }
void print_set(int Set[]){
    for (int i = 0; i < N; i++) (Set[i]==MaxPrice)?cout<<".":cout<< Set[i] << ",";
    cout << "\n\n\n";
}
int main(){


    cin >> N >> M;
    for (int i = 0; i < M; i++){
        string id;
        cin >> id;
        offer val;
        cin >> val.quantity >> val.price;
        switch (id[0]) {
            case '1':
                switch (id[1]){
                    case 'A':
                        A1.push_back(val);
                        break;
                    case 'B':
                        B1.push_back(val);
                        break;

                    case 'C':
                        C1.push_back(val);
                        break;

                }
                break;
            
            case '2':
                switch (id[1]){
                    case 'A':
                        A2.push_back(val);
                        break;
                    case 'B':
                        B2.push_back(val);
                        break;

                    case 'C':
                        C2.push_back(val);
                        break;

                }
                break;

            case '3':
                switch (id[1]){
                    case 'A':
                        A3.push_back(val);
                        break;
                    case 'B':
                        B3.push_back(val);
                        break;

                    case 'C':
                        C3.push_back(val);
                        break;

                }
                break;

        }

    }
    // int A[Nmax],B[Nmax],C[Nmax];
        
    
    // print_v(A1);
    // print_v(B1);
    // print_v(C1);
    // print_v(A2);
    // print_v(B2);
    // print_v(C2);
    // print_v(A3);
    // print_v(B3);
    // print_v(C3);

int Set1[Nmax] = {0},Set2[Nmax]= {0},Set3[Nmax]= {0}; 
   knapsack(A,A1);
   knapsack(B,B1);
   knapsack(C,C1);
   Complete_Sets(Set1,A,B,C); 
    // for (int i = 0; i < N;i++){
    //     cout << A[i]<< "\n";
    // }
   knapsack(A,A2);
   knapsack(B,B2);
   knapsack(C,C2);
Complete_Sets(Set2,A,B,C); 

   knapsack(A,A3);
   knapsack(B,B3);
   knapsack(C,C3);
   Complete_Sets(Set3,A,B,C); 
// print_set(Set1);
// print_set(Set2);

// print_set(Set3);



    int minprice = combine(Set1,Set2,Set3);

    if (minprice == MaxPrice)
    cout << "-1\n";
    else cout << minprice<<'\n';


}