#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 50
#define INCREMENTAL_SIZE 10
typedef struct {
    char name[80];
    char number[20];
} PhoneEntry;
 
typedef struct {
    PhoneEntry *entries;
	int total;
	int size;
} PhoneBook;
 
PhoneBook* createPhoneBook() {
    PhoneBook* p= malloc(sizeof(PhoneBook));
    p->entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    p->total = 0;
    return p;
}

 
void addPhoneNumber(char* name, char* number, PhoneBook* p) {
    if(p->total != p->size) {
        for(int i = 0; i < p->total; ++i) {
            if(strcmp(name, p->entries[i].name) == 0) {
                strcpy(p->entries[i].number, number);
                return;
            }
        }
        strcpy(p->entries[p->total].name, name);
        strcpy(p->entries[p->total].number, number);
        p->total++;
    } else {
        p->entries = realloc(p->entries, sizeof(PhoneEntry) * (p->size + INCREMENTAL_SIZE));
        p->size += INCREMENTAL_SIZE;
        
    }
}
char* getPhoneNumber(char* name,const PhoneBook* p)
{
	int q=0;
	for(int i = 0; i < p->total; ++i) {
        if(strcmp(name, p->entries[i].name) == 0) {
            char* number = malloc(sizeof(char) * 20);
            strcpy(number, p->entries[i].number);
            printf("%s\n", p->entries[i].number);
            q=1;
        }  
    }
    if(q!=1){
    	printf("Khong tim thay\n");
	} 
    return NULL;
}
void printData(PhoneBook* p) {
    for(int i = 0; i < p->total; ++i) {
        printf("%s :\t%s\n", p->entries[i].name, p->entries[i].number);
    }
}
void dropPhoneBook(PhoneBook* p) {
    free(p->entries);
    free(p);
}
int main ()
{
	PhoneBook* p;
//Khoi tao & chen
	p = createPhoneBook();
	for(int i = 0; i <=100; i++) {
        char number[80];
        char name[80];
        sprintf(name, "admin%d", i);
        sprintf(number, "19478%d", i);
        addPhoneNumber( name,number, p);
    }
	addPhoneNumber("Do Lam", "909090",p);
	addPhoneNumber("Tuan Dung","929292" ,p);
	addPhoneNumber("Anh Thang","919191" ,p);
	addPhoneNumber("Ngo Phong","949494" ,p);
	addPhoneNumber("Le Linh","949495" ,p);
//Hien thi danh sach book
	printData(p);
//Tim kiem
    printf("Do Lam\t\t");
	getPhoneNumber("Do Lam", p);
	printf("Tuan Dung\t");
	getPhoneNumber("Tuan Dung", p);
	printf("Hai Tu\t");
	getPhoneNumber("Hai Tu", p);
}

