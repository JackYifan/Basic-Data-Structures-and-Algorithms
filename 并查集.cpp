#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
#include<set>

using namespace std;
vector<int>father,isRoot;
map<string,int>mp;
map<int,string>itostring;
vector<set<int> >mates;


int findFather(int x){
    int a=x;
    while(x!=father[x]){
        x=father[x];
    }
    while(a!=x){
        father[a]=x;
        a=father[a];
    }
    return x;
}
void Union(int a,int b){
    int faA=findFather(a);
    int faB=findFather(b);
    if(faA!=faB) {
        father[faA]=faB;
        mates[faB].insert(mates[faA].begin(),mates[faA].end());
    }

}


int main(){
    int n;cin>>n;
    father.resize(n);
    isRoot.resize(n);
    mates.resize(n);
    for(int i=0;i<n;i++){
        father[i]=i;
        mates[i].insert(i);
    }
    for(int i=0;i<n;i++){
        string name ;cin>>name;
        mp[name]=i;
        itostring[i]=name;
    }
    int m;cin>>m;
    for(int i=0;i<m;i++){
        string a,b;
        cin>>a>>b;
        Union(mp[a],mp[b]);
    }
    
    for(int i=0;i<n;i++){
        isRoot[findFather(i)]++;
    }
    int maxn=0;
    int cnt=0;
    int index=0;
    for(int i=0;i<n;i++){
        if(isRoot[i]!=0){
            if(isRoot[i]>maxn){
                maxn=isRoot[i];
                index=i;
                cnt++;
            }
        }
    }
    for(auto x:mates[index]){
        cout<<itostring[x]<<" ";
    }
    // cout<<endl;
    // cout<<cnt<<" "<<maxn<<endl;

    
}