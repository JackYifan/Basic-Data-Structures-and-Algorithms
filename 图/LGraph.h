//
// Created by HONOR on 2020/10/12.
//

#ifndef TEST1_LGRAPH_H
#define TEST1_LGRAPH_H
#include"Graph.h"

class LGraph: public Graph {
protected:
    vector<map<int,int>>adjL;
    void setAdjL();
public:
    LGraph(bool dir= false):Graph(dir){}
    LGraph(vector<string>v,bool dir = false):Graph(v,dir){setAdjL();}
    LGraph(int n,bool dir=false):Graph(n,dir){setAdjL();}
    void print();
    void insertV();
	bool insertV(string v);
};


#endif //TEST1_LGRAPH_H
