#include<iostream>
#include<queue>
using namespace std;
struct cmp{
    bool operator ()(int x,int y){
        return x>y;
    }
};
int main(){
    priority_queue<int,vector<int>,cmp>q;
    q.push(11);
    q.push(22);
    q.push(33);
    q.push(44);
    cout<<q.top()<<endl;
}