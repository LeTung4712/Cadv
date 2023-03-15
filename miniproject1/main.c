#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"inc/fields.h"
#include"inc/soundex.h"
#include<stdio_ext.h>
#include "inc/btree.h"
#define MAXC 1001

typedef struct dictionary{
    char *vocab;//vocabulary
    char *mean;
}Dict;

char*test(char *c);
void readFile(BTA *dict,BTA *encode,char *filename);

int main()
{
    int i, n, size;
    char voca[80],means[80],code[80],fvoca[80];
    BTA * dict; //btree database.
    BTA * encode; 
    btinit();   //initialise B tree tables 
    dict = btopn("mydictionary", 0, 0); //mở database mydictionary
   //btinit();
    encode =btopn("encode",0,0);    //mở database encode
    if (!dict) { // nếu chưa có file mydictionary
        printf("\nCreate my dictionary\n");
        dict = btcrt("mydictionary", 0, 0); //tạo ra file mydictionary để lưu trữ cấu trúc btree
        encode=btcrt("encode",0,0); //tạo ra file encode để lưu trữ mã hóa từ
        char filename[] = "tudien.txt";
        readFile(dict,encode,filename);
    }
	
    do
    {
        printf("\n==============VOCABULARY============");
        printf("\n1.Add vocabulary\n2.Search vocabulary\n3.Print dict\n4.Del vocabulary\n5.printf soundex\n6.Exit");
        printf("\n====================================\nYour choice:");
        scanf("%d",&n);
        while (getchar()!='\n');
        switch(n){
            case 1:
                __fpurge(stdin);
                printf("\nVocabulary:");
                gets(voca);
                printf("Means:");
                gets(means);
                
                if ( btsel(dict, voca, means, MAXC, &size))
                { 
			        if(btins(dict, voca,means, 1+strlen(means))) 
                        // -------------------NOTE 1+strlen
			            printf("\nError, can not insert %s\n",voca);
                    else 
                    {
                        printf("Insert successfully ! \n");
                        if(btins(encode,voca,test(voca),1+strlen(voca))) 
                        // ----------------------------NOTE 1+strlen
			                printf("\nError, can not insert soundex %s\n",voca);   
                    }    
                }
                else
                {
                    printf("\nVocabulary already exists !\n"); //đã tồn tại 
                    if (btupd(dict,voca,means,1+strlen(means)))
                        printf("update failed !\n");
                    else printf("Updated successfully !\n");
                }                      
                break;
            case 2:
                __fpurge(stdin);
                printf("\nVocabulary you want to find: ");
                gets(fvoca);     
                btsel(encode,"",code,MAXC, &size);// duyệt cây btree
		            while ( btseln(encode,voca,code, MAXC, &size)==0 ) 
                    {
                        if (strcmp(code,test(fvoca))==0)
                        {
			                if ( btsel(dict, voca, means, MAXC, &size) ) 
			                    printf("\nNot found means for ' %s '!\n", voca);
                            else 
			                    printf("\nMeans of ' %s ' is: %s .\n", voca, means);
                        }
                    }
                	
                break;
            case 3:
                btsel(dict,"", means,MAXC, &size);
		        while ( btseln(dict,voca , means, MAXC, &size)==0 ) 
                {
			        printf("%-20s  %s\n",voca,means);
                }	
                break;
            case 4:
                __fpurge(stdin);
                printf("\nVocabulary you want to delete: ");
                gets(voca); 
                if(btdel(dict,voca)==0)
                {
                    printf("\ndeleted vocabulary !");
                    if(btdel(encode,voca)==0)
                        printf("\ndeleted soundex of %s !",voca);
                }
                break;
            case 5:// printf table soundex code
                btsel(encode,"", means,MAXC, &size);
		        while ( btseln(encode,voca,code, MAXC, &size)==0 ) 
                {
			        printf("%-20s  %s\n",voca,code);
                }	
                break;
            case 6:
                btcls(dict);
                btcls(encode);
                break;
        }    
     }while(n!=6);
     return 0;
}

char *fixMeans(char *s)
{
    int n = strlen(s);
    char *s1 = (char *)malloc(sizeof(char) * n);
    for (int i = 0; i < n - 1; i++)
    {
        s1[i] = s[i];
    }
    s1[n - 1] = '\0'; //cho khoảng tráng về sau chuỗi mới
    return s1;
}

char *test(char *c)
{   
    char *s1 = (char*)malloc(sizeof(char)*6);
    soundex(c, s1);
    //printf("%-20s%-6s\n", c, s1);
    return s1;
}

void readFile(BTA *dict,BTA *encode,char *filename)
{
    Dict *p;   // khai báo struct dictionary
    IS is;      //làm việc với file
    int i=0;
    is = new_inputstruct(filename); 
    if (is == NULL)
    {
        printf("Error: File Fail!\n");
        exit(1);
    }
    printf("Inseet data\n");
    const char s[1] =":";
    p = (Dict *)malloc(sizeof(Dict)*MAXC); //cấp phát cho struct p
    p->vocab = (char *) malloc(sizeof(char)*40);
    p->mean  = (char *) malloc(sizeof(char)*40); 
        if (p->vocab == NULL)
        {
            printf("Co loi! khong the cap phat bo nho.");
            exit(0);
        }
    while(get_line(is)>=0)
    {
        i++;
        
        char *check = strchr(is->text1,':'); 
        if (check != NULL)
        {
            p->vocab = strtok(is->text1, s);
            p->mean = strtok(NULL, s);
            if(btins(dict, p->vocab,fixMeans(p->mean) , strlen(p->mean)))
                printf("Error, can not insert %d\n",i);
            if(btins(encode,p->vocab,test(p->vocab),1+strlen(p->vocab)))
                printf("Error, can not insert soundex\n");                                   
        }                                                                   
    }       
}
