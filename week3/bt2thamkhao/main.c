#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    char name[80];
    char number[20];
} PhoneEntry;
 
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10
 
typedef struct {
    PhoneEntry* entries;
    int total;
    int ceil;
} PhoneBook;
 
PhoneBook* createPhoneBook() {
    PhoneBook* pb = malloc(sizeof(PhoneBook));
    pb->entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    pb->total = 0;
    return pb;
}
void dropPhoneBook(PhoneBook* book) {
    free(book->entries);
    free(book);
}
void addPhoneNumber(char*, char*, PhoneBook*);
char* getPhoneNumber(char*, const PhoneBook*);
 
int binarySearch(PhoneEntry* entries, int l, int r, char* name, int* found) {
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (strcmp(entries[mid].name, name) == 0) {
            *found = 1;
            return mid; 
        }
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (strcmp(entries[mid].name, name) > 0) 
            return binarySearch(entries, l, mid - 1, name, found); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(entries, mid + 1, r, name, found); 
    }
  
    // We reach here when element is not 
    // present in array
    *found = 0;
    return l; 
}
 
void addPhoneNumber(char* number, char* name, PhoneBook* book) {
    if(book->total != book->ceil) {
        int foundEntry;
        int indexFound = binarySearch(book->entries, 0, book->total - 1, name, &foundEntry);
        if(foundEntry == 1) {
            strcpy(book->entries[indexFound].number, number);
            return;
        } else {
            for(int i = book->total;i >= indexFound; i--)
                book->entries[i] = book->entries[i-1];
            /* insert value at the proper position */
            strcpy(book->entries[indexFound].name, name);
            strcpy(book->entries[indexFound].number, number);
            book->total++;
        }
 
    } else {
        book->entries = realloc(book->entries, sizeof(PhoneEntry) * (book->ceil + INCREMENTAL_SIZE));
        book->ceil += INCREMENTAL_SIZE;
        return addPhoneNumber(number, name, book);
    }
}
char* getPhoneNumber(char* name, const PhoneBook* book) {
    for(int i = 0; i < book->total; ++i) {
        if(strcmp(name, book->entries[i].name) == 0) {
            char* number = malloc(sizeof(char) * 20);
            strcpy(number, book->entries[i].number);
            return number;
        }
    }
    return NULL;
}
 
char* getNumberOwner(char* number, const PhoneBook* book) {
    for(int i = 0; i < book->total; ++i) {
        if(strcmp(number, book->entries[i].number) == 0) {
            char* name = malloc(sizeof(char) * 80);
            strcpy(name, book->entries[i].name);
            return name;
        }
    }
    return NULL;
}
 
void printPhoneBook(PhoneBook* book) {
    for(int i = 0; i < book->total; ++i) {
        printf("%s :\t%s.\n", book->entries[i].name, book->entries[i].number);
    }
}
 
int main() {
    PhoneBook* pb = createPhoneBook();
 
    for(int i = 0; i < 200; ++i) {
        char number[80];
        char name[80];
        sprintf(number, "094784837%d", i);
        sprintf(name, "Joe%d", i);
        addPhoneNumber(number, name, pb);
    }
 
    printPhoneBook(pb);
 
    printf("Joe1's number: %s \n", getPhoneNumber("Joe1", pb));
    printf("Joe3's number: %s \n", getPhoneNumber("Joe3", pb));
    printf("Joe188's number: %s \n", getPhoneNumber("Joe188", pb));
 
}

