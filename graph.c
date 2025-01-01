#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//* Graph use Adjacent Matrix
int** create_matrix_graph(int V) {
    int** matrix = (int**)malloc(V * sizeof(int*));
    for(int i = 0; i < V; i++) {
        matrix[i] = (int*)malloc(V * sizeof(int));
        for(int j = 0; j < V; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

//? Add Edge to Graph
void add_edge_matrix(int** matrix, int src, int dest) {
    matrix[src][dest] = 1;
}

//? Print Graph use Adjacent Matrix
void print_matrix_graph(int** matrix, int V) {
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//? Dispose Graph use Adjacent Matrix
void dispose_graph_matrix(int** matrix, int V) {
    for (int i = 0; i < V; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


//? Struct Adjacenct list Node
typedef struct AdjacentListNode {
    int dest;
    char name;
    struct AdjacentListNode* next;
} AdjacentListNode;

//? Struct Adjacency List
typedef struct AdjacentList {
    struct AdjacentListNode* head;
} AdjacentList;

//* Graph use Adjacent List
typedef struct Graph {
    int V;
    AdjacentList* array;
} Graph;

//? Create Adjacenct list Node
AdjacentListNode* create_node(int dest, char name) {
    AdjacentListNode* node = (AdjacentListNode*)malloc(sizeof(AdjacentListNode));
    node->dest = dest;
    node->name = name;
    node->next = NULL;
    return node;
}

//? Create Graph of V vertices
Graph* create_list_graph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjacentList*)malloc(V * sizeof(AdjacentList));
    for(int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

//? Add Edge to Graph
void add_edge_list(Graph* graph, int src, char name_src, int dest, char name_dest) {
    AdjacentListNode* node = create_node(dest, name_dest);
    if (graph->array[src].head == NULL) {
        graph->array[src].head = node;
    } 
    else {
        AdjacentListNode* temp = graph->array[src].head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

//* BFS
void BFS(Graph* graph, int start_vertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for(int i = 0; i < graph->V; i++)
        visited[i] = false;

    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    visited[start_vertex] = true;
    queue[rear++] = start_vertex;

    while(front < rear) {
        int current_vertex = queue[front++];
        printf("%d ", current_vertex);
        AdjacentListNode* temp = graph->array[current_vertex].head;
        while(temp) {
            int adjVertex = temp->dest;
            if(!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue);
}

//? DFS Recursive
void DFS_Recursive(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);
    AdjacentListNode* temp = graph->array[vertex].head;
    while(temp) {
        int adjVertex = temp->dest;
        if(!visited[adjVertex]) {
            DFS_Recursive(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

//* DFS
void DFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for(int i = 0; i < graph->V; i++)
        visited[i] = false;

    DFS_Recursive(graph, startVertex, visited);

    free(visited);
}

int main() {
    int V = 7;

    //? Adjacent Matrix
    int** matrix_graph = create_matrix_graph(V);
    add_edge_matrix(matrix_graph, 0, 1); 
    add_edge_matrix(matrix_graph, 0, 2); 
    add_edge_matrix(matrix_graph, 0, 3); 
    add_edge_matrix(matrix_graph, 1, 4); 
    add_edge_matrix(matrix_graph, 3, 4); 
    add_edge_matrix(matrix_graph, 3, 5); 
    add_edge_matrix(matrix_graph, 4, 2);
    add_edge_matrix(matrix_graph, 4, 6); 
    add_edge_matrix(matrix_graph, 4, 5); 
    add_edge_matrix(matrix_graph, 6, 1); 
    add_edge_matrix(matrix_graph, 6, 5); 

    printf("Adjacency Matrix of the graph:\n");
    print_matrix_graph(matrix_graph, V);

    dispose_graph_matrix(matrix_graph, V);

    //? Adjacent List
    Graph* list_graph = create_list_graph(V);
    add_edge_list(list_graph, 0, 'a', 1, 'b'); 
    add_edge_list(list_graph, 0, 'a', 2, 'c'); 
    add_edge_list(list_graph, 0, 'a', 3, 'd'); 
    add_edge_list(list_graph, 1, 'b', 4, 'e'); 
    add_edge_list(list_graph, 3, 'd', 4, 'e'); 
    add_edge_list(list_graph, 3, 'd', 5, 'f'); 
    add_edge_list(list_graph, 4, 'e', 2, 'c'); 
    add_edge_list(list_graph, 4, 'e', 6, 'g'); 
    add_edge_list(list_graph, 4, 'e', 5, 'f'); 
    add_edge_list(list_graph, 6, 'g', 1, 'b'); 
    add_edge_list(list_graph, 6, 'g', 5, 'f'); 

    printf("\nBFS Perform:\n");
    BFS(list_graph, 0);

    printf("\nDFS Perform:\n");
    DFS(list_graph, 0);

    return 0;
}
