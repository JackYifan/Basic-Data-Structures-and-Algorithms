#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int>v;
    v.push_back(11);
    v.push_back(22);
    v.push_back(33);
    v.insert(v.begin(),666);
    v.insert(v.begin()+2,777);
    v.erase(v.begin()+1);
    for(int i:v){
        cout<<i<<" ";
    }
}