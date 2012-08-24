//
//  tree.h
//  Compressor
//
//  Created by Krzysztof Gabis on 23.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_tree_h
#define Compressor_tree_h

enum Tree_Node_Type {
    TNTBranch,
    TNTLeaf
};

typedef struct tree_node_t Tree_Node;
typedef Tree_Node * Tree_Node_Ptr;

union Tree_Node_Value {
    Tree_Node_Ptr branches[2];
    unsigned char value;
};

struct tree_node_t {
    enum Tree_Node_Type type;
    union Tree_Node_Value node_value;
    unsigned long long count;
    unsigned char value;
    struct tree_node_t *left;
    struct tree_node_t *right;
};

void Tree_Grow(Tree_Node_Ptr tree, unsigned char value);
Tree_Node_Ptr Tree_Alloc();
void Tree_Dealloc(Tree_Node_Ptr tree);
void Tree_Print(Tree_Node_Ptr tree);
int Tree_Get_Code(Tree_Node_Ptr tree, unsigned char value, unsigned int *mask);
unsigned char Tree_Get_Value(Tree_Node_Ptr tree, unsigned int code, unsigned int mask);

#endif
