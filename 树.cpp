#include<iostream>
#include<stack>
using namespace std;
template<class T>
struct Node{
    T data ;
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
        countLeaves(root);
    }
};
int main(){
    // BinTree<int>bt(11);
    // bt.insert(11,0,22);
    // bt.insert(11,1,33);
    // // bt.preprint();
    // // bt.print();
    // bt.preprint();
    // bt.postprint();
    
    // cout<<"end"<<endl;
    string name;
    cin>>name ;
    BinTree<string>bt(name);
    cin>>name;
    while(name!="-"){
        string lc,rc;
        cin>>lc>>rc;
        if(lc!="-") bt.insert(name,0,lc);
        if(rc!="-") bt.insert(name,1,rc);
        cin>>name ;
    }
    cout<<"Amount: "<<bt.count()<<endl;


}
/*
Ann
Ann Bill Chris
Bill Daisy Ellen
Chris - Flin
Daisy - -
Ellen Grace Henry
Flin - -
Grace - -
Henry - -
-
*/