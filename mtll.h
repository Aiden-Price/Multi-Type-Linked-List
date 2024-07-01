#ifndef MTLL_H
#define MTLL_H

#include <stddef.h>
#include <stdlib.h>

// Structs
struct Node {
    char *data;
    struct Node* next;
    int reference;
    struct Node* listReference;
};

// Global Variables Initialisation
extern int number_of_lists;
extern struct Node *heads_lists[100];

// Part 1
struct Node* newNode(char* data, struct Node* listReference);
void displayLinkedList(struct Node* node);
void viewType(struct Node* node);
void removeList(int indicator);
int isFloat(const char* str);
int isInteger(const char* str);
char* trim(char* str);
void newList(struct Node** headReference, char *update_data);
char* duplicate(const char* val);

// Part 2
void insertList(int listId, int index, char* value);
void deleteList(int listId, int index);

// Part 3
void nested(struct Node* node, int isNestedCall);
int findListIndex(struct Node* listReference);

// Memory Management 
void freeMemoryAllocation(struct Node** headReference);

#endif
