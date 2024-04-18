#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct      s_node
{
    int             id;
    struct s_node   *next;
}                   t_node;

typedef struct      s_graph
{
    t_node          **nodes;
    int             size;
}                   t_graph;

// Utility function to print an error message and exit
void    ft_fatal_error(void)
{
    write(1, "Error: Fatal\n", 13);
    exit(1);
}

// Add an edge to the graph
void    add_edge(t_graph *graph, int from, int to)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        ft_fatal_error();
    new_node->id = to;
    new_node->next = graph->nodes[from];
    graph->nodes[from] = new_node;
}

// Depth-First Search (DFS) to find the longest path
int     dfs(t_graph *graph, int node, int *visited)
{
    visited[node] = 1;
    int max_depth = 0;
    for (t_node *adj = graph->nodes[node]; adj != NULL; adj = adj->next)
    {
        if (!visited[adj->id])
        {
            int depth = dfs(graph, adj->id, visited);
            if (depth > max_depth)
                max_depth = depth;
        }
    }
    visited[node] = 0;
    return max_depth + 1;
}

// Initialize the graph
t_graph *init_graph(int max_nodes)
{
    t_graph *graph = malloc(sizeof(t_graph));
    if (!graph)
        ft_fatal_error();
    graph->nodes = malloc(sizeof(t_node *) * max_nodes);
    if (!graph->nodes)
        ft_fatal_error();
    for (int i = 0; i < max_nodes; i++)
        graph->nodes[i] = NULL;
    graph->size = max_nodes;
    return graph;
}

// Find the node with the maximum id in the input to determine the graph size
int     find_max_node(char *str)
{
    int max_id = 0;
    while (*str)
    {
        int node = atoi(str);
        if (node > max_id)
            max_id = node;
        while (*str && *str != ' ')
            str++;
        if (*str)
            str++;
    }
    return max_id;
}

// Main function to parse the graph and find the longest path
int     main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "\n", 1);
        return (0);
    }
    int max_node = find_max_node(argv[1]) + 1;
    t_graph *graph = init_graph(max_node);
    char *ptr = argv[1];
    while (*ptr)
    {
        int from = atoi(ptr);
        while (*ptr && *ptr != '-')
            ptr++;
        ptr++; // Skip '-'
        int to = atoi(ptr);
        add_edge(graph, from, to);
        add_edge(graph, to, from); // Since the graph is undirected
        while (*ptr && *ptr != ' ')
            ptr++;
        if (*ptr)
            ptr++;
    }
    int *visited = calloc(max_node, sizeof(int));
    if (!visited)
        ft_fatal_error();
    int max_length = 0;
    for (int i = 0; i < max_node; i++)
    {
        if (graph->nodes[i] != NULL)
        {
            int length = dfs(graph, i, visited);
            if (length > max_length)
                max_length = length;
        }
    }
    free(visited);
    printf("%d\n", max_length);
    return (0);
}
