#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    /*
                 next
                  |
        ********  v
        * data *------>
        ********

        next: pointer to the next NODE
        data: the data (as an integer in this case)
        all the structure is called NODE
    */
    struct node *next;
    int data;
}NODE;

typedef struct stack{
   /*

         
                 pointer to NODE
                   |
        ********   v
        * size *------>
        ********
        size: The size of the stack
        all the structure is called stack
   */
    int size; /*This doesn't work*/
    NODE *top;
}STACK;

STACK* create_stack(){
    /*
        Here I create a pointer to the stack structure.
        And I inicialize the values.
        Also return NULL in case that is not more memory
        available otherwise return a stack with defaults
        values
    */
    STACK *s = (STACK*) malloc(sizeof(STACK));
    if(s == NULL) /* Not more memory available */
        return s; /* return NULL */
    /* In other case set up the default values */
    s->size = 0; /* No elements in the stack */
    s->top = NULL; /* The top doesn't have any NODE */
    return s; /* Return the stack with default values */
}

int empty(STACK *s){
    /*
        Returns 1 (or True) if the stack is empty
        Returns 0 (or False) if the stack is NOT empty.
    */

    /*If there is no STACK or don't have any NODE*/
    if(s == NULL || s->top == NULL)
        return 1; /* returns True */
    return 0; /* returns False */
}

void push(STACK *s, int data){
    /*
        This function insert a new NODE in the top of the stack
        Example 1: Empty STACK
           Pointer to the top of the stack
                   |                
        *********  v
        * STACK *---->NULL
        *********

        Step 1: Create a new node
           Pointer to the next NODE
                    |
        **********  v
        * NODE_1 *---->
        **********

        Step 2: Put it on the top
        *********     
        * STACK *---->NULL
        *********     

        **********
        * NODE_1 *---->NULL
        **********

        *********     **********
        * STACK *---->* NODE_1 *---->NULL
        *********     **********

        Example 2: Stack N NODES
           Pointer to the top of the stack
                   |                
        *********  v  **********             **********
        * STACK *---->* NODE_N *---->...---->* NODE_1 *---->NULL
        *********     **********             **********

        Step 1: Create a new node
           Pointer to the next NODE
                        |
        **************  v
        * NODE_(N+1) *---->
        **************

        Step 2: Put it on the top
        *********  v  **********             **********
        * STACK *---->* NODE_N *---->...---->* NODE_1 *---->NULL
        *********     **********             **********

        **************     **********
        * NODE_(N+1) *---->* NODE_N *
        **************     **********

        *********     **************     **********             **********
        * STACK *---->* NODE_(N+1) *---->* NODE_N *---->...---->* NODE_1 *---->NULL
        *********     **************     **********             **********

    */

    /* If the stack doesn't exists then stop */
    if(s == NULL)
        return;
    /* Create a NODE and keep the pointer in p */
    NODE *p = (NODE*)malloc(sizeof(NODE));
    if(p == NULL) /* If p is NULL then stop (no more memory available) */
        return;
    /* Put the data in the node */
    p->data = data;
    /* The next element of p is top */
    p->next = s->top;
    /* The new top is now p */
    s->top = p;
}

void pop(STACK *s){
    /* If the stack doesn't exists then stop*/
    if(s == NULL)
        return;
    /*
        *********     **********     **********
        * STACK *---->* NODE_2 *---->* NODE_1 *---->NULL
        *********     **********     **********
        Step 1: Create a pointer P that points to the top of the STACK
        **********     **********
        * NODE_2 *---->* NODE_1 *
        **********     **********
            ^
            |
            |
          *****
          * P *
          *****
        Step 2: The next element of P is the new top.
        *********     **********
        * STACK *---->* NODE_1 *---->NULL
        *********     **********
        Now NODE_2 is not anymore in the stack but it stills in P
        Just free P (aka NODE_2)
        
    */


    /* If the stack is NOT empty */
    if(!empty(s)){
        NODE *p; /* Create a pointer to a NODE */
        p = s->top; /* The top of the STACK is in p */
        s->top = p->next; /* The top of the STACK is now the next element of p */
        free(p); /* Delete the top of the stack */
    }
}

int top(STACK *s){
    /* 
        If STACK is empty just return 0
        otherwise returns the value of the top of STACK
    */
    if(!empty(s))
        return 0;
    return s->top->data;
}

void print_stack(STACK *s){
    /* Just print the STACK in a nice way */
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
    /* Destroy the stack */
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
