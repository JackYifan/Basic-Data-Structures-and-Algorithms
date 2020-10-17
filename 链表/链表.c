#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data; 
    struct Node* next ;
};
typedef struct Node* LList ;
void init(struct Node** phead){
    *phead=NULL;
}
int getLength(struct Node *head){
    int len = 0;
    while(head!=NULL){
        len++;
        head = head->next;
    }
}
void printList(struct Node*head ){
    while(head!=NULL){
        printf("%d ",head->data);
        head=head->next;
    }
}
struct Node* createNode(int x){
    struct Node *t;
    t=(struct Node*)malloc(sizeof(struct Node));
    t->next=NULL;
    t->data=x;
    return t;
}
struct Node* findKth(struct Node* head,int k){
    int cnt = 1;
    struct Node*p=head ;
    while(p!=NULL&&cnt<k){
        cnt++;
        p=p->next;
    }
    return p;
}
int insert(struct Node** phead,int k, int x){
    if(k<1) return 0;
    if(k==1){
        struct Node*t=createNode(x);
        t->next=*phead;
        *phead=t;
        return 1;
    }
    //找到k-1号位置
    struct Node*p;
    p=findKth(*phead,k-1);
    if(p==NULL) return 0;
    struct Node *t;
    t=createNode(x);
    t->next=p->next;
    p->next=t;
    return 1;
    
}
int removeNode(struct Node** phead,int k, int *px){
    if(k<1) return 0;
    else if(k==1){
        if(*phead){
            *px=(*phead)->data;
            *phead=(*phead)->next;
            return 1;
        }else{
            //如果是空链表，显然删除失败
            return 0;
        }
    }else{
        struct Node*p=findKth(*phead,k-1);
        if(p==NULL||p->next==NULL) return 0;
        struct Node*t;
        t=p->next;
        p->next=t->next;
        *px=t->data;
        free(t);
        return 1;
    }
}
int main(){
    struct Node *head;
    init(&head);
    int k=getLength(head);
    
    //printf("%d\n",k);
    int flag = 0;
    flag = insert(&head,1,11);
    // printf("%d",flag);
    insert(&head,1,22);
    int x;
    removeNode(&head,2,&x);
    printList(head);
    return 0;
}