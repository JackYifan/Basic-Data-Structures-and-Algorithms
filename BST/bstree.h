#ifndef bstree_h
#define bstree_h


#include<iostream>
#include"bintree.h"
using namespace std;
template<class T>
class BSTree : public BinTree<T>{
protected:
    Node<T>* rfindMax(Node<T>*r){
        if(r->right==NULL) return r; 
        return rfindMax(r->right);//尾递归 
    }
    //返回插入完成后的树根指针
    virtual Node<T>* rinsert(T x,Node<T>*r){
        if(r==NULL){
            r=new Node<T>(x);
            if(!r) throw -1;
        }
        else if(x<r->data) r->left=rinsert(x,r->left);
        else if(x>r->data) r->right=rinsert(x,r->right);
        else throw -2;
        return r;
        // if(r==NULL) return new Node<T>(x);
        // else if(x<r->data) r->left=rinsert(x,r->left);
        // else if(x>r->data) r->right=rinsert(x,r->right);
        // return r;
    }
    Node<T>*remove(T x,Node<T>*r){
        Node<T>*tmp ; 
        if(r==NULL) throw -1 ;
        else{
            if(x<r->data){
                r->left=remove(x,r->left);
            }else if(x>r->data){
                r->right=remove(x,r->right);
            }else{
                if(r->left&&r->right){
                    tmp=rfindMax(r->left);
                    r->data=tmp->data;
                    r->left=remove(tmp->data,r->left);
                }else{
                    //将子节点链接过来
                    tmp=r; 
                    r=r->left?r->left:r->right;
                    delete tmp;
                }
            }
        }
        return r;
    }
public:
    BSTree(){
        this->root=NULL;
    }
    Node<T>* findMax();
    Node<T>* findMin(){
        if(this->root==NULL) return NULL;
        Node<T>*r=this->root;
        while(r->left){
            r=r->left;
        }
        return r;
    }
    Node<T>* findX(T x){
        Node<T>*tmp=this->root;
        while(tmp&&x!=tmp->data){
            // if(x==tmp->data) break; 一开始就break可以写在while里面
            if(x<tmp->data) tmp=tmp->left;
            else tmp=tmp->right; 
        }
        return tmp;
    }
    bool insert(T x){
        try
        {
            this->root=rinsert(x,this->root);
            return true; 
        }
        catch(int e)
        {
            return false ;
        }
    }
    bool remove(T x){
        try
        {
            this->root=remove(x,this->root);
            return true; 
        }
        catch(int e)
        {
            return false ;
        }
    }
};
template<class T>
Node<T>* BSTree<T>::findMax(){
    // return rfindMax(this->root);
    if(this->root==NULL) return NULL;
    Node<T>*r=this->root ;
    //如果r==NULL 第二项不会去求解，就不会空指针 while(r&&r->right!=NULL)
    while(r->right!=NULL){
        r=r->right;
    }
    return r;
    
}
// int main(){
//     BSTree<int>bt;
//     bt.insert(10);
//     bt.insert(5);
//     bt.insert(20);
//     bt.insert(8);
//     bt.insert(15);
//     bt.insert(2);
//     bt.insert(6);
//     bt.print();
//     // cout<<bt.findMax()->data<<endl;
//     // cout<<bt.findMin()->data<<endl;
//     // cout<<bt.findX(6)->data<<endl;
//     // cout<<bt.findX(66)<<endl;
//     cout<<"-----------------"<<endl;
//     bt.remove(10);
//     bt.print();
// }

#endif