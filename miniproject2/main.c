#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>     //ham toupper
#include <stdio_ext.h> // __fpurge(stdin) xóa bộ đệm thay cho fllush stdin
#include "lib/graph_jrb.h"

void readFile(Graph g, char *filename);
char chuanhoa(char s2[30]);

int main()
{
    int luachon, i;
    char name[50], s1[50], s2[50], bus[4];
    char *filename = "data.txt";

    Graph graph;
    graph = createGraph();
    readFile(graph, filename);
    
    do
    {
        printf("**************************MENU**************************\n"
               "1 . Nhap ten tuyen in ra danh sach cac ben cua tuyen day \n"
               "2 . Tim duong di ngan nhat giua hai dia diem             \n"
               "3 . Liet ke tat ca cac tuyen bus di qua mot diem         \n"
               "0 . Thoat khoi chuong trinh                              \n"
               "*********************************************************\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luachon);

        switch (luachon)
        {
        case 1:
            printf("\nNhap ten tuyen bus: ");
            __fpurge(stdin);
            gets(bus);
            printf("\nDanh sach:\n");
            JRB node, tree;
            jrb_traverse(node, graph.vertices)
            {
                tree = (JRB)jval_v(node->val);
                if (jrb_find_str(tree, bus) != NULL)
                    printf("* %s\n", jval_s(node->key));
            }

            printf("\n");
            break;
        case 2:
            printf("\n\t___Tim duong di ngan nhat giua hai dia diem___\n");
            printf("Nhap ten hai dia diem: ");
            printf("\nDiem 1: ");
            __fpurge(stdin);
            gets(s1);
            printf("\nDiem 2: ");
            __fpurge(stdin);
            gets(s2);

            if (jrb_find_str(graph.vertices, s1) == NULL)
            {
                printf("Khong ton tai diem %s\n", s1);
                break;
            }
            if (jrb_find_str(graph.vertices, s2) == NULL)
            {
                printf("Khong ton tai diem %s\n", s2);
                break;
            }

            char *path[2000];
            int num_path = shortest_bus(graph, s1, s2, path);
        
            if (num_path == 0)
                printf("Khong tim duoc duong di tu %s den %s\n", s1, s2);
            else
            {
                for (i = 0; i < num_path; i++)
                {
                    printf("%s ", path[i]);
                    if(i < num_path - 1)
                        printf("- ");
                }
                printf("\n");
            }
            
                
            printf("\n");
            break;

        case 3:
            printf("\n\t___Liet ke cac tuyen bus di qua mot diem___\n\n");
            printf("Nhap ten diem: ");
            __fpurge(stdin);
            gets(name);

            JRB nodef = jrb_find_str(graph.vertices, name);
            if (nodef == NULL)
                printf("Khong ton tai ten diem: [%s]\n", name);
            else
            {
                printf("Cac tuyen bus di qua diem [%s] la: \n", name);
                JRB tree = (JRB)jval_v(nodef->val);
                JRB node1;

                jrb_traverse(node1, tree)
                    printf("\t%s\n", jval_s(node1->key));
            }
            printf("\n");
            break;
        case 0:
            break;
        default:
            printf("Vui long nhap lai !\n");
            break;
        }
    } while (luachon != 0);

    return 0;
}

void readFile(Graph g, char *filename)
{
    IS is = new_inputstruct(filename);

    if (is == NULL)
    {
        printf("File fail!\n");
        exit(1);
    }

    char *busLine; //name busline

    while (get_line(is) > 0)
    {
        if (strcmp(is->fields[0], "TUYEN") == 0) //duyệt dòng chúa tên tuyến
        {
            busLine = (char *)malloc(sizeof(char) * strlen(is->fields[1]) + 1); 
            strcpy(busLine, is->fields[1]);  // lấy tên tuyến từ trường thứ 1                                  
            continue; //xuống dòng tiếp theo
        }

        int numbus = 0;                             //số điểm dừng bus
        for (int i = 0; i < is->NF; i++)
        {
            if (strcmp(is->fields[i], "-") == 0)
                numbus++;                           //số kí tự - trong dòng
        }

        char *namebus[++numbus];        //mảng lưu tên điểm dừng bus 
        int j = 0;                      

        namebus[j] = (char *)malloc(sizeof(char) * 100);
        for (int i = 0; i < is->NF; i++)
        {
            if (strcmp(is->fields[i], "-") == 0) // Bo qua ki tu - , cap phat bo nho cho namebus[j] tiep theo, tiep tuc tao thanh ten cho 1 namebus
            {
                j++;                //thứ tự điểm dừng trong dòng
                namebus[j] = (char *)malloc(sizeof(char) * 100);
                continue;
            }
            else
            {
                strcat(namebus[j], is->fields[i]); // fix tên điẻm dừng bus
                if (i < is->NF - 1)
                    if (strcmp(is->fields[i + 1], "-") != 0)
                        strcat(namebus[j], " ");
            }
        }

        for (int i = 0; i < numbus; i++)          //Lưu tên các điểm dừng vào vertex
            addVertexbus(g, namebus[i], busLine); 
        for (int i = 0; i < numbus - 1; i++)        
            addEdgebus(g, namebus[i], namebus[i + 1]); // lưu đường đi
    }
}

//chuẩn hóa dữ liệu người dùng nhâp
char chuanhoa(char s2[30])
{
    int i = 0;
    int n = strlen(s2);
    s2[0] = toupper(s2[0]);
    for (i = 1; s2[i] != '\0'; ++i)
    {
        if (isspace(s2[i]))
        {
            s2[i + 1] = toupper(s2[i + 1]);
        }
    }
    s2[n - 1] = '\0';
    return s2;
}
