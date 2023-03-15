#include <stdio.h>
#include <stdio_ext.h> // __fpurge(stdin);
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "jrb.h"
//gcc main.c jrb.c jval.c -lncurses -o main

int main()
{
    int i, n;
    long sdt;
    char name[80];
    JRB book, node;
    
    book = make_jrb();
    
    jrb_insert_str(book, strdup("Dung"), new_jval_l(983456789));
    jrb_insert_str(book, strdup("Thang"), new_jval_l(945678978));
    jrb_insert_str(book, strdup("Huong"), new_jval_l(123456789));
    jrb_insert_str(book, strdup("Anh"), new_jval_l(983984775));
    
    do
    {
        //system("clear");//trong win thi dung system("cls")
        printf("1.Add phone\n2.Search phone\n3.Print list(traverse)\n4.Print list(rtraverse)\n5.Exit\nYour choice:");
        scanf("%d",&n);
        switch(n){
              case 1:
                   __fpurge(stdin);
                   printf("Name:");
                   gets(name);
                   __fpurge(stdin);
                   printf("Number:");
                   scanf("%d",&sdt);
                   node = jrb_find_str(book, name);
                   if (node!=NULL) {
                      // overwrite the value of this node       
                      node->val = new_jval_l(sdt);       
                   } else {
                      // not found, insert a new entry
                      jrb_insert_str(book, strdup(name), new_jval_l(sdt));    
                   }
                   break;
              case 2:
                   __fpurge(stdin);
                   printf("Name:");
                   gets(name);
                   node = jrb_find_str(book, name);
                   if (node==NULL) printf("Not found number for %s!\n", name);
                   else printf("Phone number of %s is %d\n", name, jval_l(node->val));
                   getch();
                   break;
              case 3:
                   jrb_traverse(node, book)
                       printf("%-15s%10d\n", jval_s(node->key), jval_l(node->val));
                   getch();
                   break;
              case 4:
                    jrb_rtraverse(node,book)
                         printf("%-15s%10d\n", jval_s(node->key), jval_l(node->val));
                    getch();
                    break;
              case 5:         
                   jrb_traverse(node, book)
                       free(jval_s(node->key));
                   jrb_free_tree(book);
                   break;
          }
     }while(n!=5);
     return 0;
}
