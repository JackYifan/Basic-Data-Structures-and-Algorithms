//
// Created by HONOR on 2020/10/12.
//

#include "LGraph.h"

void LGraph::setAdjL() {
    adjL.resize(nv);
    for(auto x:adjL) x.clear();

}

void LGraph::print() {
//    adjL[0].insert(pair<int,int>(1,90));
//    adjL[0].insert(pair<int,int>(2,80));
    for(int i=0;i<nv;i++){
        cout<<vertices[i]<<"["<<i<<"]"<<"-->";
        for(auto x:adjL[i]){
            cout<<vertices[x.first]<<"("<<x.second<<")  ";
        }
        cout<<endl;
    }

}

void LGraph::insertV()
{
	insertV(to_string(nv));
}

bool LGraph::insertV(string v)
{
	bool r = Graph::insertV(v);
	if (!r) return false;
	adjL.push_back(map<int, int>());
	return true;
}
