//
// Created by HONOR on 2020/10/12.
//

#ifndef TEST1_MGRAPH_H
#define TEST1_MGRAPH_H
#include"Graph.h"
#include<vector>
using namespace std;
class MGraph :public Graph{
protected:
    vector<vector<int>> adjM;
    void setAdjM();
public:
    MGraph(bool dir= false) : Graph(dir){}
    MGraph(vector<string> v,bool dir = false):Graph(v,dir){setAdjM();}
    MGraph(int n,bool dir=false):Graph(n,dir){setAdjM();}
    void print();
    void insertV() ;
    bool insertV(string v) ;

};


#endif //TEST1_MGRAPH_H
