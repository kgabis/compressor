//
//  tree.c
//  Compressor
//
//  Created by Krzysztof Gabis on 23.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "bit_operations.h"

Tree_Node_Ptr Tree_Alloc() {
    Tree_Node_Ptr new_node = (Tree_Node_Ptr)malloc(sizeof(Tree_Node));
    assert(new_node != NULL);
    new_node->count = 0;
    new_node->value = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void Tree_Grow(Tree_Node_Ptr tree, unsigned char value) {
    if (tree->count == 0) {
        tree->value = value;
        tree->count++;
        return;
    }
    
    if (value == tree->value) {
        tree->count++;
    } else if (value < tree->value) {
        if (tree->left == NULL) {
            tree->left = Tree_Alloc();
        }
        Tree_Grow(tree->left, value);
    } else if (value > tree->value) {
        if (tree->right == NULL) {
            tree->right = Tree_Alloc();
        }
        Tree_Grow(tree->right, value);
    }
}

void Tree_Dealloc(Tree_Node_Ptr tree) {
    //static int count = 0;
    //printf("freeing count = %d\n", count++);
    if (tree == NULL) {
        return;
    }
    Tree_Dealloc(tree->left);
    Tree_Dealloc(tree->right);
    free(tree);
}

static int Tree_Get_Code_Real(Tree_Node_Ptr tree,
                              unsigned char value,
                              unsigned int code,
                              unsigned int *mask) {
    if (value == tree->value) {
        return code;
    } else if (value < tree->value) {
        if (tree->left == NULL) {
            return -1;
        }
        code = code << 1;
        BIT_CLEAR(code, 0);
        *mask = *mask << 1;
        BIT_SET(*mask, 0);
        return Tree_Get_Code_Real(tree->left, value, code, mask);
        
    } else if (value > tree->value) {
        if (tree->right == NULL) {
            return -1;
        }
        code = code << 1;
        BIT_SET(code, 0);
        *mask = *mask << 1;
        BIT_SET(*mask, 0);
        return Tree_Get_Code_Real(tree->right, value, code, mask);
    }
    return -1;
}

int Tree_Get_Code(Tree_Node_Ptr tree, unsigned char value, unsigned int *mask) {
    return Tree_Get_Code_Real(tree, value, 0, mask);
}

unsigned char Tree_Get_Value(Tree_Node_Ptr tree, unsigned int code, unsigned int mask) {
    if (tree == NULL) {
        return 0;
    }
    
    if (mask == 0) {
        return tree->value;
    } else if (BIT_GET(code, 0)) {
        return Tree_Get_Value(tree->right, code>>1, mask>>1);
    } else {
        return Tree_Get_Value(tree->left, code>>1, mask>>1);
    }
}

void Tree_Print_Real(Tree_Node_Ptr tree, unsigned int depth) {
    int i;
    printf("(%u)", tree->value);
    if (tree->right != NULL) {
        printf("-");
        Tree_Print_Real(tree->right, depth + 1);
    }
    if (tree->left != NULL) {
        printf("\n |");
        if (depth > 0) {
            for (i = 0; i < depth + 1; i++) {
                printf(" ");
            }
            printf("|");
        }
        printf("\n");
        if (depth > 0) {
            printf(" |");
            for (i = 0; i < depth; i++) {
                printf(" ");
            }
        }
            

        Tree_Print_Real(tree->left, depth);
    }
}

void Tree_Print(Tree_Node_Ptr tree) {
    Tree_Print_Real(tree, 0);
}
