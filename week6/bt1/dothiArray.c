#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int * matrix;
    int sizemax;
} Graph;

Graph createGraph(int sizemax);
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int* output); // return the number of adjacent vertices.
void dropGraph(Graph graph);

Graph createGraph(int sizemax)
{
    Graph graph;
    graph.matrix=(int*)malloc(sizeof(int)*sizemax*sizemax);
    for(int i=0;i<sizemax*sizemax;i++)
        graph.matrix[i]=0;
        graph.sizemax=sizemax;
    return graph;

}

void addEdge ( Graph graph , int v1 , int v2 )
{
    graph . matrix [ v1 * graph . sizemax + v2 ]= 2 ; 
    graph . matrix [ v2 * graph . sizemax + v1 ]= 2 ;
    //a[v1][v2] luôn gans bằng 2
} 
/*
int adjacent ( Graph graph , int v1 , int v2 )
{ 
    return graph . matrix [ v1 * graph . sizemax + v2 ]== 2; 
}
*/
int getAdjacentVertices ( Graph graph , int vertix , int * output )
{ 
    int i , k = 0 ; 
    for ( i = 0 ; i < graph . sizemax ; i ++) 
        { 
            if ( graph . matrix [ vertix * graph . sizemax + i ]== 2 ) {
                output [ k ]= i ; 
                k++; 
            } 
        }
    return k ; 
} 

void dropGraph ( Graph graph )
{ 
    free ( graph . matrix ); 
}

int main()
{
    int i, n, output[100];
    Graph g = createGraph(100);
    
    addEdge(g, 1, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 1, 5);
    addEdge(g, 1, 6);
    addEdge(g, 0, 3);
    addEdge(g, 0, 7);
    addEdge(g, 2, 3);
    addEdge(g, 0, 2);
    addEdge(g, 0, 1);

    n = getAdjacentVertices (g, 1, output);
    printf("số đỉnh:%d\n",n);
    if (n==0) printf("No adjacent vertices of node 1\n");
    else {
        printf("Adjacent vertices of node 1:");
        for (i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
    }
    
    n = getAdjacentVertices (g, 3, output);
    printf("số đỉnh:%d\n",n);
    if (n==0) printf("No adjacent vertices of node 0\n");
    else {
        printf("Adjacent vertices of node 0:");
        for (i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
    }

    dropGraph(g);
    return 0;
}
