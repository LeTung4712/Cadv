#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "dllist.h"
//gcc main.c jrb.c jval.c dllist.c -o dothi 
typedef struct {
    JRB edges;
    JRB vertices;
    
} Graph;

Graph createGraph();//khởi tạo 
void addVertex(Graph g, int id, char* name);//thêm id và tên đỉnh
char *getVertex(Graph g, int id);// nhận vào id trả về tên của id 
void addEdge(Graph g, int v1, int v2); //thêm đỉnh vào đò thị
int hasEdge(Graph g, int v1, int v2); //kiểm tra xem hai đỉnh có liên kết với nhau không 
int indegree(Graph g, int v, int* output); //trả về  các đinh nối đến đỉnh v
int outdegree(Graph g, int v, int* output);// trả về  các đỉnh nối ra từ đỉnh v
int DAG(Graph g);// kiểm tra đường đi có hướng và chu trình có hướng
int topologicalSort(g, output);
void dropGraph(Graph g);

int main()
{
     int i,n,output[100];
     Graph g=createGraph();
     addVertex(g, 1, "CS140");
     addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
     addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
     addEdge(g, 1, 2); addEdge(g,1, 3);
     addEdge(g, 2, 3); addEdge(g,2, 4);
     addEdge(g, 3, 4); addEdge(g,3,5);
     printf("insert thành công\n");
//kiểm tra tên của id
     printf("id 1 co name la :%s\n",getVertex( g,1));
     printf("id 0 co name la :%s\n",getVertex( g,0));
     printf("id 5 co name la :%s\n",getVertex( g,5));
//kiểm tra xem có đường nối từ id đến id 2 không
     printf("có đường từ 1 đến 2 không ?\t");
     n=hasEdge(g,1,2);
     if(n==1)printf("có\n");
     else printf("không\n");
//số id nối vào đỉnh  có id là 1
     n = indegree(g,1,output);
     printf("số id nối đến đỉnh id 1: %d\n",n); 

     if (n==0) printf("không có id nào nối đén id 1\n");
     else {
         printf("các id nối đến id 1:");
         for (i=0; i<n; i++) printf("%5d", output[i]);
          printf("\n");
     }
//số id nối ra từ đỉnh có id là 1
     n = outdegree(g,1,output);
     printf("số id nối ra từ đỉnh id 1: %d\n",n);

     if (n==0) printf("không có cạnh nào nối đén id 1\n");
     else {
         printf("các id nối ra từ id 1:");
         for (i=0; i<n; i++) printf("%5d", output[i]);
          printf("\n");
     }
//
     if (DAG(g)==1) { 
          n=topologicalSort(g, output);
          printf("The topological order:\n");
          for (i=0; i<n; i++){
               printf("%s\n", getVertex(g, output[i]));
          }   
     }else printf("Can not make topological sort \n"); 

     dropGraph(g);
            
     return 0;
}

Graph createGraph()
{
    Graph g;
    g.edges=make_jrb();
    g.vertices=make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name)
{
     JRB node;
     node = jrb_find_int(g.vertices, id);
     if (node!=NULL) {        
          node->val = new_jval_s(name);  
     } else {
          jrb_insert_int(g.vertices, id, new_jval_s(name));       
     }

}

char *getVertex(Graph g,int id)
{
    JRB node;
    node=jrb_find_int(g.vertices,id);
    if(node==NULL)
        return NULL;
    else return jval_s(node->val);
}

void addEdge(Graph g, int v1, int v2)
{
     JRB node,tree;
     tree=make_jrb();
     node = jrb_find_int(g.edges, v1);
     if (node!=NULL) {
     // node v1 đã được chèn vào         
          tree = (JRB) jval_v(node->val);
          jrb_insert_int(tree, v2, new_jval_i(1)); 
     } else {
     // not found, insert a new entry
          jrb_insert_int(g.edges, v1, new_jval_v(tree));
          jrb_insert_int(tree, v2, new_jval_i(1));    
     }

}

int hasEdge(Graph g,int v1,int v2)
{
     JRB node,tree;
     node=jrb_find_int(g.edges,v1);
     if(node==NULL)
          return 0;
     else
     {
          tree=(JRB) jval_v(node->val);
          jrb_traverse(node,tree)
     if(v2==jval_i(node->key))
          return 1;
     }
     return 0;
}

int indegree(Graph g,int v,int* output)
{
     JRB node,tree;
     int total;
     node=jrb_find_int(g.edges,v);
     if(node==NULL)
          return 0;
     else
     {
          tree=(JRB) jval_v(node->val);
          total=0;
          jrb_traverse(node,tree)
          output[total++]=jval_i(node->key);
          return total;
     }
}

int getAdjacentVertices(Graph g,int v,int*output)
{
     JRB node,tree;
     int total = 0;
     node = jrb_find_int(g.edges, v);
     if(node!=NULL)
     {   
          tree = (JRB) jval_v(node->val);
          jrb_traverse(node, tree)
          output[total++] = jval_i(node->key);
     }else return total;
     return total;
}

int outdegree(Graph graph,int v,int*output)
{
     JRB node,tree;
     node=NULL;
     int key;
     int total;
     total=0;
     jrb_traverse(node,graph.vertices)
     {
          key=jval_i(node->key);
          if(hasEdge(graph,key,v)==1)
          output[total++]=key;
     }
     return total;
}

int DAG(Graph graph)
{
   int visited[1000];
   int n, output[100], i, u, v, start;
   Dllist node, stack;
   JRB vertex;
   
   jrb_traverse(vertex, graph.vertices)
   {
       memset(visited, 0, sizeof(visited));

       start = jval_i(vertex->key);              
       stack = new_dllist();
       dll_append(stack, new_jval_i(start));
    
       while ( !dll_empty(stack) )
       {
          node = dll_last(stack);
          u = jval_i(node->val);
          dll_delete_node(node);
          if (!visited[u])
          {
              visited[u] = 1;
              n = outdegree(graph, u, output);
              for (i=0; i<n; i++)
              {
                  v = output[i];
                  if ( v == start ) // cycle detected 
                     return 0;
                  if (!visited[v])    
                     dll_append(stack, new_jval_i(v));
              }
          }           
       }
   }
   return 1; // no cycle    
}

void swapArray(int arr[], int cnt)
{
    for (int i = 0; i < cnt / 2; i++)
    {
        int c = arr[i];
        arr[i] = arr[cnt - i - 1];
        arr[cnt - i - 1] = c;
    }
}

int topologicalSort(Graph graph, int *output)
{
    int indeg[1000], tmp[100];
    Dllist queue, node;
    queue = new_dllist();

    JRB vertex;
    jrb_traverse(vertex, graph.vertices)
    {
        int u = jval_i(vertex->key);
        indeg[u] = indegree(graph, u, tmp);
        if (indeg[u] == 0)
            dll_append(queue, new_jval_i(u));
    }

    int total = 0;
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        int u = jval_i(node->val);
        dll_delete_node(node);
        output[total++] = u;

        int m = outdegree(graph, u, tmp);
        for (int i = 0; i < m; i++)
        {
            int v = tmp[i];
            indeg[v]--;
            if (indeg[v] == 0)
                dll_append(queue, new_jval_i(v));
        }
    }
    swapArray(output, total);
    return total;
}

void dropGraph(Graph g)
{
     JRB node, tree;
    jrb_traverse(node, g.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(g.edges);
    jrb_free_tree(g.vertices);
}


