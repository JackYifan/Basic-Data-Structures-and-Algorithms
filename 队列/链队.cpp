#include<iostream>
using namespace std;
struct Node{
    int data;
    Node*next;
    Node(int x){
        data=x;
        next=NULL;
    }
};
class Queue{
private:
    Node*front ;
    Node*rear ;
public:
    Queue(){
        front=rear=NULL;
    }
    ~Queue(){
        Node*temp;
        while(front){
            temp=front;
            front=front->next;
            delete temp ;
        }
    }
    bool isEmpty(){
        return front==NULL;
    }
    void enQueue(int x){
        Node*temp;
        temp=new Node(x);
        if(isEmpty()){
            front=rear=temp;
        }else{
            rear->next=temp;
            rear=rear->next;
        }
    }
    bool deQueue(int *px){
        if(isEmpty()) return false ;
        else{
            *px=front->data;
            Node*temp=front;
            front=front->next;
            delete temp; 
            if(front==NULL) rear=NULL;
            return true;
        }
    }
};
int main(){
    Queue q;
    q.enQueue(11);
    q.enQueue(22);
    q.enQueue(33);
    q.enQueue(44);
    int x;
    q.deQueue(&x);
    cout<<x<<endl;
    q.deQueue(&x);
    cout<<x<<endl;
    q.deQueue(&x);
    cout<<x<<endl;
    q.deQueue(&x);
    cout<<x<<endl;
    return 0;
}