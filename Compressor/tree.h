//
//  tree.h
//  Compressor
//
//  Created by Krzysztof Gabis on 23.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_tree_h
#define Compressor_tree_h

#include "count_dictionary.h"

enum Tree_Node_Type {
    TNTBranch,
    TNTLeaf
};

typedef struct tree_node_t Tree_Node;
typedef Tree_Node * Tree_Node_Ptr;

union Tree_Node_Value {
    unsigned char byte;
    Tree_Node_Ptr children[2];
};

struct tree_node_t {
    Tree_Node_Ptr root;
    unsigned int count;
    enum Tree_Node_Type type;
    union Tree_Node_Value value;
};

int compare_nodes(const void *a, const void *b);
Tree_Node_Ptr tree_branch_init(Tree_Node_Ptr root);
void tree_dealloc(Tree_Node_Ptr tree);

void tree_grow(CDictionary_Ptr count_dictionary);

//test functions
void tree_grow_test(Tree_Node_Ptr tree, unsigned char value, unsigned int count);
void tree_print(Tree_Node_Ptr tree);
               
#endif
