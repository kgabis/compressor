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
#include "priority_queue.h"
#include "bit_operations.h"

#define MY_DEBUG 0

static int compare_nodes(const void *a, const void *b) {
    Tree_Ptr tna = (Tree_Ptr)a;
    Tree_Ptr tnb = (Tree_Ptr)b;
    return tna->count < tnb->count;
}

Tree_Ptr tree_branch_init() {
    Tree_Ptr new_node = (Tree_Ptr)malloc(sizeof(Tree));
    new_node->root = NULL;
    new_node->count = 0;
    new_node->type = TNTBranch;
    new_node->value.children[0] = NULL;
    new_node->value.children[1] = NULL;
    return new_node;
}

Tree_Ptr tree_branch_init_with_children(Tree_Ptr left, Tree_Ptr right) {
    Tree_Ptr new_node = tree_branch_init();
    
#if MY_DEBUG
    printf("Creating branch with:\n");
    printf("\t");
    if (left->type == TNTBranch) {
        printf("branch with count: %lu\n", left->count);
    } else {
        printf("leaf %c with count: %lu\n", left->value.leaf_value, left->count);
    }
    printf("\t");
    if (right->type == TNTBranch) {
        printf("branch with count: %lu\n", right->count);
    } else {
        printf("leaf %c with count: %lu\n", right->value.leaf_value, right->count);
    }
#endif
    new_node->value.children[0] = left;
    new_node->value.children[1] = right;
    new_node->count = left->count + right->count;
    return new_node;
}

Tree_Ptr tree_leaf_init(int leaf_value, unsigned long count) {
    Tree_Ptr new_node = (Tree_Ptr)malloc(sizeof(Tree));
    new_node->root = NULL;
    new_node->count = count;
    new_node->type = TNTLeaf;
    new_node->value.leaf_value = leaf_value;
    return new_node;
}

void tree_dealloc(Tree_Ptr tree) {
    if (tree != NULL) {
        if (tree->type == TNTBranch) {
            free(tree->value.children[0]);
            free(tree->value.children[1]);
        }
        free(tree);
    }
}

static Tree_Ptr get_node_from_dict_entry(CountDict_KVPair dict_entry) {
    return tree_leaf_init(dict_entry.key, dict_entry.value);
}

Tree_Ptr tree_grow_from_countdict(CountDict_Ptr count_dictionary) {
    PQueue_Ptr pqueue = pqueue_init(compare_nodes);
    Tree_Ptr new_node;
    Tree_Ptr result;
    int i;
    for (i = 0; i < count_dictionary->count; i++) {
        new_node = get_node_from_dict_entry(count_dictionary->items[i]);
        pqueue_enqueue(pqueue, new_node);
    }
    while (pqueue->count > 1) {
        Tree_Ptr left = pqueue_dequeue(pqueue);
        Tree_Ptr right = pqueue_dequeue(pqueue);
        pqueue_enqueue(pqueue,
                       tree_branch_init_with_children(left, right));
    }
    result = pqueue_dequeue(pqueue);
    pqueue_dealloc(pqueue);
    return result;
}

static void add_leaves_to_codedict(Tree_Ptr tree,
                                   CodeDict_Ptr codedict,
                                   unsigned int code,
                                   unsigned int mask) {
    if (tree == NULL) {
        return;
    } else if (tree->type == TNTLeaf) {
        codedict_add(codedict, tree->value.leaf_value, code, mask);
    } else {
        code = code << 1;
        BIT_CLEAR(code, 0);
        add_leaves_to_codedict(tree->value.children[0], codedict, code, (mask << 1) | 1);
        BIT_SET(code, 0);
        add_leaves_to_codedict(tree->value.children[1], codedict, code, (mask << 1) | 1);
    }    
}

CodeDict_Ptr tree_get_codedict(Tree_Ptr tree) {
    CodeDict_Ptr codedict = codedict_init();
    add_leaves_to_codedict(tree, codedict, 0, 0);
    return codedict;
}

//void tree_grow_test(Tree_Ptr tree, unsigned char leaf_value, unsigned long count) {
//    tree->count += count;
//    if (tree->value.children[1] == NULL) {
//        tree->value.children[1] = tree_leaf_init(leaf_value, count);
//    } else if (tree->value.children[0] == NULL) {
//        tree->value.children[0] = tree_branch_init();
//        tree_grow_test(tree->value.children[0], leaf_value, count);
//    } else {
//        tree_grow_test(tree->value.children[0], leaf_value, count);
//    }
//}

void tree_print(Tree_Ptr tree) {
    if (tree == NULL) {
        return;
    }
    
    if (tree->type == TNTBranch) {
        printf("Branch : %lu\n", tree->count);
        tree_print(tree->value.children[1]);
        tree_print(tree->value.children[0]);
    } else {
        printf("%u : %lu\n", tree->value.leaf_value, tree->count);
    }
    
}