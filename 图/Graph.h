//
// Created by HONOR on 2020/10/12.
//

#ifndef TEST1_GRAPH_H
#define TEST1_GRAPH_H

#include<string>
#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Graph{
protected:
    int nv;
    bool directed ;
    vector<string>vertices;
    map<string,int>iov;
public:
    Graph(bool dir = false){
        directed=false ;
        nv=0;
    }
    Graph(vector<string>v,bool dir = false){
        directed=dir;
        nv=(int)v.size();
        vertices = v;
        for(int i=0;i<nv;i++){
            iov[v[i]]=i;
        }
    }
    Graph(int n,bool dir = false){
        directed=dir ;
        nv=n;
        vertices.resize(n);
        for(int i=0;i<n;i++){
            vertices[i]=to_string(i);
            iov[to_string(i)]=i;
        }
    }
    virtual void print()=0;
    virtual void insertV(){insertV(to_string(nv));}
    virtual bool insertV(string v);
};

//int main(){
//    vector<string>v={"AA","BB","CC","DD","EE"};
//    Graph g(10);
//    g.test();
//    return 0;
//}


#endif //TEST1_GRAPH_H
