#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* next;
    int data;
}NODE;

typedef struct queue{
    NODE *back;
    NODE *front;
    int size;
}QUEUE;

QUEUE* create_queue(){
    QUEUE *q = (QUEUE*) malloc(sizeof(QUEUE));
    if(q == NULL)
        return q;
    q->back = NULL;
    q->front = NULL;
    q->size = 0;
    return q;
}

int empty(QUEUE *q){
    if(q == NULL || q->front == NULL)
        return 1;
    return 0;
}

void enqueue(QUEUE *q, int data){
    /*Enqueue in the back*/
    if(q == NULL)
        return;

    NODE *pnew = (NODE*) malloc(sizeof(NODE));
    if(pnew == NULL)
        return;

    pnew->data = data;
    pnew->next = NULL;
    if(q->back == NULL)
        q->front = pnew;
    else
        q->back->next = pnew;
    q->back = pnew;
    q->size++;
}

void dequeue(QUEUE *q){
    /*Dequeue in the front*/
    if(q == NULL || q->front == NULL)
        return;

    NODE *p = q->front;
    q->front = q->front->next;
    free(p);
    q->size--;
}

void print_queue(QUEUE *q){
    if(q == NULL){
        printf("NULL\n");
        return;
    }

    NODE *p;
    if(q->front == NULL)
        printf("[]\n");
    else{
        printf("[%d", q->front->data);
        for(p = q->front->next; p != NULL; p = p->next)
            printf(" %d", p->data);
        printf("]\n");
    }
}

int front(QUEUE *q){
    if(q == NULL || q->front == NULL)
        return 0;
    return q->front->data;
}

int back(QUEUE *q){
    if(q == NULL || q->back == NULL)
        return 0;
    return q->back->data;
}

void destroy_queue(QUEUE **q){
    if( q == NULL || *q == NULL )
        return;

    while( !empty(*q) )
        dequeue(*q);

    free(*q);
    *q = NULL;
}

int main(){
    
    QUEUE *q = create_queue();
    int i;
    printf("ENQUEUE\n");
    for(i = 0; i < 10; i++){
        print_queue(q);
        enqueue(q, i);
    }

    printf("DEQUEUE\n");
    while(!empty(q)){
        print_queue(q);
        dequeue(q);
    }
    print_queue(q);
    
    destroy_queue(&q);
    print_queue(q);

    return 0;
}
