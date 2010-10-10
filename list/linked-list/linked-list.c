#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *next;
    int data;
}NODE;

typedef struct list{
    NODE *next;
    long long size;
    short empty;
}LIST;

LIST* create_list(){
    LIST *l = malloc(sizeof(LIST));
    if(l == NULL)
        return l;
    l->next = NULL;
    l->size = 0;
    l->empty = 1;

    return l;
}

NODE* append(LIST* l, int data){
    NODE *p;
    if(l == NULL)
        return NULL;

    p = malloc(sizeof(NODE));
    if(p == NULL)
        return NULL;

    p->next = l->next;
    l->next = p;
    p->data = data;

    l->size++;
    l->empty = 0;

    return p;
}

void insert(LIST *l, int index){

}

void delete(LIST* l){
    NODE *p;
    if(l == NULL) /*No list*/
        return;

    if(l->next == NULL) /*Empty list*/
        return;

    p = l->next->next;
    free(l->next);
    l->next = p;
    
    l->size--;
    if(l->size == 0)
        l->empty = 1;
}

NODE* search(LIST* l, int key){
    NODE *p;
    if(l == NULL)
        return NULL;

    p = l->next;
    while(p != NULL){
        if(p->data == key)
            return p;
        p = p->next;
    }

    return NULL;
}

void destroy_list(LIST* l){
    NODE *p, *aux;
    if(l == NULL)
        return;

    p = l->next;
    while(p != NULL){
        aux = p->next;
        free(p);
        p = aux;
    }
    free(l);
}

void print_list(LIST *l){
    NODE *p;
    if(l == NULL){
        printf("NULL\n");
        return;
    }

    p = l->next;
    printf("[");
    if(p != NULL){
        printf("%d", p->data);
        p = p->next;
    }
    while(p != NULL){
        printf(", %d", p->data);
        p = p->next;
    }
    printf("]\n\n");
}

void print_pointers(LIST *l){
    NODE *p;
    printf("       LIST        \n");
    if(l == NULL)
        printf("NULL\n");

    p = l->next;
    while(p != NULL){
        printf("%p -> %p\n", p, p->next);
        p = p->next;
    }
    printf("\n");
}

int main(){

    LIST *l = create_list();
    NODE *p;
    if(l == NULL){
        printf("Run out of memory x_x\n");
        return 1;
    }

    print_list(l);

    append(l, 1);
    print_list(l);
   
    append(l, 2);
    print_list(l);
    
    append(l, 3);
    print_list(l);

    p = search(l, 1);
    if( p != NULL )
        p->data = 4;
    print_list(l);

    delete(l);
    print_list(l);
    
    delete(l);
    print_list(l);

    delete(l);
    print_list(l);

    destroy_list(l);
    return 0;
}
