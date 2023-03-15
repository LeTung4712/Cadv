#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
//gcc main.c jrb.c jval.c -o dothi -g
typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int v,int* output); // return the number of adjacent vertices.
void dropGraph(Graph graph);

Graph createGraph()
{
    Graph g; 
    g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2)
{
     JRB node,tree;
     tree=make_jrb();
     node = jrb_find_int(g, v1);
     if (node!=NULL) {
     // node v1 đã được chèn vào         
          tree = (JRB) jval_v(node->val);
          jrb_insert_int(tree, v2, new_jval_i(1)); 
     } else {
     // not found, insert a new entry
          jrb_insert_int(g, v1, new_jval_v(tree));
          jrb_insert_int(tree, v2, new_jval_i(1));    
     }

}

int getAdjacentVertices(Graph g,int v,int*output)
{
     JRB node,tree;
     int total = 0;
     node = jrb_find_int(g, v);
     if(node!=NULL)
     {   
          tree = (JRB) jval_v(node->val);
          jrb_traverse(node, tree)
          output[total++] = jval_i(node->key);
     }else return total;
     return total;
}

void dropGraph(Graph g)
{
     JRB node;
     jrb_traverse(node, g)
     jrb_free_tree( jval_v(node->val) );
}
int main()
{
     int i,n,output[100];
     Graph g=createGraph();
     JRB node;
     addEdge(g, 1, 2);
     addEdge(g, 1, 3);
     addEdge(g, 1, 4);
     addEdge(g, 1, 5);
     addEdge(g, 0, 6);
     addEdge(g, 0, 7);
     addEdge(g, 0, 3);
     addEdge(g, 0, 2);
     addEdge(g, 2, 3);

     printf("insert thành công\n");

     n = getAdjacentVertices (g, 1,output);
     printf("số đỉnh kề :%d\n",n);
     if (n==0) printf("No adjacent vertices of node 1\n");
     else {
         printf("Adjacent vertices of node 1:");
         for (i=0; i<n; i++) printf("%5d", output[i]);
          printf("\n");
     }

     n = getAdjacentVertices (g, 0, output);
     printf("số đỉnh kề :%d\n",n);
     if (n==0) printf("No adjacent vertices of node 0\n");
     else {
         printf("Adjacent vertices of node 0:");
         for (i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
     }  

     dropGraph(g);
            
     return 0;
}