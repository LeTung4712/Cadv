#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PHONE_NUMBER 1000
typedef struct 
{
	char name[80];
	char number[10];
} PhoneEntry;

typedef struct 
{
	PhoneEntry entries[MAX_PHONE_NUMBER];
	int total;
} PhoneBook;

PhoneBook* createPhoneBook(){
	PhoneBook* p = malloc(sizeof(PhoneBook));
    p->total = 0;
    return p;
}
void dropPhoneBook(PhoneBook* p)
{
	free(p->entries);
    free(p);
}
void addPhoneNumber(char* name, char* number, PhoneBook* p)
{
	for(int i = 0; i < p->total; ++i) {
        if(strcmp(name, p->entries[i].name) == 0) {
            strcpy(p->entries[i].number, number);
            return;
        }
    }
    strcpy(p->entries[p->total].name, name);
    strcpy(p->entries[p->total].number, number);
    p->total++;
}
char* getPhoneNumber(char* name,const PhoneBook* p)
{
	int q=0;
	for(int i = 0; i < p->total; ++i) {
        if(strcmp(name, p->entries[i].name) == 0) {
            char* number = malloc(sizeof(char) * 10);
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
int main ()
{
	PhoneBook* p;
//Khoi tao & chen
	p = createPhoneBook();
	addPhoneNumber("Do Lam", "909090",p);
	addPhoneNumber("Tuan Dung","929292" ,p);
	addPhoneNumber("Anh Thang","919191" ,p);
	addPhoneNumber("Ngo Phong","949494" ,p);
	addPhoneNumber("Le Linh","949495" ,p);
//Hien thi danh sach book
	printData(p);
//Tim kiem
    printf("Do Lam\t");
	getPhoneNumber("Do Lam", p);
	printf("Tuan Dung\t");
	getPhoneNumber("Tuan Dung", p);
	printf("Hai Tu\t");
	getPhoneNumber("Hai Tu", p);
}
