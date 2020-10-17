#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
int main(){
    list<int>a;
    a.push_back(11);
    a.push_back(22);
    a.insert(a.begin(),666);
    if(find(a.begin(),a.end(),666)!=a.end()){cout<<"Found!";}
    for(int i:a){
        cout<<i<<" ";
    }

}