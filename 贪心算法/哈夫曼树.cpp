#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct Node{
    int data;
    Node*left;
    Node*right;
    Node(){left=right=NULL;}
    Node(int data){
        this->data=data;
        left=right=NULL;
    }
};
struct HuffmanTree{
    Node*root ;
    HuffmanTree(){root=NULL;}
    HuffmanTree(int weight){
        root=new Node(weight);
    }
    HuffmanTree(vector<HuffmanTree>&nodes){
        //小顶堆
        priority_queue<HuffmanTree,vector<HuffmanTree>,greater<HuffmanTree>>q(nodes.begin(),nodes.end());
        HuffmanTree tmp;
        for(int i=1;i<nodes.size();i++){
            tmp.root=new Node;
            tmp.root->left=q.top().root;q.pop();
            tmp.root->right=q.top().root;q.pop();
            tmp.root->data=tmp.root->left->data+tmp.root->right->data;
            q.push(tmp);
        }
        root=q.top().root;
    }
    bool operator >(const HuffmanTree& t) const{
        return this->root->data>t.root->data;
    }
    void rprint(Node*r,int depth){
        for(int i=0;i<depth;i++) cout<<"  ";
        if(!r) cout<<"[/]"<<endl;
        else{
            cout<<r->data<<endl;
            rprint(r->left,depth+1);
            rprint(r->right,depth+1);
        }

    }
    void print(){
        rprint(root,0);
    }
};
int main(){
    vector<HuffmanTree>nodes;
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int weight;cin>>weight;
        nodes.emplace_back(weight);
    }
    HuffmanTree ht(nodes);
    ht.print();
    return 0;
}
/*
7
10 15 12 3 4 13 1
*/

