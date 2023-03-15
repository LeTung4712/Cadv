#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "dllist.h"
#define INFINITIVE_VALUE  10000000
//gcc main.c jrb.c jval.c dllist.c -o dothi 
typedef struct {
    JRB edges;
    JRB vertices;
    
} Graph;

Graph createGraph();//khởi tạo 
void addVertex(Graph g, int id, char* name);//thêm id và tên đỉnh
char *getVertex(Graph g, int id);// nhận vào id trả về tên của id 
void addEdge(Graph g, int v1, int v2,double weight); //thêm cạnh nối từ v1 v2 vào đò thị
double getEdgeValue(Graph graph, int v1, int v2); // trảvề INFINITIVE_VALUE nếukhôngcócạnhgiữav1 vàv2
int outdegree(Graph g, int v, int* output);// trả về  các đỉnh nối ra từ đỉnh v
double shortestPath(Graph graph, int s, int t, int* path, int*length);// return tổng giá trị đường đi, đường đi. ReturnINFINITIVE_VALUE nếu không tìm thấy đường đi
void dropGraph(Graph g);

int main()
{
     int i,n,output[100];
     Graph g=createGraph();
     addVertex(g, 0, "V0");
     addVertex(g, 1, "V1");
     addVertex(g, 2, "V2");
     addVertex(g, 3, "V3");
     addEdge(g, 0, 1, 1);
     addEdge(g, 1, 2, 2);
     addEdge(g, 2, 3, 2);
     addEdge(g, 3, 4, 2);
     addEdge(g, 2, 0, 3);
     addEdge(g, 1, 3, 1);
     printf("insert thành công\n");
//kiểm tra tên của id
     printf("id 1 co name la :%s\n",getVertex( g,1));
//trả về trong số hai đỉnh đưa vào
     printf("weight (0,4) là:%lf\n",getEdgeValue(g,0,4));
//
     int s=0,t=4, length, path[1000];
     double weight = shortestPath(g, s, t, path, &length);
     if (weight == INFINITIVE_VALUE)printf("No path between %d and %d\n", s, t);
     else {printf("Path between %d and %d:", s, t);
          for (i=0; i<length; i++) printf("%4d", path[i]);
          printf("\nTotal weight: %f\n", weight);
     }

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

void addEdge(Graph graph, int v1, int v2, double weight)
{
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
            tree = (JRB)jval_v(node->val);

        jrb_insert_int(tree, v2, new_jval_d(weight));
    }

}

double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return INFINITIVE_VALUE;
    tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return INFINITIVE_VALUE;
    else
        return jval_d(node->val);
}

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
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

double shortestPath(Graph graph, int s, int t, int *path, int*length)
{
    double distance[1000];
    int previous[1000], u, visit[1000];

    for (int i = 0; i < 1000; i++)
    {
        distance[i] = INFINITIVE_VALUE;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visit[s] = 1;

    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));

    while (!dll_empty(queue))
    {
        double min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue)
        {
            u = jval_i(ptr->val);
            if (min > distance[u])
            {
                min = distance[u];
                node = ptr;
            }
        }

        u = jval_i(node->val);
        visit[u] = 1;
        dll_delete_node(node);
        if (u == t)
            break;

        int output[1000];
        int n = outdegree(graph, u, output);

        for (int i = 0; i < n; i++)
        {
            int v = output[i];
            double w = getEdgeValue(graph, u, v);
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            if (visit[v] == 0)
            {
                dll_append(queue, new_jval_i(v));
            }
        }
    }

    double distance_s_t = distance[t];
    int count = 0;
    if (distance[t] != INFINITIVE_VALUE)
    {
        path[count++] = t;
        while (t != s)
        {
            t = previous[t];
            path[count++] = t;
        }
        *length = count;
    }
    swapArray(path, count);
    return distance_s_t;
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


