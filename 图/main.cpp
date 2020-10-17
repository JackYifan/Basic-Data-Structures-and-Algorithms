// #include<iostream>
#include"DisjoinSet.h"
#include<queue>
using namespace std;
struct Edge{
    string u;string v; 
    int weight ;
    Edge(string u,string v,int weight){
        this->u=u;
        this->v=v;
        this->weight=weight;
    }
    Edge(){}
    bool operator <(const Edge&e)const{
        return this->weight>e.weight;
    }
};
int main(){
    DisjointSet<string>ds; 
    priority_queue<Edge>q;//默认是大顶堆
    vector<Edge>edges;//树的每一条边
    int nv,ne ,w;
    string u,v;
    cin>>nv;
    for(int i=0;i<nv;i++){
        cin>>u;
        ds.insert(u);
    }
    cin>>ne;
    for(int i=0;i<ne;i++){
        cin>>u>>v>>w;
        q.emplace(u,v,w);
    }
    int cnt=0,minCost=0;
    Edge e ;
    while(cnt<nv-1&&!q.empty()){
        e=q.top();q.pop();
        if(ds.find(e.u)!=ds.find(e.v)){
            ds.unionSet(e.u,e.v);
            edges.push_back(e);
            minCost+=e.weight;
            cnt++;
        }
    }
    if(cnt!=nv-1) cout<<"Error!"<<endl;
    else{
        cout<<minCost<<endl;
        for(auto x:edges){
            cout<<x.u<<","<<x.v<<"("<<x.weight<<")"<<endl;
        }
    }

    return 0;
}
/*
7
A B C D E F G
12
A B 2
C A 4
A D 1
B D 3
B E 10
D C 2
D E 7
C F 5
D F 8
D G 4
E G 6
G F 1



*/