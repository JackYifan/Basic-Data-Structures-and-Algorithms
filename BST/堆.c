#include<stdio.h>
#include<stdlib.h>
typedef int Elem;
struct heap{
    Elem* data; 
    int capacity ;
    int size ;
};
typedef struct heap* Heap;
Heap initHeap(int max){
    Heap h; 
    h=(Heap)malloc(sizeof(struct heap));
    if(!h) return NULL;
    h->data=(Elem*)malloc(sizeof(Elem)*(max+1));
    if(!h->data) return NULL;
    h->capacity=max;
    h->size=0;
    return h;
}
void printHeap(Heap h){
    for(int i=1;i<=h->size;i++){
        printf("%d ",h->data[i]);
    }
    putchar('\n');
}
int isFull(Heap h){
    return h->capacity==h->size;
}
//上滤 再k号位置的元素上滤
void percolateup(int k,Heap h){
    int x;
    x=h->data[k];
    int i;
    //找到相应的位置
    for(i=k;h->data[i]<h->data[i/2]&&i>1;i/=2){
        h->data[i]=h->data[i/2];
    }
    h->data[i]=x;
}
int insertHeap(Elem x,Heap h){
    if(isFull(h)) return 0;
    h->data[++h->size]=x;
    percolateup(h->size,h);
    return 1;
}
int isEmpty(Heap h){
    return h->size==0;
}
void percolateDown(int k,Heap h){
    Elem x; 
    x=h->data[k];
    int i,child;//child是最小的子节点编号
    for(i=k;i*2<=h->size;i=child){
        child=i*2;
        if(child+1<=h->size&&h->data[child]>h->data[child+1]) child++;
        if(h->data[i]>h->data[child]){
            h->data[i]=h->data[child];
        }else{
            break; 
        }
    }
    h->data[i]=x;

}
int removeHeap(Elem*px,Heap h){
    if(isEmpty(h)) return 0;
    *px=h->data[1];
    h->data[1]=h->data[h->size--];
    percolateDown(1,h);
    return 1;
}
Heap buildHeap(int *a,int size,int max){
    Heap h;
    h=initHeap(max);
    if(!h) return NULL;
    h->size=size; 
    for(int i=1;i<=size;i++){
        h->data[i]=a[i-1];
    }
    // printHeap(h);
    //最后一个有孩子的点size/2
    for(int i=size/2;i>0;i--){
        percolateDown(i,h);
        // printHeap(h);
    }
    return h;
}
int main(){
    // Heap h ;
    // h = initHeap(10);
    // insertHeap(20,h);
    // insertHeap(10,h);
    // insertHeap(5,h);
    // int x;
    // removeHeap(&x,h);
    // printHeap(h);
    // removeHeap(&x,h);
    // printHeap(h);
    int a[6]={10,50,60,5,30,20};
    Heap h;
    h=buildHeap(a,6,50);
    printHeap(h);
}