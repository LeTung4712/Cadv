#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libfdr/fields.h"
#include "GraphAPI/graph_jrb.h"

int users;
void readfile1(Graph g, char *filename);
void readfile2(Graph g, char *filename);
void ListFriend(Graph g);
void PopularPerson(Graph g);
void CheckFriend(Graph g);
void SuggestFriend(Graph g);
void printArray(Graph g, int arr[],int arr2[], int sz);
void menu();

int main()
{     
  Graph g = createGraph();
  int selection;  
  while (selection != 6)
  {
    menu();
    scanf("%d", &selection);
    switch (selection)
    {   
      case 1:
      {
        printf("Input data 1:\n\n");
        readfile1(g, "users.txt");
        printf("\nInput data 2:\n");
        readfile2(g, "friends.txt");
        break;   
      }
      case 2:
      {
        printf("List friend:\n");
        ListFriend(g);   
        break;
      }
      case 3:
      {
        printf("Popular person\n");
        PopularPerson(g);
        break;
      }  
      case 4:
      { 
        printf("Check friend\n");
        CheckFriend(g);
        break;
      }
      case 5:
      {
        printf("Suggest friend\n");
        SuggestFriend(g);
        break;
      }  
      case 6:
        break;
      default:
        printf("Sai lua chon:");
      break;
    }
  }
  dropGraph(g);
  return 0;
}

void readfile1(Graph g, char *filename)
{
  int output[100];  
  JRB node, node1, tree;
  IS is = new_inputstruct(filename);
  if (is == NULL)
  {
    printf("File fail!\n");
    exit(1);
  }
  get_line(is);//lay dong thu nhat truoc vi lenh getline se bo qua dong da dc lay
  users = atoi(is->fields[0]);
  while ((get_line(is) > 0))
  {
    int id = atoi(is->fields[0]);
    char *name = strdup(is->fields[1]);
    addVertex(g, id, name);
  }
  jrb_traverse(node, g.vertices)
      {
        printf("%-30s %2d\n", node->val.s, node->key.i);
      }
  return users;
}

void readfile2(Graph g, char *filename)
{
  JRB node, node1, tree;
  IS is = new_inputstruct(filename);
  if (is == NULL)
  {
    printf("File fail!\n");
    exit(1);
  }
  while ((get_line(is) > 0))
  {
    for (int i = 1; i < is->NF; i++)
    {
      addEdge(g, atoi(is->fields[0]), atoi(is->fields[i]), 1);
    }
  }
  jrb_traverse(node, g.edges){
    printf("%d ", jval_i(node->key));
    tree = (JRB)jval_v(node->val);
    jrb_traverse(node1, tree)
    {
      printf("%d ", jval_i(node1->key));
    }
      printf("\n");
  }
}

void printArray(Graph g, int arr[],int arr2[], int sz)
{
  for (int i = 0; i <sz; i++)
  {
    printf("%-40s %2d\n", getVertex(g, arr[i]), arr2[i]);
  }
}

void ListFriend(Graph g)
{
  int output[100];  
  char s0[50];
  JRB node;
  printf("Nhap ten nguoi: ");
  __fpurge(stdin);
  gets(s0);
  jrb_traverse(node, g.vertices)
  {
    if(strcmp(node->val.s,s0)==0)
    {
      int n = outdegree(g,node->key.i,output);
      printf("số ban cua users:%d\n",n);
      if (n==0) printf("không có ban\n");
        else {
            printf("\n");
            for (int i=0; i<n; i++) printf("%s\n", getVertex(g,output[i]));
        }
    }
  }
}

void PopularPerson(Graph g)
{
      int n=users,output[100];  
      JRB node;
      int i = 0,k=0,temp1[100], temp2[100]; 
      jrb_traverse(node, g.vertices)
      {
        i = outdegree(g, node->key.i, output);
        temp1[k] = node->key.i;
        temp2[k] = i;
        k++;
      }

      for(int k = 0; k < n - 1; k++){
        for(int h = k + 1; h < n; h++){
            if(temp2[k] < temp2[h]){
                int tg = temp2[k];  int tg2 =temp1[k];
                temp2[k] = temp2[h];temp1[k]=temp1[h];
                temp2[h] = tg;   temp1[h]= tg2;    
            }
        }
      }
      printArray(g, temp1,temp2, k);
}

void CheckFriend(Graph g)
{
      int a,b;
      JRB node1,node2;
      char s1[50],s2[50];
      printf("Nhap ten hai nguoi: ");
      printf("\nnguoi thu 1: ");
      __fpurge(stdin);
      gets(s1);
      jrb_traverse(node1, g.vertices)
      {
        if(strcmp(node1->val.s,s1)==0)
        {
            a=node1->key.i;
        }
      }
      printf("\nnguoi thu 2: ");
      __fpurge(stdin);
      gets(s2);
      jrb_traverse(node2, g.vertices)
      {
        if(strcmp(node2->val.s,s2)==0)
        {
          b=node2->key.i;
        }
      }
            int check;
            check=hasEdge(g,a,b);
        
            if (check == 0)
            {
                printf("khong phai ban be\n");
            }    
            else
            {
                printf("La ban be\n");
            }
            
            printf("\n");
}

void menu()
{
    printf("--------------------Menu-----------------\n");
    printf("1. Input Data \n"
            "2. List friend\n"
            "3. Popular person\n"
            "4. Check friend\n"
            "5. Suggest friend\n"
            "6. Thoat\n");
    printf("--------------------End-----------------\n");
    printf("---> Chon:\n");
}

void SuggestFriend(Graph g)
{
  int a,b,check,temp1[100], temp2[100];
  int x,y;
  JRB node1,node2;
  char s1[50];
  printf("\nnhap vao: ");
  __fpurge(stdin);
  gets(s1);
  jrb_traverse(node1, g.vertices)
  {
    if(strcmp(node1->val.s,s1)==0)
    {
      a=node1->key.i;
      x= outdegree(g, node1->key.i, temp1);
    }
  }
  printf("goi y ket ban: \n");
  jrb_traverse(node2,g.edges)
  {
    b=node2->key.i;
    if(b==a) continue;
    check=hasEdge(g,a,b);
    if(check!=0)
    {
        continue;
    }else{
        y= outdegree(g, b, temp2);
        for(int i=0;i<x;i++){
          for(int j=0;j<y;j++){
            if(temp1[i]==temp2[j])
            {
              printf("%s\n",getVertex(g,b));
            }else continue;
          }
        }
      }

  }
}