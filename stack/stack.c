#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *next;
    int data;
}NODE;

typedef struct stack{
    int size;
    NODE *top;
}STACK;

STACK* create_stack(){
    STACK *s = (STACK*) malloc(sizeof(STACK));
    if(s == NULL)
        return s;
    s->size = 0;
    s->top = NULL;
    return s;
}

int empty(STACK *s){
    if(s == NULL || s->top == NULL)
        return 1;
    return 0;
}

void push(STACK *s, int data){
    if(s == NULL)
        return;
    NODE *p = (NODE*)malloc(sizeof(NODE));
    if(p == NULL)
        return;
    p->data = data;
    p->next = s->top;
    s->top = p;
}

void pop(STACK *s){
    if(s == NULL)
        return;
    if(!empty(s)){
        NODE *p;
        p = s->top;
        s->top = p->next;
        free(p);
    }
}

int top(STACK *s){
    if(s == NULL)
        return 0;
    return s->top->data;
}

void print_stack(STACK *s){
    NODE *p;
    if(s == NULL){
        printf("NULL\n");
        return;
    }

    if(empty(s)){
        printf("[]\n");
        return;
    }
    else{
        printf("[%d", s->top->data);
        for(p = s->top->next; p != NULL; p = p->next)
            printf(" %d", p->data);
        printf("]\n");
    }
}

void destroy_stack(STACK **s){
    if(s == NULL || *s == NULL)
        return;
    
    while(!empty(*s))
        pop(*s);
    free(*s);
    *s = NULL;
}

int main(){

    STACK *s = create_stack();
    int i;
    
    printf("PUSH TIME\n");
    for(i = 0; i < 10; i++){
        print_stack(s);
        push(s, i);
    }

    printf("POP TIME\n");
    while( !empty(s) ){
        print_stack(s);
        pop(s);
    }

    print_stack(s);

    destroy_stack(&s);
    print_stack(s);
    return 0;
}
