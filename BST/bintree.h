#ifndef bintree_h
#define bintree_h
#include<iostream>
#include<stack>
using namespace std;
// template<class T>
// struct BinNode{
//     T data ;
//     BinNode<T>*left ;
//     BinNode<T>*right ;
//     BinNode(T x){
//         data=x;
//         left = right = NULL;
//     }
// };
template<class T>
struct Node{
    T data ;
    int h=0;
    Node<T>*left ;
    Node<T>*right ;
    int time = 0 ;
    Node(T x){
        data=x;
        left = right =NULL;
    }
};
template<class T>
class BinTree{
protected:
    Node<T>* root ;
    void rpreprint(Node<T>*r){
        if(r==NULL) return ;
        cout<<r->data<<' ';
        rpreprint(r->left);
        rpreprint(r->right);
    }
    Node<T>* rfind(T x,Node<T>*r){
        if(!r) return NULL;
        if(r->data==x) return r;
        Node<T>* found;
        found=rfind(x,r->left);
        return found? found:rfind(x,r->right);
    }
    void rprint(Node<T>*r,int depth){
        for(int i=0;i<depth;i++) cout<<"  ";
        if(!r){
            cout<<"[/]"<<endl;
            return ;
        }
        cout<<r->data<<endl;
        rprint(r->left,depth+1);
        rprint(r->right,depth+1);
    }
    void rinprint(Node<T>*r){
        if(r==NULL) return ;
        rinprint(r->left);
        cout<<r->data<<' ';
        rinprint(r->right);
    }
    void ipreprint(Node<T>*r){
        stack<Node<T>*>st;
        if(r==NULL) return;
        // while(r!=NULL){
        //     cout<<r->data<<" ";
        //     st.push(r);
        //     r=r->left;
        //     while(r==NULL&&!st.empty()){
        //         r=st.top();
        //         st.pop();
        //         r=r->right; 
        //     }
        // }

        while(r!=NULL||!st.empty()){
            //左路径
            while(r!=NULL){
                cout<<r->data<<" ";
                st.push(r);
                r=r->left;
            }
            if(!st.empty()){
                r=st.top()->right ;
                st.pop();
            }
        }

    }
    
    void iinprint(Node<T>*r){
        stack<Node<T>*>st;
        if(r==NULL) return;
        // while(r!=NULL){
        //     // cout<<r->data<<" ";
        //     st.push(r);
        //     r=r->left;
        //     while(r==NULL&&!st.empty()){
        //         r=st.top();
        //         st.pop();
        //         cout<<r->data<<" ";
        //         r=r->right; 
        //     }
        // }

        while(r!=NULL||!st.empty()){
            //左路径
            while(r!=NULL){
                st.push(r);
                r=r->left;
            }
            if(!st.empty()){
                r=st.top()->right ;
                cout<<(st.top())->data<<" ";
                st.pop();
            }
        }
    }
    void ipostprint(Node<T>*r){
        stack<Node<T>*>st;
        if(r==NULL) return;
        while(r!=NULL||!st.empty()){
            while(r!=NULL){
                st.push(r);
                st.top()->time++;
                r=r->left;
            }
            if(!st.empty()){
                if(st.top()->time==2){
                    cout<<st.top()->data<<" ";
                    st.pop();
                }else{
                    st.top()->time++;
                    r=st.top()->right; 
                }
            }
           
                
        }

    }
    
    int countLeaves(Node<T>*r){
        if(r==NULL) return 0;
        if(r->left==NULL&&r->right==NULL) return 1;
        else return countLeaves(r->left) + countLeaves(r->right);
    }
public:
    BinTree(){root=NULL;}
    BinTree(T r){
        root = new Node<T>(r);
    }
    ~BinTree(){}
    void preprint(){
        // rpreprint(root);
        ipreprint(root);//iter迭代
        cout<<endl;
        iinprint(root);
        cout<<endl;
    }
    Node<T>* findX(T x){
        return rfind(x,root);
    }
    bool insert(T p,int LorR,T x){
        Node<T>*found;
        found=findX(p);
        if(!found) return false ;
        if(LorR==0){
            if(found->left!=NULL) return false ;
            found->left=new Node<T>(x);
        }else{
            if(found->right!=NULL) return false ;
            found->right=new Node<T>(x);
        }
        return true;
    }
    void print(){
        rprint(root,0);
    }
    void inprint(){
        rinprint(root);
    }
    void postprint(){
        ipostprint(root);
    }
    int count(){
        return countLeaves(root);
    }
};



#endif