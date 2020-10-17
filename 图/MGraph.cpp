//
// Created by HONOR on 2020/10/12.
//

#include "MGraph.h"
#include <limits.h>
void MGraph::setAdjM() {
    adjM.resize(nv);
    for(int i=0;i<nv;i++){
        adjM[i].resize(nv);
        for(int j=0;j<nv;j++){
            adjM[i][j]=INT_MAX;
        }
    }


}

void MGraph::print() {
    cout<<"\t";
    for(int i=0;i<nv;i++)   cout<<vertices[i]<<"\t";
    cout<<endl;
    for(int i=0;i<nv;i++){
        cout<<vertices[i]<<":\t";
        for(int j=0;j<nv;j++){
            if(adjM[i][j]==INT_MAX) cout<<"-\t";
            else cout<<adjM[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

void MGraph::insertV() {
    insertV(to_string(nv));
}

bool MGraph::insertV(string v) {
    bool r = Graph::insertV(v);
    if(!r) return false ;
    for(int i=0;i<nv-1;i++){
        adjM[i].push_back(INT_MAX);
    }
    adjM.push_back(vector<int>(nv,INT_MAX));

    return true;
}
