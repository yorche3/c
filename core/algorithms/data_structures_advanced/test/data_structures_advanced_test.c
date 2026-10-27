/*
 * Suite de pruebas — data_structures_advanced (C)
 * Framework: Criterion
 */

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <stdlib.h>
#include "../include/data_structures_advanced.h"

/* Each parameter is one specification row on fresh state. The immutable
 * TreeNode row does not apply to the contract's in-place setters.
 * NULL links are tested by the absent-link and unlink rows; NULL ADT
 * receivers have no specified failure policy and are not invented here.
 */

#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

typedef struct {
    int parent;
    int left;
    int right;
    bool link_children;
    bool traverse_children;
    bool unlink_children;
} TreeNodeInput;

typedef struct {
    bool check_value;
    int parent;
    bool check_links;
    int left;
    int right;
} TreeNodeOutput;

static const TreeNodeInput create_node_input = {10, 0, 0, false, false, false};
static const TreeNodeOutput create_node_output = {true, 10, false, 0, 0};
static const TreeNodeInput absent_links_input = {10, 0, 0, false, false, false};
static const TreeNodeOutput absent_links_output = {false, 0, true, 0, 0};
static const TreeNodeInput link_children_input = {10, 20, 30, true, false, false};
static const TreeNodeOutput link_children_output = {false, 0, true, 20, 30};
static const TreeNodeInput traverse_links_input = {10, 20, 30, true, true, false};
static const TreeNodeOutput traverse_links_output = {false, 0, true, 20, 30};
static const TreeNodeInput unlink_children_input = {10, 20, 30, true, false, true};
static const TreeNodeOutput unlink_children_output = {true, 10, true, 0, 0};

typedef struct {
    const char *name;
    const TreeNodeInput *input;
    const TreeNodeOutput *output;
} TreeNodeCase;

static TreeNodeCase tree_node_cases[] = {
    {"create_node", &create_node_input, &create_node_output},
    {"absent_links", &absent_links_input, &absent_links_output},
    {"link_children", &link_children_input, &link_children_output},
    {"traverse_links", &traverse_links_input, &traverse_links_output},
    {"unlink_children", &unlink_children_input, &unlink_children_output},
};

static void check_link(TreeNode *child, int expected, bool traverse,
                       const char *subject, const char *name, const char *side) {
    if (expected == 0) {
        cr_expect_null(child, "%s should have an absent %s link in %s",
                       subject, side, name);
        return;
    }
    cr_expect_not_null(child, "%s should have a %s child with value %d in %s",
                       subject, side, expected, name);
    if (child == NULL) {
        return;
    }
    cr_expect_eq(tree_node_get_value(child), expected,
                 "%s should reach %s child value %d in %s",
                 subject, side, expected, name);
    if (traverse) {
        cr_expect_null(tree_node_get_left(child),
                       "%s should reach a child with an absent left link in %s",
                       subject, name);
        cr_expect_null(tree_node_get_right(child),
                       "%s should reach a child with an absent right link in %s",
                       subject, name);
    }
}

static void run_tree_node_case(const TreeNodeCase *test_case, const char *subject) {
    const TreeNodeInput *input = test_case->input;
    const TreeNodeOutput *output = test_case->output;
    const char *name = test_case->name;
    TreeNode parent = {0};
    TreeNode left = {0};
    TreeNode right = {0};

    tree_node_init(&parent, input->parent);
    if (input->link_children) {
        tree_node_init(&left, input->left);
        tree_node_init(&right, input->right);
        tree_node_set_left(&parent, &left);
        tree_node_set_right(&parent, &right);
    }
    if (input->unlink_children) {
        tree_node_set_left(&parent, NULL);
        cr_expect_eq(tree_node_get_value(&parent), output->parent,
                     "%s should preserve parent value %d after clearing left in %s",
                     subject, output->parent, name);
        check_link(tree_node_get_left(&parent), 0, false, subject, name, "left");
        check_link(tree_node_get_right(&parent), input->right, false,
                   subject, name, "right");
        tree_node_set_right(&parent, NULL);
    }
    if (output->check_value) {
        cr_expect_eq(tree_node_get_value(&parent), output->parent,
                     "%s should return parent value %d in %s",
                     subject, output->parent, name);
    }
    if (output->check_links) {
        check_link(tree_node_get_left(&parent), output->left,
                   input->traverse_children, subject, name, "left");
        check_link(tree_node_get_right(&parent), output->right,
                   input->traverse_children, subject, name, "right");
    }
}

typedef struct {
    int values[5];
    size_t count;
    bool query_missing;
    int missing_value;
} BinaryTreeInput;

typedef struct {
    int insertion_status;
    bool empty;
    size_t size;
    int present[5];
    size_t present_count;
    bool missing_present;
} BinaryTreeOutput;

static const BinaryTreeInput empty_tree_input = {{0}, 0, true, 50};
static const BinaryTreeOutput empty_tree_output = {0, true, 0, {0}, 0, false};
static const BinaryTreeInput root_input = {{50}, 1, false, 0};
static const BinaryTreeOutput root_output = {0, false, 1, {50}, 1, false};
static const BinaryTreeInput lower_higher_input = {{50, 30, 70}, 3, false, 0};
static const BinaryTreeOutput lower_higher_output =
    {0, false, 3, {50, 30, 70}, 3, false};
static const BinaryTreeInput multilevel_input = {{50, 30, 70, 20, 40}, 5, false, 0};
static const BinaryTreeOutput multilevel_output =
    {0, false, 5, {50, 30, 70, 20, 40}, 5, false};
static const BinaryTreeInput missing_value_input = {{50}, 1, true, 99};
static const BinaryTreeOutput missing_value_output =
    {0, false, 1, {50}, 1, false};
static const BinaryTreeInput duplicate_value_input = {{50, 30, 70, 30}, 4, false, 0};
static const BinaryTreeOutput duplicate_value_output =
    {0, false, 3, {50, 30, 70}, 3, false};
static const BinaryTreeInput ordered_insertions_input =
    {{20, 30, 40, 50, 70}, 5, true, 99};
static const BinaryTreeOutput ordered_insertions_output =
    {0, false, 5, {20, 30, 40, 50, 70}, 5, false};

typedef struct {
    const char *name;
    const BinaryTreeInput *input;
    const BinaryTreeOutput *output;
} BinaryTreeCase;

static BinaryTreeCase binary_tree_cases[] = {
    {"empty_tree", &empty_tree_input, &empty_tree_output},
    {"root", &root_input, &root_output},
    {"lower_higher", &lower_higher_input, &lower_higher_output},
    {"multilevel", &multilevel_input, &multilevel_output},
    {"missing_value", &missing_value_input, &missing_value_output},
    {"duplicate_value", &duplicate_value_input, &duplicate_value_output},
    {"ordered_insertions", &ordered_insertions_input, &ordered_insertions_output},
};

static void run_binary_tree_case(const BinaryTreeCase *test_case,
                                 const char *subject) {
    const BinaryTreeInput *input = test_case->input;
    const BinaryTreeOutput *output = test_case->output;
    const char *name = test_case->name;
    BinaryTree tree = {0};

    binary_tree_init(&tree);
    for (size_t i = 0; i < input->count; ++i) {
        cr_expect_eq(binary_tree_insert(&tree, input->values[i]),
                     output->insertion_status,
                     "%s should return insertion status %d for value %d at step %zu in %s",
                     subject, output->insertion_status, input->values[i], i, name);
    }
    if (input->query_missing) {
        cr_expect_eq(binary_tree_contains(&tree, input->missing_value),
                     output->missing_present,
                     "%s should report missing value %d as %s in %s",
                     subject, input->missing_value,
                     output->missing_present ? "present" : "absent", name);
    }
    for (size_t i = 0; i < output->present_count; ++i) {
        cr_expect(binary_tree_contains(&tree, output->present[i]),
                  "%s should preserve membership of %d in %s",
                  subject, output->present[i], name);
    }
    cr_expect_eq(binary_tree_is_empty(&tree), output->empty,
                 "%s should report is_empty = %s in %s",
                 subject, output->empty ? "true" : "false", name);
    cr_expect_eq(binary_tree_size(&tree), output->size,
                 "%s should report size %zu in %s", subject, output->size, name);
    binary_tree_free(&tree);
}

typedef enum {
    ADD_VERTEX,
    ADD_EDGE,
    HAS_EDGE,
    GET_NEIGHBORS,
    SAVE_NEIGHBORS,
    CHANGE_NEIGHBORS,
    CHECK_SAVED_NEIGHBORS
} GraphOperation;

typedef struct {
    GraphOperation operation;
    int u;
    int v;
} GraphStep;

typedef struct {
    int result;
    size_t count;
    int values[3];
} GraphStepOutput;

typedef struct {
    bool empty;
    size_t vertices;
    size_t edges;
    const GraphStepOutput *steps;
} GraphOutput;

static const GraphStep empty_graph_input[] = {
    {HAS_EDGE, 10, 30}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput empty_graph_steps_output[] = {
    {0, 0, {0}}, {-1, 0, {0}},
};
static const GraphOutput empty_graph_output = {true, 0, 0, empty_graph_steps_output};

static const GraphStep isolated_vertex_input[] = {
    {ADD_VERTEX, 10, 0}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput isolated_vertex_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}},
};
static const GraphOutput isolated_vertex_output =
    {false, 1, 0, isolated_vertex_steps_output};

static const GraphStep directed_edge_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 70, 0}, {ADD_EDGE, 10, 70},
    {HAS_EDGE, 10, 70}, {HAS_EDGE, 70, 10},
};
static const GraphStepOutput directed_edge_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {1, 0, {0}}, {0, 0, {0}},
};
static const GraphOutput directed_edge_output =
    {false, 2, 1, directed_edge_steps_output};

static const GraphStep duplicate_vertex_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 30, 0}, {ADD_EDGE, 10, 30},
    {ADD_VERTEX, 10, 0}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput duplicate_vertex_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 1, {30}},
};
static const GraphOutput duplicate_vertex_output =
    {false, 2, 1, duplicate_vertex_steps_output};

static const GraphStep duplicate_edge_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 30, 0}, {ADD_EDGE, 10, 30},
    {ADD_EDGE, 10, 30}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput duplicate_edge_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 1, {30}},
};
static const GraphOutput duplicate_edge_output =
    {false, 2, 1, duplicate_edge_steps_output};

static const GraphStep missing_endpoint_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 30, 0}, {ADD_EDGE, 10, 30},
    {ADD_EDGE, 10, 99}, {ADD_EDGE, 99, 10}, {ADD_EDGE, 98, 99}, {ADD_EDGE, 99, 99},
    {GET_NEIGHBORS, 10, 0}, {GET_NEIGHBORS, 30, 0},
    {HAS_EDGE, 10, 99}, {HAS_EDGE, 99, 10}, {HAS_EDGE, 98, 99}, {HAS_EDGE, 99, 99},
    {GET_NEIGHBORS, 98, 0}, {GET_NEIGHBORS, 99, 0},
};
static const GraphStepOutput missing_endpoint_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}},
    {-1, 0, {0}}, {-1, 0, {0}}, {-1, 0, {0}}, {-1, 0, {0}},
    {0, 1, {30}}, {0, 0, {0}},
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}},
    {-1, 0, {0}}, {-1, 0, {0}},
};
static const GraphOutput missing_endpoint_output =
    {false, 2, 1, missing_endpoint_steps_output};

static const GraphStep sorted_neighbors_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 30, 0},
    {ADD_VERTEX, 50, 0}, {ADD_VERTEX, 70, 0},
    {ADD_EDGE, 10, 70}, {ADD_EDGE, 10, 30},
    {ADD_EDGE, 10, 50}, {ADD_EDGE, 30, 50},
    {GET_NEIGHBORS, 10, 0}, {GET_NEIGHBORS, 30, 0},
    {GET_NEIGHBORS, 50, 0}, {GET_NEIGHBORS, 70, 0},
};
static const GraphStepOutput sorted_neighbors_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}},
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}},
    {0, 3, {30, 50, 70}}, {0, 1, {50}}, {0, 0, {0}}, {0, 0, {0}},
};
static const GraphOutput sorted_neighbors_output =
    {false, 4, 4, sorted_neighbors_steps_output};

static const GraphStep missing_edge_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 30, 0}, {HAS_EDGE, 10, 30},
};
static const GraphStepOutput missing_edge_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}},
};
static const GraphOutput missing_edge_output =
    {false, 2, 0, missing_edge_steps_output};

static const GraphStep missing_neighbors_input[] = {
    {ADD_VERTEX, 10, 0}, {GET_NEIGHBORS, 99, 0}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput missing_neighbors_steps_output[] = {
    {0, 0, {0}}, {-1, 0, {0}}, {0, 0, {0}},
};
static const GraphOutput missing_neighbors_output =
    {false, 1, 0, missing_neighbors_steps_output};

static const GraphStep self_loop_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_EDGE, 10, 10}, {ADD_EDGE, 10, 10},
    {HAS_EDGE, 10, 10}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput self_loop_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {1, 0, {0}}, {0, 1, {10}},
};
static const GraphOutput self_loop_output =
    {false, 1, 1, self_loop_steps_output};

static const GraphStep neighbor_isolation_input[] = {
    {ADD_VERTEX, 10, 0}, {ADD_VERTEX, 30, 0}, {ADD_VERTEX, 50, 0},
    {ADD_EDGE, 10, 30}, {SAVE_NEIGHBORS, 10, 0}, {CHANGE_NEIGHBORS, 10, 70},
    {GET_NEIGHBORS, 10, 0}, {ADD_EDGE, 10, 50},
    {CHECK_SAVED_NEIGHBORS, 10, 0}, {GET_NEIGHBORS, 10, 0},
};
static const GraphStepOutput neighbor_isolation_steps_output[] = {
    {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}}, {0, 0, {0}},
    {0, 1, {30}}, {0, 1, {30}}, {0, 1, {30}}, {0, 0, {0}},
    {0, 1, {30}}, {0, 2, {30, 50}},
};
static const GraphOutput neighbor_isolation_output =
    {false, 3, 2, neighbor_isolation_steps_output};

typedef struct {
    const char *name;
    const GraphStep *input;
    size_t count;
    const GraphOutput *output;
} GraphCase;

#define GRAPH_CASE(name) \
    {#name, name##_input, ARRAY_COUNT(name##_input), &name##_output}

static GraphCase graph_cases[] = {
    GRAPH_CASE(empty_graph),
    GRAPH_CASE(isolated_vertex),
    GRAPH_CASE(directed_edge),
    GRAPH_CASE(duplicate_vertex),
    GRAPH_CASE(duplicate_edge),
    GRAPH_CASE(missing_endpoint),
    GRAPH_CASE(sorted_neighbors),
    GRAPH_CASE(missing_edge),
    GRAPH_CASE(missing_neighbors),
    GRAPH_CASE(self_loop),
    GRAPH_CASE(neighbor_isolation),
};

static void check_neighbors(const int *neighbors, size_t count,
                            const GraphStepOutput *output, const char *subject,
                            const char *name, size_t step) {
    cr_expect_eq(count, output->count,
                 "%s should return %zu neighbors at step %zu in %s",
                 subject, output->count, step, name);
    if (output->count == 0) {
        cr_expect_null(neighbors,
                       "%s should return NULL for empty neighbors at step %zu in %s",
                       subject, step, name);
        return;
    }
    cr_expect_not_null(neighbors,
                       "%s should return a neighbor array at step %zu in %s",
                       subject, step, name);
    if (neighbors == NULL || count != output->count) {
        return;
    }
    for (size_t i = 0; i < output->count; ++i) {
        cr_expect_eq(neighbors[i], output->values[i],
                     "%s should return neighbor[%zu] = %d at step %zu in %s",
                     subject, i, output->values[i], step, name);
    }
}

static void run_graph_case(const GraphCase *test_case, const char *subject) {
    Graph graph = {0};
    int *saved_neighbors = NULL;
    size_t saved_count = 0;
    const char *name = test_case->name;
    const GraphOutput *output = test_case->output;

    graph_init(&graph);
    for (size_t i = 0; i < test_case->count; ++i) {
        const GraphStep *step = &test_case->input[i];
        const GraphStepOutput *expected = &output->steps[i];
        int result;

        switch (step->operation) {
        case ADD_VERTEX:
            result = graph_add_vertex(&graph, step->u);
            cr_expect_eq(result, expected->result,
                         "%s should return add_vertex(%d) status %d at step %zu in %s",
                         subject, step->u, expected->result, i, name);
            break;
        case ADD_EDGE:
            result = graph_add_edge(&graph, step->u, step->v);
            cr_expect_eq(result, expected->result,
                         "%s should return add_edge(%d,%d) status %d at step %zu in %s",
                         subject, step->u, step->v, expected->result, i, name);
            break;
        case HAS_EDGE:
            result = graph_has_edge(&graph, step->u, step->v);
            cr_expect_eq(result, expected->result,
                         "%s should return has_edge(%d,%d) = %d at step %zu in %s",
                         subject, step->u, step->v, expected->result, i, name);
            break;
        case CHECK_SAVED_NEIGHBORS:
            check_neighbors(saved_neighbors, saved_count, expected, subject, name, i);
            break;
        case GET_NEIGHBORS:
        case SAVE_NEIGHBORS:
        case CHANGE_NEIGHBORS: {
            int unchanged_value = 0;
            int *neighbors = &unchanged_value;
            size_t count = (size_t)-1;

            result = graph_get_neighbors(&graph, step->u, &neighbors, &count);
            cr_expect_eq(result, expected->result,
                         "%s should return get_neighbors(%d) status %d at step %zu in %s",
                         subject, step->u, expected->result, i, name);
            if (result != 0) {
                cr_expect_eq(neighbors, &unchanged_value,
                             "%s should preserve the neighbor output on failure at step %zu in %s",
                             subject, i, name);
                cr_expect_eq(count, (size_t)-1,
                             "%s should preserve the count output on failure at step %zu in %s",
                             subject, i, name);
                break;
            }
            /* An unchanged stack sentinel is not an owned result. */
            cr_expect_neq(neighbors, &unchanged_value,
                          "%s should replace the neighbor output on success at step %zu in %s",
                          subject, i, name);
            if (neighbors == &unchanged_value) {
                break;
            }
            check_neighbors(neighbors, count, expected, subject, name, i);
            if (step->operation == SAVE_NEIGHBORS) {
                saved_neighbors = neighbors;
                saved_count = count;
            } else {
                if (step->operation == CHANGE_NEIGHBORS &&
                    neighbors != NULL && count == expected->count && count > 0) {
                    neighbors[0] = step->v;
                }
                free(neighbors);
            }
            break;
        }
        }
    }
    cr_expect_eq(graph_is_empty(&graph), output->empty,
                 "%s should report is_empty = %s in %s",
                 subject, output->empty ? "true" : "false", name);
    cr_expect_eq(graph_vertex_count(&graph), output->vertices,
                 "%s should report %zu vertices in %s", subject, output->vertices, name);
    cr_expect_eq(graph_edge_count(&graph), output->edges,
                 "%s should report %zu edges in %s", subject, output->edges, name);
    free(saved_neighbors);
    graph_free(&graph);
}

/* Every public specification operation runs every row of its abstraction.
 * Criterion supplies main and isolates each row/operation in its own test.
 * Parameters carry indices, not pointers into another test process.
 */
#define OPERATION_TEST(type, cases, runner, operation) \
    ParameterizedTestParameters(data_structures_advanced, operation##_should_satisfy_contract) { \
        static size_t indices[ARRAY_COUNT(cases)]; \
        for (size_t i = 0; i < ARRAY_COUNT(cases); ++i) { \
            indices[i] = i; \
        } \
        return cr_make_param_array(size_t, indices, ARRAY_COUNT(cases)); \
    } \
    ParameterizedTest(size_t *case_index, data_structures_advanced, operation##_should_satisfy_contract) { \
        const type *test_case = &cases[*case_index]; \
        runner(test_case, #operation); \
    }

OPERATION_TEST(TreeNodeCase, tree_node_cases, run_tree_node_case, tree_node_init)
OPERATION_TEST(TreeNodeCase, tree_node_cases, run_tree_node_case, tree_node_get_value)
OPERATION_TEST(TreeNodeCase, tree_node_cases, run_tree_node_case, tree_node_get_left)
OPERATION_TEST(TreeNodeCase, tree_node_cases, run_tree_node_case, tree_node_get_right)
OPERATION_TEST(TreeNodeCase, tree_node_cases, run_tree_node_case, tree_node_set_left)
OPERATION_TEST(TreeNodeCase, tree_node_cases, run_tree_node_case, tree_node_set_right)

OPERATION_TEST(BinaryTreeCase, binary_tree_cases, run_binary_tree_case, binary_tree_init)
OPERATION_TEST(BinaryTreeCase, binary_tree_cases, run_binary_tree_case, binary_tree_insert)
OPERATION_TEST(BinaryTreeCase, binary_tree_cases, run_binary_tree_case, binary_tree_contains)
OPERATION_TEST(BinaryTreeCase, binary_tree_cases, run_binary_tree_case, binary_tree_is_empty)
OPERATION_TEST(BinaryTreeCase, binary_tree_cases, run_binary_tree_case, binary_tree_size)

OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_init)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_add_vertex)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_add_edge)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_has_edge)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_get_neighbors)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_is_empty)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_vertex_count)
OPERATION_TEST(GraphCase, graph_cases, run_graph_case, graph_edge_count)
