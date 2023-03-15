#include <stdio.h>
#include <stdio_ext.h> // __fpurge(stdin);
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "jrb.h"
//gcc main.c -Ilib libfdr.a -lncurses -o main

int main()
{
    int i, n;
    int value,key;
    JRB tree, node;
    
    tree = make_jrb();
    
    jrb_insert_int(tree,2 , new_jval_i(0));
    jrb_insert_int(tree,10, new_jval_i(0));
    jrb_insert_int(tree,3 , new_jval_i(0));
    jrb_insert_int(tree,19, new_jval_i(0));
    jrb_insert_int(tree,4 , new_jval_i(0));
    jrb_insert_int(tree,8 , new_jval_i(0));
    
    do
    {
        //system("clear");//trong win thi dung system("cls")
        printf("1.Add \n2.Print list(traverse)\n3.Exit\nYour choice:");
        scanf("%d",&n);
        switch(n){
              case 1:
                   printf("Number:");
                   scanf("%d",&key);
                   jrb_insert_int(tree, key, new_jval_i(0));    
                   break;

              case 2:
                    jrb_traverse(node, tree)
                    printf("%d,", jval_i(node->key));
                    printf("\n");
                   break;
            
              case 3:         
                    jrb_free_tree(tree);
                   break;
          }
     }while(n!=3);
     return 0;
}
