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

typedef struct tree_node_t Tree;
typedef Tree * Tree_Ptr;

//TODO: new name for byte
union Tree_Node_Value {
    unsigned char byte;
    Tree_Ptr children[2];
};

struct tree_node_t {
    Tree_Ptr root;
    unsigned long count;
    enum Tree_Node_Type type;
    union Tree_Node_Value value;
};

Tree_Ptr tree_grow_from_cdict(CountDict_Ptr count_dictionary);
Tree_Ptr tree_branch_init();
Tree_Ptr tree_branch_init_with_children(Tree_Ptr left, Tree_Ptr right);
Tree_Ptr tree_leaf_init(unsigned char byte_value, unsigned long count);
void tree_dealloc(Tree_Ptr tree);

//test functions
void tree_grow_test(Tree_Ptr tree, unsigned char byte, unsigned long count);
void tree_print(Tree_Ptr tree);
               
#endif
