#include<iostream>
#include<set>
#include<map>
using namespace std;
template<class T>
struct DisjointSet{
    int* parent ;
    T* data ;
    int capacity;
    int size ;
    map<T,int>m;
    //从1开始放，0号不放任何元素
    DisjointSet(int max=10){
        capacity=max;
        size = 0;
        parent = new int[max+1];
        data = new T[max+1];
    }
    ~DisjointSet(){
        delete [] parent;
        delete [] data; 
    }
    bool insert(T x){
        if(size == capacity ) return false ;
        data[++size]=x;
        parent[size]=-1;
        m[x]=size ;
        return true; 
    }
    //返回下标
    //如果map中不存在x则会插入<x,0>
    int find(T x){
        typename map<T,int>::iterator it;
        it = m.find(x);
        if(it==m.end()) return -1; 
        int rt;
        rt=it->second;
        while(parent[rt]>0){
            rt=parent[rt];
        }
        int tmp;
        for(int i=m[x];i!=rt;i=tmp){
            tmp=parent[i];
            parent[i]=rt;
        }
        return rt;
    }
    // void unionSet(int r1,int r2){
    //     parent[r2]=r1;
    // }
    void unionSet(T x,T y){
        int rx,ry; 
        rx=find(x);
        ry=find(y);
        if(rx==-1||ry==-1) return; 
        if(rx==ry) return ;
        if(parent[rx]<parent[ry]){
            parent[rx]+=parent[ry];
            parent[ry]=rx;
        }else{
            parent[ry]+=parent[rx];
            parent[rx]=ry;
        }
    }
    void test(){
        unionSet(1,3);
        unionSet(2,4);
        unionSet(4,5);
        print();
        cout<<find(123)<<endl;
    }
    void print(){
        for(int i=1;i<=size;i++){
            cout<<i<<"\t";
        }
        cout<<endl;
        for(int i=1;i<=size;i++){
            cout<<parent[i]<<"\t";
        }
        cout<<endl;
        for(int i=1;i<=size;i++){
            cout<<data[i]<<"\t";
        }
        cout<<endl;
    }
};



int main(){
    DisjointSet<int>s;
    s.insert(11);   
    s.insert(22);  
    s.insert(66);  
    s.insert(-5);
    s.insert(123);
    s.unionSet(11,66);
    s.unionSet(22,11);
    // s.unionSet(11,66);
    s.print();
    return 0;
}