//
// Created by HONOR on 2020/10/12.
//
#include "Graph.h"
//void Graph::test(){
//    for(auto x: vertices){cout<<x<<",";}
//    cout<<endl;
//    for(auto x:iov) cout<<x.first<<"->"<<x.second<<"; ";
//}
bool Graph::insertV(string v) {
    if(iov.find(v)!=iov.end()) return false ;
    vertices.push_back(v);
    iov[v]=nv++;
    return true;
}
