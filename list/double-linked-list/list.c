#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *next;
    struct node *prev;
    int data;
}NODE;

typedef struct list{
    NODE *first;
    NODE *last;
    unsigned long long size;
}LIST;

/*Create a list, return NULL if not posible*/
LIST *create_list(){
    LIST *l = malloc(sizeof(LIST));
    if(l == NULL)
        return l;
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

/*
    Add a node at the beging of the list
    Return 0 -> Successful
    Return 1 -> List is NULL
    Return 2 -> Run out of memory
*/
int append(LIST *l, int data){
    if(l == NULL)
        return 1;

    NODE *p = malloc(sizeof(NODE));
    if(p == NULL)
        return 2;
    p->data = data;
    
    if(l->first == NULL){
        l->first = p;
        l->last = p;

        p->next = p;
        p->prev = p;
    }
    else{
        p->next = l->first;
        p->prev = l->last;

        l->first->prev = p;
        l->last->next = p;

        l->first = p;
    }
    return 0;
}

/*
    Remove the first node of the list
    Return 0 -> Successful
    Return 1 -> List is NULL
    Return 2 -> Empty list
*/
int pop(LIST *l){
    if(l == NULL )
        return 1;
    if(l->first == NULL)
        return 2;

    NODE *p;
    if( l->first == l->last ){
        free(l->first);
        l->first = NULL;
        l->last = NULL;
        l->size = 0;
    }
    else{
        p = l->first->next;

        l->last->next = l->first->next;
        l->first->next->prev = l->last;
        
        free(l->first);
        l->size--;

        l->first = p;
    }

    return 0;
}

/*
    print the list fordward
*/
void fordward(LIST *l){
    if(l == NULL){
        printf("NULL\n");
        return;
    }

    if(l->first == NULL){
        printf("Empty\n");
        return;
    }
    else{
        NODE *p = l->first;
        do{
            printf("%d ", p->data);
            p = p->next;
        }while(p != l->first);
        printf("\n");
    }
}

/*
    Print the list backwards
*/
void backward(LIST *l){
    if(l == NULL){
        printf("NULL\n");
        return;
    }

    if(l->last == NULL){
        printf("Empty\n");
        return;
    }
    else{
        NODE *p = l->last;
        do{
            printf("%d ", p->data);
            p = p->prev;
        }while(p != l->last);
        printf("\n");
    }
}

/*
    Seems like destroy the list
*/
void destroy_list(LIST *l){
    if(l == NULL)
        return;
    while(pop(l) != 0);
    free(l);
}

int main(){
    int i;

    LIST *l = create_list();
    for(i = 0; i < 5; i++){
        append(l, i);
        fordward(l);
    }
    destroy_list(l);

    return 0;
}
