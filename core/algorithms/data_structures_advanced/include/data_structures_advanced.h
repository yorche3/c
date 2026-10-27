#ifndef DataStructuresAdvanced_H
#define DataStructuresAdvanced_H

#include <stdbool.h>
#include <stddef.h>

/* Nodo base para estructuras de datos avanzadas / Base node for advanced data structures. */
#if 0
typedef struct Node {
    int value;
} Node;
#endif

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct BinaryTree {
    TreeNode *root;
    size_t count;
} BinaryTree;

typedef struct NeighborNode {
    int label;
    struct NeighborNode *next;
} NeighborNode;

typedef struct GraphNode {
    int label;
    NeighborNode *neighbours;
    struct GraphNode *next_vertex;
} GraphNode;

typedef struct Graph {
    GraphNode *vertices;
    size_t vertex_total;
    size_t edges;
} Graph;

/* void node_init(Node *node, int value); */
#if 0
void node_init(Node *node, int value);
int node_get_value(const Node *node);
#endif

void tree_node_init(TreeNode *node, int value);
int tree_node_get_value(const TreeNode *node);
TreeNode *tree_node_get_left(const TreeNode *node);
TreeNode *tree_node_get_right(const TreeNode *node);
void tree_node_set_left(TreeNode *node, TreeNode *left);
void tree_node_set_right(TreeNode *node, TreeNode *right);

/* Estados int: 0 exito, -1 fallo / int status: 0 success, -1 failure.
 * Enlaces ausentes: NULL / Absent links: NULL.
 */
void binary_tree_init(BinaryTree *tree);
int binary_tree_insert(BinaryTree *tree, int value);
bool binary_tree_contains(const BinaryTree *tree, int value);
bool binary_tree_is_empty(const BinaryTree *tree);
size_t binary_tree_size(const BinaryTree *tree);

/*
 Libera todos los nodos del árbol. Deja el árbol vacío (root = NULL, count = 0).
 Free all nodes of the tree. Leaves the tree empty (root = NULL, count = 0). */
void binary_tree_free(BinaryTree *tree);

/* GraphNode.init es interno a Graph / GraphNode.init is internal to Graph. */
void graph_init(Graph *graph);
int graph_add_vertex(Graph *graph, int label);
int graph_add_edge(Graph *graph, int u, int v);
bool graph_has_edge(const Graph *graph, int u, int v);
/*
 * Exito: copia propia en *neighbors, longitud en *count; liberar con free().
 * Vacio: NULL y 0 con estado 0; fallo: -1, sin modificar las salidas.
 * Success: owned copy in *neighbors, length in *count; release with free().
 * Empty: NULL and 0 with status 0; failure: -1, outputs unchanged.
 */
int graph_get_neighbors(const Graph *graph, int u, int **neighbors, size_t *count);
bool graph_is_empty(const Graph *graph);
size_t graph_vertex_count(const Graph *graph);
size_t graph_edge_count(const Graph *graph);

/* Libera todos los nodos del grafo. Deja el grafo vacío (vertices = NULL, vertex_total = 0, edges = 0).
 Free all nodes of the graph. Leaves the graph empty (vertices = NULL, vertex_total = 0, edges = 0). */
void graph_free(Graph *graph);

#endif
