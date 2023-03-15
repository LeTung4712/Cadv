#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include "inc/btree.h"
//gcc main.c -Iinc lib/libbt.a -o main
//#include<stdio_ext.h>


int main()
{
    int i, n, size;
    long sdt;
    char name[80];
    BTA * book;
    btinit();
    book = btopn("mybook", 0, 0); //mở file mybook 
    if (!book) { // nếu chưa có file mybook
        printf("Create my book\n");
	book = btcrt("mybook", 0, 0); //tạo ra file mybook để lưu trữ cấu trúc btree
        printf("Inseet data\n");
        
        sdt = 983456789;
        if ( btins(book, "Dung", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Dung\n");
        sdt = 544545454;
        if ( btins(book, "Thang", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Thang\n");
        sdt = 466565656;
        if ( btins(book, "Huong", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Huong\n");
        sdt = 545454555;
        if ( btins(book, "Anh", (char*)&sdt, sizeof(long)) )
		printf("Error, can not insert Anh\n");
        
    }
	
    do
    {
        printf("1.Add phone\n2.Search phone\n3.Print list\n4.Del phone\n5.Exit\nYour choice:");
        scanf("%d",&n);
        while (getchar()!='\n');
        switch(n){
            case 1:
                __fpurge(stdin);
                printf("Name:");
                gets(name);
                printf("Number:");
                scanf("%ld",&sdt);
                while (getchar()!='\n');
                   if(btins(book, name, (char*)&sdt, sizeof(long))) 
			            printf("Error, can not insert %s\n",name);                   
                break;
            case 2:
                __fpurge(stdin);
                printf("Name:");
                gets(name);
                if ( btsel(book, name, (char*)&sdt, sizeof(long), &size) ) 
			        printf("Not found number for %s!\n", name);
                else 
			        printf("Phone number of %s is %ld\n", name, sdt);
                break;
            case 3:
                btsel(book, "", (char*)&sdt, sizeof(long), &size);
		        while ( btseln(book, name, (char*)&sdt, sizeof(long), &size)==0 ) 
                {
			        printf("%s\t%10ld\n", name, sdt);
                }	
                break;
            case 4:
                printf("Del name:");
                gets(name);
                //int x=btdel(book, name);
                //printf("%d",x);
                if (btdel(book, name)==0)  
			        printf("Deleted successfully %s!\n", name);
                else 
			        printf("Delete failed !\n"); 
                break;
            case 5:
                btcls(book);
                break;
          }
     }while(n!=5);
     return 0;
}
