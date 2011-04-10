#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    /*
         pointer to next node
                  |
        ********  v
        * data *---->
        ********
        ^            ^
        |            |
        |    NODE    |
        node: Pointer to the next NODE structure
        data: Integer (in this case)
    */
    struct node* next;
    int data;
}NODE;

typedef struct queue{
    /*

        *********     *********             **********
        * Node1 *---->* Node2 *---->...---->* Node_N *---->NULL
        *********     *********             **********
            ^                                   ^
            |                                   |
          front                               back
        size: N
    */
    NODE *back;
    NODE *front;
    int size;
}QUEUE;

QUEUE* create_queue(){
    /* Create a queue and return a pointer to it */

    /*

        *********************
        *  NULL        NULL *
        *   ^           ^   *
        *   |           |   *
        * front       back  *
        *                   *
        * Size: 0           *
        *********************
        EMPTY QUEUE STRUCTURE
    */
    QUEUE *q = (QUEUE*) malloc(sizeof(QUEUE)); //allocate memory for the QUEUE
    if(q == NULL) //If the pointer is null there isn't have enough memory
        return q; //return NULL

    //If you pointer isn't null then inicialize the QUEUE
    /*
        front --> NULL
        back  --> NULL
        size  =   0
    */
    q->back = NULL;
    q->front = NULL;
    q->size = 0;
    return q;
}

int empty(QUEUE *q){

    /* returns true if the QUEUE q is empty false otherwise */

    //If the queue is invalid or doesn't have items in the front then is empty
    if(q == NULL || q->front == NULL)
        return 1;
    return 0;
}

void enqueue(QUEUE *q, int data){
    /* Add a NODE at the back of the queue */
    if(q == NULL) //If the queue is null then stop
        return;

    NODE *pnew = (NODE*) malloc(sizeof(NODE)); //Allocate a NODE
    if(pnew == NULL) //If pnew (new pointer) is null then stop
        return;

    //Put the data in the node
    pnew->data = data; 
    pnew->next = NULL;
    /*
        **********
        * NODE_1 *---->NULL
        **********
        data: data
    */
    if(q->back == NULL)//If the back is null, then is the first node that will be in the queue, so...
        /*
        Before:
        *********************
        *  NULL        NULL *
        *   ^           ^   *
        *   |           |   *
        * front       back  *
        *                   *
        * Size: 0           *
        *********************
        
        After:
        ************************
        *                      *
        *  **********          *
        *  * NODE_1 *---->NULL *
        *  **********          *
        *  ^       ^           *
        *  |       |           *
        *  front   back        *
        *                      *
        * Size: 1              *
        ************************
        
        */
        q->front = pnew;//Put it in the front
    else
        /*
        Before:
        *****************************************************************
        *                                                               *
        *  **********     **********              **********            *
        *  * NODE_1 *---->* NODE_2 *---->....---->* NODE_N *---->NULL   *
        *  **********     **********              **********            *
        *   ^                                          ^                *
        *   |                                          |                *
        *  front                                      back              *
        *                                                               *
        * Size: N                                                       *
        *****************************************************************

        After:
        ********************************************************************************
        *                                                                              *
        *  **********     **********              **********     ************          *
        *  * NODE_1 *---->* NODE_2 *---->....---->* NODE_N *---->* NODE_N+1 *---->NULL *
        *  **********     **********              **********     ************          *
        *   ^                                                        ^                 *
        *   |                                                        |                 *
        *  front                                                    back               *
        *                                                                              *
        * Size: N + 1                                                                  *
        ********************************************************************************
        */
        q->back->next = pnew;//Otherwise put in the back
    q->back = pnew; //The back is now the new node
    q->size++; //Increment the god damn size of the queue
}

void dequeue(QUEUE *q){
    /* Dequeue in the front */
    if(q == NULL || q->front == NULL)//If the queue is empty then stop
        return;

    NODE *p = q->front; //Keep the front
    q->front = q->front->next; //The new front is the next element
    /*
        Before:
        *****************************************************************
        *                                                               *
        *  **********     **********              **********            *
        *  * NODE_1 *---->* NODE_2 *---->....---->* NODE_N *---->NULL   *
        *  **********     **********              **********            *
        *   ^                                          ^                *
        *   |                                          |                *
        *  front                                      back              *
        *                                                               *
        * Size: N                                                       *
        *****************************************************************

        After:
        *****************************************************************
        *                                                               *
        *  **********     **********              ************          *
        *  * NODE_2 *---->* NODE_3 *---->....---->*  NODE_N  *---->NULL *
        *  **********     **********              ************          *
        *   ^                                           ^               *
        *   |                                           |               *
        *  front                                       back             *
        *                                                               *
        * Size: N - 1                                                   *
        *****************************************************************
    */
    if(q->front == NULL)
    /*
        Before:
        **************************
        *                        *
        *  **********            *
        *  * NODE_1 *---->NULL   *
        *  **********            *
        *   ^      ^             *
        *   |      |             *
        *  front  back           *
        *                        *
        * Size: 1                *
        **************************

        After:
        *********************
        *                   *
        *                   *
        *  NULL     NULL    *
        *                   *
        *   ^        ^      *
        *   |        |      *
        *  front    back    *
        *                   *
        * Size: 0           *
        *********************
    */
        q->back = NULL;
    free(p); //Free the old front
    q->size--; //Decrement the god damn size of the queue
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
