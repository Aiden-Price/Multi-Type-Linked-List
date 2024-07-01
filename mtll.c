#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Global Variables Definition 
int number_of_lists = 0;
struct Node *heads_lists[100];

struct Node* newNode(char* data, struct Node* listReference) {

    /* Parameters: pointer to string, pointer to another node (instead of holding data)
    Functionality: 1. Allocate Memory
                    2. Data or the list initialisation
                        2a. If the list reference is null node can hold direct data
                        2b. else hold reference to another list
                    3. Next pointer moved
    Purpose: Constructor for complex lists, can the node hold direct data or needs to reference
                another list?
    Return: struct Node* */

    struct Node* addedNode = (struct Node*)malloc(sizeof(struct Node));

    if (addedNode == NULL) {
        printf("Memory Allocation UNsuccessful");
        exit(EXIT_FAILURE);
    }

    if (listReference == NULL) {
        addedNode->data = strdup(data);
        addedNode->reference = 0;
        addedNode->listReference = NULL;
    } else {
        addedNode->data = NULL;
        addedNode->reference = 1;
        addedNode->listReference = listReference;
    }

    addedNode->next = NULL;
    return addedNode;
}

int findListIndex(struct Node* listReference) {

    /*  Parameters:    Pointer to head node
        Functionality: Iterate Array comapring each stored head node
                       If match is found return index else -1
        Purpose: Manage multiple linked lists based on head node 
                 reference 
        Return: int */

    for (int i = 0; i < number_of_lists; i++) {
        if (heads_lists[i] == listReference) {
            return i; 
        }
    }
    return -1; 
}

void nested(struct Node* node, int isNestedCall) {

    /* Parameters: Pointer to current node, flag for base case (inital call)
    Functionality: 1. Iterate over the list
                    2. Reference to nested lists
                    3. Special case: if a direct data node
                    4. Formatting nodes
    Purpose: Represent complex linked lists (hold direct values or references)
    Return: void */

    while (node) {
        if (node->reference) {
            int listIndex = findListIndex(node->listReference);
            if (!isNestedCall) {
                printf("Nested %d: ", listIndex);
            }
            printf("{List %d} -> ", listIndex);
            nested(node->listReference, 1); 
        } else {
            printf("%s", node->data); 
        }

        node = node->next;
        if (node && !node->reference) {
            printf(" -> ");
        }
    }
}

void newList(struct Node** headReference, char *update_data){

    /* Parameters: Double pointer to head of list, data for new node
    Functionality:  1. Allocate memory for node & data
                    2. If empty list create new head node
                    3. If not empyty traverse list to find the last node 
                        and append
                    4. Move pointer
    Purpose: Appending elements to the linked list or building one
    Return: void */

    struct Node* addedNode = (struct Node*)malloc(sizeof(struct Node));
    
    // 1.
    if (addedNode == NULL) {
        printf("%s", "Memory Allocation Unsuccessful\n");
        return;
    }

    addedNode->data = (char *)malloc(strlen(update_data) + 1);
    if (addedNode->data == NULL) {
        printf("%s", "Memory Allocation Unsuccessful\n");
        free(addedNode);
        return;
    }

    addedNode->next = NULL;
    
    //2.
    if (*headReference == NULL) {
        *headReference = addedNode;
        return;
    }

    //3.
    struct Node* lastNode = *headReference;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    //4.
    lastNode->next = addedNode;
}

int isFloat(const char* str) {

    /* Parameters: Pointer to start of null-terminated string
    Functionality: 1. strtod to convert str -> double
                    2. Checking for "\0"
                    3. Checking for digits
                    4. Scientific Notation
                    5. Decimal Points & Signs
    Purpose: Check if the string is actually a float and convert it to a floating point 
                    representation with 2dp
    Return: 1 -> true, 0 -> false*/
   
    char* endptr;
    strtod(str, &endptr); // 1.

    if (*endptr != '\0') return 0;  // 2.
        int hasDigit = 0, hasE = 0;
        const char *p = str, *lastE = NULL;
        while (*p) {
            if (isdigit((unsigned char)*p)) { // 3.
                hasDigit = 1; 
            } else if ((*p == 'e' || *p == 'E') && hasDigit) { // 4.
                if (hasE) return 0; 
                hasE = 1;
                hasDigit = 0; 
                lastE = p;
            } else if (*p == '.' && !hasE) { // 5.
            } else if ((*p == '+' || *p == '-') && (p == str || p - 1 == lastE)) {
            } else {
                return 0;
            }
            p++;
    }
    return hasDigit; 
}


int isInteger(const char* str) {

    /* Validate input of checking if a string 
        can be converted to int
        Return: 1 -> True, 0 -> False */
        
    char* endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0' && *str != '\0';
}

char* trim(char* str) {

    /* Parameters: Pointer to start of null terminated string
    Functionality: 1. Remove leading white space
                    2. Check if string is empty
                    3. Remove the trailing whitespace
    Purpose: Removing space characters for parsing input
    Return: char* */

    char* end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0) { 
        return str;
    }

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';

    return str;
}

void viewType(struct Node* node) {

    /* Parameters: Pointer to first node of linked list
    Functionality: 1. Interate over each node
                    2. Check in scaffold order 
                        2a. Integer Check
                        2b. Float Check 
                        2c. Char Check
                        2d. Else String 
                    3. If there exists a next node print an arrow (loop)
                    4. Move pointer to next node 
    Purpose: Categorise and display each type of element in linked list 
    Return: void */
    
    // 1.
    while (node != NULL) { 
        char* data = node->data;
        int length = strlen(data);

        if (isInteger(data)) { // 2a.
            printf("int");
        } else if (isFloat(data)) { // 2b.
            printf("float");
        } else if (length == 1 && isprint((unsigned char)data[0])) { // 2c.
            printf("char");
        } else {
            printf("string"); // 2d.
        }

        // 3.
        if (node->next != NULL) {
            printf(" -> ");
        }
        // 4.
        node = node->next;
    }
}

void displayLinkedList(struct Node* node) {

    /* Parameters: Pointer to first node of linked list
    Functionality: 1. If empty list exit
                    2. Uses flag to prevent printing arrow initially
                    3. Iterates over list 
                        3a. Checking special 0 case
                        3b. Checking if the string is interpreted as integer
                        3c. Convert float to 2dp + scientific notation
                        3d. String
                    4. Move pointer to next node
    Purpose: Format and disoplay elements in list after adding them
    Return: void */

    // 1.
    if (node == NULL) {
        return;
    }
    int first = 1;  // 2.

    while (node != NULL) { // 3.
        
        if (first) {
            first = 0; 
        } else {
            printf(" -> "); 
        }
        
        if (strcmp(node->data, "-0") == 0) {  // 3a.
            printf("0");
        } else if (isInteger(node->data)) {  // 3b.
            printf("%s", node->data);
        } else if (isFloat(node->data)) { // 3c.
            printf("%.2f", atof(node->data));
        } else { 
            printf("%s", node->data); // 3d.
        }
        node = node->next; // 4.
    }
    printf("\n");
}

void freeMemoryAllocation(struct Node** headReference){

    /* Parameters: Pointer to first node in linked list
    Functionality: 1. Iterate each node
                    1a. Free memory for node data & node itself -> move to next node
                2. Reset list head
    Purpose: Management of dynamically allocated memory (prevent memory leaks)
    Return: void */

    struct Node* current = *headReference;
    struct Node* next;

    while (current != NULL) { // 1.
        next = current->next;
        free(current->data); 
        free(current);
        current = next;
    }
    *headReference = NULL; // 2.
}

void removeList(int indicator){

    /* Parameters: Specify which list to remove (target within the many lists)
    Functionality: 1. Ensure range of indicator is valid
                    2. If list exists and not empty; free it
                    3. Iterate over list (through each node) and free the memory of the node
                        and node data
                    4. Reset the reference
    Purpose: Removing lists and freeing the memory 
    Return: void */
    
    // 1.
    if (indicator >= 0 && indicator < number_of_lists) {
        
        // 2.
        if (heads_lists[indicator] != NULL) {
        struct Node* current = heads_lists[indicator];
        
        // 3.
        while (current != NULL) {
            struct Node* next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        
        // 4.
        heads_lists[indicator] = NULL;
        printf("List %d has been removed.\n", indicator);
        } else {
            printf("INVALID COMMAND: REMOVE\n");
        }
    } else {
        printf("INVALID COMMAND: REMOVE\n");
    }
}

char* duplicate(const char* val) {

    /* Parameters: Pointer to original string
    Functionality: 1. Calculate length 
                    2. Allocate memory
                    3. Error handling
                    4. Return new string
    Purpose: String manipulation by creating a duplicate instance for safe modifications
                to reuse original list
    Return: char* */

    size_t length = strlen(val) + 1;
    char* newStr = (char*)malloc(length);

    if (newStr == NULL) {
        perror("Allocation of Memory failed");
        exit(EXIT_FAILURE);
    }
    memcpy(newStr, val, length);
    return newStr;
}

void insertList(int listId, int index, char* value) {

    /* Parameters: Indentifier for new node, posiiton in list, value for the new node
    Functionality: 1. Validate the list reference
                    2. Allocate memory for new node + create a copy
                    3. Special case: if new node is head of list
                    4. Special case: negative position, iterate from back of list
                    5. Validate the position within the list
                    6. Insert the node with data
                    7. Display the new list
    Purpose: Move elements within given lists and positions and update the lists
    Return: void */

    // 1.
    if (listId < 0 || listId >= number_of_lists) {
        printf("INVALID COMMAND: INSERT\n");
        return;
    }

    // 2.
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->data = duplicate(value); 
    newNode->next = NULL;

    // 3.
    if (index == 0) {
        newNode->next = heads_lists[listId];
        heads_lists[listId] = newNode;
        printf("List %d: ", listId);
        displayLinkedList(heads_lists[listId]);
        return;
    }

    struct Node* current = heads_lists[listId];
    int len = 0;
    while (current != NULL) {
        len++;
        current = current->next;
    }

    // 4.
    if (index < 0) {
        index = len + index + 1; 
    }

    // 5.
    if (index < 0 || index > len) { 
        printf("INVALID COMMAND: INSERT\n");
        free(newNode->data);
        free(newNode);
        return;
    }

    // 6.
    current = heads_lists[listId];
    for (int i = 0; i < index - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    // 7.
    printf("List %d: ", listId);
    displayLinkedList(heads_lists[listId]);
}


void deleteList(int listId, int index) {

    /* Parameters: Indentifier for new node, posiiton in list
    Functionality: 1. Validate the list reference
                    2. Special case: negative position, iterate from back of list 
                    3. Delete Node
                        3a. If index is 0 (head) set head to second node
                        3b. Traverse list to find node if not head and adjust the next 
                            pointers of the node before
                        3c. Free memory of deleted node
                    4. Check if index is within range of list
    Purpose: Delete a given element within a provided linked list
    Return: void */

    // 1.
    if (listId < 0 || listId >= number_of_lists || heads_lists[listId] == NULL) {
        printf("INVALID COMMAND: DELETE\n");
        return;
    }

    // 2.
    if (index == -1) {
        struct Node* current = heads_lists[listId];
        int count = 0;
        while (current != NULL) {
            current = current->next;
            count++;
        }
        index = count - 1; 
    }

    struct Node* temp = heads_lists[listId];
    struct Node* toDelete = NULL;

    // 3a.
    if (index == 0) {
        heads_lists[listId] = temp->next; 
        free(temp->data);
        free(temp); 
    } else {
        
        // 3b.
        for (int i = 0; temp != NULL && i < index - 1; i++) {
            temp = temp->next;
        }
        
        // 4.
        if (temp == NULL || temp->next == NULL) {
            printf("INVALID COMMAND: DELETE\n");
            return;
        }

        toDelete = temp->next;
        temp->next = temp->next->next; 

        // 3c.
        free(toDelete->data); 
        free(toDelete);
    }

    printf("List %d: ", listId);
    displayLinkedList(heads_lists[listId]); 
}