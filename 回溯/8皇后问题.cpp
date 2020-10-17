#include<iostream>
#include<vector>
using namespace std;
const int N=8;
vector<int>queens(N,0);//皇后的列数
bool can_place(int k,int i){
    for(int j=0;j<k;j++){
        if(queens[j]==i||queens[j]-i==j-k||queens[j]-i==k-j) return false ;
    }
    return true ;
}
int cnt=0;
void place(int k){
    if(k==N){
        cnt++;
        cout<<cnt<<" ";
        for(int i=0;i<queens.size();i++){
            cout<<queens[i]<<" ";
        }
        cout<<endl;
    }
    else{
        for(int i=0;i<N;i++){
            if(can_place(k,i)){
                queens[k]=i;
                place(k+1);
            }
        }
    }
}
int main(){
    place(0);
}