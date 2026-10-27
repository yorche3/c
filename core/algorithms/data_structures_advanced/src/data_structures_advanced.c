#include "data_structures_advanced.h"

#define SUCCESS_VALUE 0
#define FAILURE_VALUE (-1)

#if 0
/* Esqueletos sin algoritmo / Stubs without algorithm implementation. */
void node_init(Node *node, int value) {
    (void)node;
    (void)value;
}

int node_get_value(const Node *node) {
    (void)node;
    return 0;
}
#endif

void tree_node_init(TreeNode *node, int value) {
    (void)node;
    (void)value;
}

int tree_node_get_value(const TreeNode *node) {
    (void)node;
    return FAILURE_VALUE;
}

TreeNode *tree_node_get_left(const TreeNode *node) {
    (void)node;
    return NULL;
}

TreeNode *tree_node_get_right(const TreeNode *node) {
    (void)node;
    return NULL;
}

void tree_node_set_left(TreeNode *node, TreeNode *left) {
    (void)node;
    (void)left;
}

void tree_node_set_right(TreeNode *node, TreeNode *right) {
    (void)node;
    (void)right;
}

void binary_tree_init(BinaryTree *tree) {
    (void)tree;
}

int binary_tree_insert(BinaryTree *tree, int value) {
    (void)tree;
    (void)value;
    return FAILURE_VALUE;
}

bool binary_tree_contains(const BinaryTree *tree, int value) {
    (void)tree;
    (void)value;
    return false;
}

bool binary_tree_is_empty(const BinaryTree *tree) {
    (void)tree;
    return false;
}

size_t binary_tree_size(const BinaryTree *tree) {
    (void)tree;
    return 0;
}

void binary_tree_free(BinaryTree *tree) {
    (void)tree;
}

static inline void graph_node_init(GraphNode *node, int label) {
    (void)node;
    (void)label;
}

void graph_init(Graph *graph) {
    (void)graph;
}

int graph_add_vertex(Graph *graph, int label) {
    (void)graph;
    (void)label;
    return FAILURE_VALUE;
}

int graph_add_edge(Graph *graph, int u, int v) {
    (void)graph;
    (void)u;
    (void)v;
    return FAILURE_VALUE;
}

bool graph_has_edge(const Graph *graph, int u, int v) {
    (void)graph;
    (void)u;
    (void)v;
    return false;
}

int graph_get_neighbors(const Graph *graph, int u, int **neighbors, size_t *count) {
    (void)graph;
    (void)u;
    (void)neighbors;
    (void)count;
    return FAILURE_VALUE;
}

bool graph_is_empty(const Graph *graph) {
    (void)graph;
    return false;
}

size_t graph_vertex_count(const Graph *graph) {
    (void)graph;
    return SUCCESS_VALUE;
}

size_t graph_edge_count(const Graph *graph) {
    (void)graph;
    return SUCCESS_VALUE;
}

void graph_free(Graph *graph) {
    (void)graph;
}
