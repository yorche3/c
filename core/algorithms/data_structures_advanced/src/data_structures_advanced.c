#include "data_structures_advanced.h"
#include <stdlib.h>

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
    node->value = value;
    node->left = NULL;
    node->right = NULL;
}

int tree_node_get_value(const TreeNode *node) {
    return node->value;
}

TreeNode *tree_node_get_left(const TreeNode *node) {
    return node->left;
}

TreeNode *tree_node_get_right(const TreeNode *node) {
    return node->right;
}

void tree_node_set_left(TreeNode *node, TreeNode *left) {
    node->left = left;
}

void tree_node_set_right(TreeNode *node, TreeNode *right) {
    node->right = right;
}

void binary_tree_init(BinaryTree *tree) {
    tree->root = NULL;
    tree->count = 0;

}

int binary_tree_insert(BinaryTree *tree, int value) {
    TreeNode *root = tree->root;
    TreeNode *new_node = malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        return FAILURE_VALUE;
    }
    if (root == NULL) {
        tree_node_init(new_node, value);
        tree->root = new_node;
        tree->count++;
        return SUCCESS_VALUE;
    }
    TreeNode *current = root;
    while (true)
    {
        if (value == current->value) {
            free(new_node); // Avoid memory leak since the value already exists
            return SUCCESS_VALUE;
        }
        else if (value < current->value) {
            if (current->left == NULL) {
                tree_node_init(new_node, value);
                current->left = new_node;
                tree->count++;
                return SUCCESS_VALUE;
            }
            current = current->left;
        }
        else {
            if (current->right == NULL) {
                tree_node_init(new_node, value);
                current->right = new_node;
                tree->count++;
                return SUCCESS_VALUE;
            }
            current = current->right;
        }
    }
}

bool binary_tree_contains(const BinaryTree *tree, int value) {
    TreeNode *current = tree->root;
    while (current != NULL) {
        if (value == current->value) {
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

bool binary_tree_is_empty(const BinaryTree *tree) {
    return tree->count == 0;
}

size_t binary_tree_size(const BinaryTree *tree) {
    return tree->count;
}

static void free_tree_nodes(TreeNode *node) {
    if (node == NULL) {
        return;
    }
    free_tree_nodes(node->left);
    free_tree_nodes(node->right);
    free(node);
}

void binary_tree_free(BinaryTree *tree) {
    free_tree_nodes(tree->root);
    tree->root = NULL;
    tree->count = 0;
}

static inline void graph_node_init(GraphNode *node, int label) {
    node->label = label;
    node->neighbours = NULL;
    node->next_vertex = NULL;
}

void graph_init(Graph *graph) {
    graph->vertices = NULL;
    graph->vertex_total = 0;
    graph->edges = 0;
}

static GraphNode *graph_find_vertex(const Graph *graph, int label) {
    GraphNode *current = graph->vertices;
    while (current != NULL) {
        if (current->label == label) {
            return current;
        }
        current = current->next_vertex;
    }
    return NULL;
}

int graph_add_vertex(Graph *graph, int label) {
    if (graph_find_vertex(graph, label) != NULL) {
        return SUCCESS_VALUE; // Vertex already exists
    }
    GraphNode *new_node = malloc(sizeof(GraphNode));
    if (new_node == NULL) {
        return FAILURE_VALUE;
    }
    graph_node_init(new_node, label);
    new_node->next_vertex = graph->vertices;
    graph->vertices = new_node;
    graph->vertex_total++;
    return SUCCESS_VALUE;
}

int graph_add_edge(Graph *graph, int u, int v) {
    GraphNode *source = graph_find_vertex(graph, u);
    GraphNode *target = graph_find_vertex(graph, v);
    if (source == NULL || target == NULL) {
        return FAILURE_VALUE;
    }
    NeighborNode *previous = NULL;
    NeighborNode **current = &source->neighbours;
    while (*current != NULL && (*current)->label < v) {
        previous = *current;
        current = &(*current)->next;
    }
    if (*current != NULL && (*current)->label == v) {
        return SUCCESS_VALUE; // Edge already exists
    }
    NeighborNode *new_neighbor = malloc(sizeof(*new_neighbor));
    if (new_neighbor == NULL) {
        return FAILURE_VALUE;
    }
    new_neighbor->label = v;
    new_neighbor->next = *current;
    if (previous == NULL) {
        *current = new_neighbor;
    } else {
        previous->next = new_neighbor;
    }
    graph->edges++;
    return SUCCESS_VALUE;
}

bool graph_has_edge(const Graph *graph, int u, int v) {
    GraphNode *source = graph_find_vertex(graph, u);
    if (source == NULL) return false;
    if (graph_find_vertex(graph, v) == NULL) return false;
    NeighborNode *current = source->neighbours;
    while (current != NULL && current->label < v) {
        current = current->next;
    }
    if (current != NULL && current->label == v) {
        return true;
    }
    return false;
}

int graph_get_neighbors(const Graph *graph, int u, int **neighbors, size_t *count) {
    GraphNode *source = graph_find_vertex(graph, u);
    if (source == NULL) {
        return FAILURE_VALUE;
    }
    size_t neighbor_count = 0;
    NeighborNode *current = source->neighbours;
    while (current != NULL) {
        neighbor_count++;
        current = current->next;
    }
    if (neighbor_count == 0) {
        *neighbors = NULL;
        *count = 0;
        return SUCCESS_VALUE;
    }
    int *buf = malloc(neighbor_count * sizeof *buf);
    if (buf == NULL) {
        return FAILURE_VALUE;
    }
    *neighbors = buf;
    current = source->neighbours;
    for (size_t i = 0; i < neighbor_count; i++) {
        (*neighbors)[i] = current->label;
        current = current->next;
    }
    *count = neighbor_count;
    return SUCCESS_VALUE;
}

bool graph_is_empty(const Graph *graph) {
    return graph->vertex_total == 0;
}

size_t graph_vertex_count(const Graph *graph) {
    return graph->vertex_total;
}

size_t graph_edge_count(const Graph *graph) {
    return graph->edges;
}

void graph_free(Graph *graph) {
    GraphNode *vertex = graph->vertices;
    while (vertex != NULL) {
        GraphNode *next_vertex = vertex->next_vertex;
        NeighborNode *neighbor = vertex->neighbours;
        while (neighbor != NULL) {
            NeighborNode *next_neighbor = neighbor->next;
            free(neighbor);
            neighbor = next_neighbor;
        }
        free(vertex);
        vertex = next_vertex;
    }
    graph->vertices = NULL;
    graph->vertex_total = 0;
    graph->edges = 0;
}
