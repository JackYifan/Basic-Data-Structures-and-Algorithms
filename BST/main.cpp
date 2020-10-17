#include<iostream>
#include"bstree.h"
#include<algorithm>
using namespace std;

template<class T>
class AVLTree : public BSTree<T>{
protected:
    int height(Node<T>*r){
        if(!r) return -1; 
        return r->h;
    }
    Node<T>* LLrotate(Node<T>* r){
        Node<T>* child ;
        child=r->left;
        r->left=child->right;
        child->right=r;
        r->h=max(height(r->left),height(r->right))+1;
        child->h=max(height(child->left),height(child->right))+1;
        return child;

    }
    Node<T>* RRrotate(Node<T>* r){
        Node<T>*child;
        child=r->right;
        r->right=child->left;
        child->left=r;
        r->h=max(height(r->left),height(r->right))+1;
        child->h=max(height(child->left),height(child->right))+1;
        return child;
    }
    Node<T>* LRrotate(Node<T>* r){
        r->left=RRrotate(r->left);
        r=LLrotate(r);
        return r; 
    }
    Node<T>* RLrotate(Node<T>* r){
        r->right = LLrotate(r->right);
        r = RRrotate(r);
        return r;
    }
    Node<T>* rinsert(T x,Node<T>*r){
        if(r==NULL){
            r=new Node<T>(x);
            if(!r) throw -1;
        }
        else if(x<r->data) {
            r->left=rinsert(x,r->left);
            if(height(r->left)-height(r->right)==2){
                if(x<r->left->data) r=LLrotate(r);
                else r=LRrotate(r);
            }
        }
        else if(x>r->data){
            r->right=rinsert(x,r->right);
            if(height(r->right)-height(r->left)==2){
                if(x>r->right->data) r=RRrotate(r);
                else r=RLrotate(r);
            }
        } 
        else throw -2;
        //插入完成后计算高度
        r->h=max(height(r->left),height(r->right))+1;
        //递归，当r==NULL时候 h=0
        return r;
    }
public:
    AVLTree(){
        this->root=NULL;
    }
};
int main(){
    AVLTree<int>t;
    t.insert(30);
    t.insert(20);
    t.print();
    t.insert(10);
    t.print();
    return 0;
}