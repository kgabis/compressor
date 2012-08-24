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

int compare_nodes(const void *a, const void *b) {
    Tree_Node_Ptr tna = (Tree_Node_Ptr)a;
    Tree_Node_Ptr tnb = (Tree_Node_Ptr)b;
    return tna->count > tnb->count;
}

Tree_Node_Ptr tree_branch_init(Tree_Node_Ptr root) {
    Tree_Node_Ptr new_node = (Tree_Node_Ptr)malloc(sizeof(Tree_Node));
    new_node->root = root;
    new_node->count = 0;
    new_node->type = TNTBranch;
    new_node->value.children[0] = NULL;
    new_node->value.children[1] = NULL;
    return new_node;
}

Tree_Node_Ptr tree_leaf_init(Tree_Node_Ptr root, unsigned char value, unsigned int count) {
    Tree_Node_Ptr new_node = (Tree_Node_Ptr)malloc(sizeof(Tree_Node));
    new_node->root = root;
    new_node->count = count;
    new_node->type = TNTLeaf;
    new_node->value.byte = value;
    return new_node;
}

void tree_dealloc(Tree_Node_Ptr tree) {
    if (tree != NULL) {
        if (tree->type == TNTBranch) {
            free(tree->value.children[0]);
            free(tree->value.children[1]);
        }
        free(tree);
    }
}

void tree_grow(CDictionary_Ptr count_dictionary) {
    
}

void tree_grow_test(Tree_Node_Ptr tree, unsigned char value, unsigned int count) {
    tree->count += count;
    if (tree->value.children[1] == NULL) {
        tree->value.children[1] = tree_leaf_init(tree, value, count);
    } else if (tree->value.children[0] == NULL) {
        tree->value.children[0] = tree_branch_init(tree);
        tree_grow_test(tree->value.children[0], value, count);
    } else {
        tree_grow_test(tree->value.children[0], value, count);
    }
}

void tree_print(Tree_Node_Ptr tree) {
    if (tree == NULL) {
        return;
    }
    
    if (tree->type == TNTBranch) {
        printf("Branch : %u\n", tree->count);
        tree_print(tree->value.children[1]);
        tree_print(tree->value.children[0]);
    } else {
        printf("%u : %u\n", tree->value.byte, tree->count);
    }
    
}