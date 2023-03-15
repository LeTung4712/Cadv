#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>//ham toupper
#include <stdio_ext.h>// __fpurge(stdin) xóa bộ đệm thay cho fllush stdin
#include "lib/graph_jrb.h"


int checkArgv(int argc, char *argv[]);
void print_help();
void readFile(Graph g, char *filename, JRB name_ID);
//int hasEdge(Graph g, int v1, int v2);
char chuanhoa(char s2[30]);
int havemore();

int main(int argc, char *argv[])
{
    if (argc != 2) {
        print_help();
        return 1;
    }
    if(checkArgv(argc, argv)==1){
        int i,n,output[100];
        Graph g = createGraph();
        JRB name_ID = make_jrb();
        readFile(g, argv[1],name_ID);
        int selection;
        do
        {
            printf(
                "\n============================MENU===========================\n"
                "*  1. In so nut va so canh!\n"
                "*  2. In ra thong tin cong viec muon tim kiem\n"
                "*  3. In ra trinh tu cac cong viec(topo sort)\n"
                "*  4. In ra thoi gian toi thieu thuc hien cong viec(longestPath)\n"
                "*  5. Kiem tra chu trinh do thi(DAG)\n"
                "*  0. Thoat!\n"
                "============================================================\n"
                "---> Chon: ");
            scanf("%d", &selection);

            switch (selection)
            {
            case 1:
            {
                JRB node,nodee;
                printf("So dinh: %d\n", getNumOfV(g));
                printf("So canh: %d\n",getNumOfEdge(g));
                //n = indegree(g, 1, output);
                //printf("%d\n",n);
            }
                break;
        
            case 2:
            {
                int sum ,length, path[1000];
                do
                {
                    char *ID = (char *)malloc(sizeof(char) * 5);
                    __fpurge(stdin);

                    printf("Nhập công việc: ");
                    gets(ID);
                    JRB find = jrb_find_str(name_ID, ID);
                    if(find!=NULL){
                        n = indegree(g,find->val.i,output);
                        printf("Số công việc ngay trước: %d\n",n);
                        if (n==0) printf("không cần làm việc nào trước công việc 5\n");
                        else {
                            printf("Là các công việc:");
                                for (i=0; i<n; i++) 
                            {
                                printf(" %5s ", getVertex(g,output[i]));
                                printf("\n");
                            }
                            sum=topo(g, find->val.i,path);
                            printf("tổng các công việc trước đó %d . Là :",sum);
                            for (i=0; i<sum; i++) 
                            {
                                printf(" %5s ", getVertex(g,path[i]));
                            
                            }
                        }
                    }else printf("Không có công việc này ! \n");
                }while(havemore());
            }
                break;
            case 3:
            {
                if (DAG(g)==1) { 
                    n=topologicalSort(g, output);
                    printf("Thứ tự trước sau:\n");
                    for (i=0; i<n; i++){
                        printf(" %s\t", getVertex(g, output[i]));
                    }   
                }else printf("Can not make topological sort \n"); 
                break;
            }  
            case 4:
            {
                __fpurge(stdin);
                int s=1, length, path[1000];
                char *ID = (char *)malloc(sizeof(char) * 5);
                
                printf("Nhập công việc: ");
                nhap:
                gets(ID);
                JRB find = jrb_find_str(name_ID, ID);
                if(find!=NULL){
                    double weight = longestPath(g, s, find->val.i, path, &length);
                    if (weight != INFINITIVE_VALUE)
                    {
                        printf("\nThời gian tối thiểu để làm công việc: %.lf (h)\n", weight);
                    }
                }else printf("không có công việc %s  \n",ID);

                break;
            }
            case 5:
            {
                if (DAG(g))
                printf("The graph is acycle\n");    //không có chu trình
                else
                    printf("Have cycles in the graph\n"); // có chu trình
            }
                break;
            case 0:
            
                break;
            default:
                printf("---> Nhap lai!\n");
                break;
            }
        }while (selection != 0);

        dropGraph(g);
        return 0;
    }else if(checkArgv(argc,argv)==2)printf("\nBài kiểm tra giữa kỳ 20212\n\n");
}

void print_help() 
{
        fprintf(stderr,"USAGE: ./main [filename]\n");
}

//check dau vao
int checkArgv(int argc, char *argv[])
{
    if (argc == 2 && (strcmp(argv[1], "congviec.txt") == 0))
        return 1;
    if(argc == 2 && (strcmp(argv[1], "about") == 0))
        return 2;
    else return 0;
}

int havemore()
{
    char ch;
    int valid;
    do
    {
        printf("\nBạn có muốn nhập lại không Y/N?\n");
        ch=getchar();
        ch = tolower(ch);
        if(ch =='y')
           valid = true;
        else if(ch =='n')
           valid = false;
        else
           printf("Invalid input. Try again.");
    }while(ch != 'y' && ch != 'n');
    return valid;
}

//chuẩn hóa dữ liệu người dùng nhâp
char chuanhoa(char s2[5])
{
    int i=0;
    int n=strlen(s2);
    s2[0]=toupper(s2[0]);
    for(i=1;s2[i]!='\0';++i)
    {
        if(isspace(s2[i]))
        {
            s2[i+1]=toupper(s2[i+1]);
        }
    }
    s2[n - 1] = '\0'; 
    return s2;  
}

//đọc file
void readFile(Graph g, char *filename, JRB name_ID)
{   
    IS is = new_inputstruct(filename);
    if (is == NULL)
    {
        printf("Error: File Fail!\n");
        exit(1);
    }
    int i=0;
    const char s[2] = "-";
    while (get_line(is) >= 0) 
    {
        //get_line(is) nhận vào số miền trong dòng
        char *ID1 = (char *)malloc(sizeof(char) * 5);
        strcpy(ID1, is->fields[0]);
        JRB find = jrb_find_str(name_ID, ID1);
        if (find == NULL)
        {
            i++;
            jrb_insert_str(name_ID, strdup(ID1), new_jval_i(i));
            addVertex(g, i, ID1);
        }
        for(int q=1;q<is->NF-1;q++)
        { 
              
            char *temp = (char *)malloc(sizeof(char) * 20);
            char *ID2 = (char *)malloc(sizeof(char) * 5);
            char *weight= (char *)malloc(sizeof(char) * 5);
            if (ID2 == NULL)
            {
                printf("Co loi! khong the cap phat bo nho.");
                exit(0);
            }
            
            strcpy(temp, is->fields[q+1]);
            char *check = strchr(temp, '-'); 
            if (check != NULL)
            {
                
                ID2 = strtok(temp, s);
                weight=strtok(NULL, s);
                double val=atof(weight);
                JRB find1 = jrb_find_str(name_ID, ID1);
                JRB find2 = jrb_find_str(name_ID, ID2);   
                //addEdge(g, i, find2->val.i, val);
                addEdge(g, find2->val.i, i, val);

              
            }
            free(ID1);
            free(temp); 
        }
    
    }
}
