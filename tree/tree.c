#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *left;
    struct node *right;
    int data;
}NODE;

typedef struct tree{
    NODE *root;
}TREE;

TREE* create_tree(){
    TREE *t = (TREE*) malloc(sizeof(TREE));
    if(t == NULL)
        return t;
    t->root = NULL;
    return t;
}

void add(NODE *root, NODE *p){
    if(root->data > p->data){
        if(root->left == NULL)
            root->left = p;
        else
            add(root->left, p);
    }
    else if(root->data < p->data){
        if(root->right == NULL)
            root->right = p;
        else
            add(root->right, p);
    }
}

void add_node(TREE *t, int value){
    if(t == NULL)
        return;
    
    NODE *p = (NODE*)malloc(sizeof(NODE));
    if(p == NULL)
        return;
    p->left = p->right = NULL;
    p->data = value;

    if(t->root == NULL)
        t->root = p;
    else
        add(t->root, p);
    
}

void pre(NODE *root){
    if(root != NULL){
        printf("%d ", root->data);
        pre(root->left);
        pre(root->right);
    }
}

void pre_orden(TREE *t){
    if(t == NULL){
        printf("NULL\n");
        return;
    }
    printf("{");
    pre(t->root);
    printf("}");
    printf("\n");
}

void in(NODE *root){
    if(root != NULL){
        in(root->left);
        printf("%d ", root->data);
        in(root->right);
    }
}

void in_orden(TREE *t){
    if(t == NULL){
        printf("NULL\n");
        return;
    }

    printf("{");
    in(t->root);
    printf("}");
    printf("\n");
}

void post(NODE *root){
    if(root != NULL){
        post(root->left);
        post(root->right);
        printf("%d ",root->data);
    }
}

void post_orden(TREE *t){
    if(t == NULL){
        printf("NULL\n");
        return;
    }
    printf("{");
    post(t->root);
    printf("}");
    printf("\n");
}

void min(NODE *root){
    if(root == NULL){
        printf("Empty\n");
        return;
    }

    if(root->left == NULL)
       printf("Min = %d\n", root->data);
    else
        min(root->left);
}

void min_value(TREE *t){
    if(t == NULL){
        printf("NULL\n");
        return;
    }

    min(t->root);
}

void max(NODE *root){
    if(root == NULL){
        printf("Empty\n");
        return;
    }

    if(root->right == NULL)
        printf("Max = %d\n", root->data);
    else
        max(root->right);
}

void max_value(TREE *t){
    if(t == NULL){
        printf("NULL\n");
        return;
    }
    max(t->root);
}
void destroy(NODE *root){
    if(root != NULL){
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}

void destroy_tree(TREE* t){
    if(t == NULL)
        return;
    destroy(t->root);
    free(t);
}

int main(){

    TREE *t;
    t = create_tree();
    add_node(t, 4);
    add_node(t, 3);
    add_node(t, 9);
    add_node(t, 5);
    add_node(t, 8);
    add_node(t, 2);
    add_node(t, 0);
    add_node(t, 6);
    add_node(t, 7);
    add_node(t, 1);

    printf("PREORDEN\n");
    pre_orden(t);

    printf("INORDEN\n");
    in_orden(t);

    printf("POSTORDEN\n");
    post_orden(t);

    min_value(t);
    max_value(t);
    destroy_tree(t);    
    return 0;
}
