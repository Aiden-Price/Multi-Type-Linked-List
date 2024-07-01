// Student Number: 530502821
// COMP2017 Assignment 2

#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char** argv) {
    
    /* Main function of the linked list program
        Sections;
            Setup + Command Reading (Through loop)
            Command Parsing
            Memory Management
            Error Handling */

    // Variable Declarations
    char str[129];
    char *token;
    char *argument;
    char *extraArgCheck;
    char *nextChar = str;

    while (fgets(str, sizeof(str), stdin) != NULL) { // Command Reading loop
        
        // Handling EOF 
        if (feof(stdin)) {  
            for (int i = 0; i < number_of_lists; i++) {
                freeMemoryAllocation(&heads_lists[i]);
            }
            exit(0);  
        }

        // Line parsing preparation (*)
        // (*) Removing new line
        str[strcspn(str, "\n")] = '\0';

        // (*) Checking for any leading whitespace
        if (isspace((unsigned char)str[0])) {
            printf("INVALID COMMAND: INPUT\n");
            continue;
        }

        // Command (token) <argument> <extraArgCheck>
        token = strtok(str, " "); 
        argument = strtok(NULL, " "); 
        extraArgCheck = strtok(NULL, "");

        // No command provided
        if (token == NULL) {
            printf("INVALID COMMAND: INPUT\n");
            continue;
        }

        nextChar = token + strlen(token) + 1;

        // Checking for space after command
        if (*nextChar == ' ') { 
            printf("INVALID COMMAND: INSERT\n");
            continue;
        }

        // If a command is present
        if (token != NULL) {

            /* Cases
                NEW -> creating new linked list
                VIEW -> view a list by a given index
                    VIEW-ALL -> view all lists created
                REMOVE -> remove a existing list
                INSERT -> place an element at a certain index in list
                DELETE -> delete an element at a certain index in list
                VIEW-NESTED -> view all nested loops */

            // String Compare -> 0 when token matches with the command
            
            // Case 1 NEW
            if (strcmp(token, "NEW") == 0) {
                
                // NEW <null>
                if (argument == NULL) { 
                printf("INVALID COMMAND: NEW\n");
                continue;
                }

                char* endptr;
                long val = strtol(argument, &endptr, 10); // Convert argument to int

                // Check if conversion successful
                if (*endptr != '\0' || val <= 0 || (extraArgCheck != NULL && !isdigit(extraArgCheck[0]))) {
                    printf("INVALID COMMAND: NEW\n");
                    continue;
                }

                if (extraArgCheck != NULL && isdigit(extraArgCheck[0])) {
                    printf("INVALID COMMAND: INPUT\n");
                    continue;
                }

                // Max list count
                if (number_of_lists >= 100) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Initalise list elements
                int num_elements = atoi(argument);
                struct Node* tail = NULL;
                struct Node* head = NULL;

                // Read stdin, allocate memory for nodes
                for (int i = 0; i < num_elements; i++) {
                    if (!fgets(str, sizeof(str), stdin)) {
                        if (feof(stdin)) {
                            freeMemoryAllocation(&head); 
                            for (int j = 0; j < number_of_lists; j++) { 
                                freeMemoryAllocation(&heads_lists[j]);
                            }
                            exit(0);
                        } else {
                            printf("INVALID COMMAND NEW: %s\n", token);
                        }
                    }

                    str[strcspn(str, "\n")] = '\0'; 

                    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                    if (newNode == NULL) {
                        printf("Memory Allocation Unsuccessful\n");
                        freeMemoryAllocation(&head);
                        for (int j = 0; j < number_of_lists; j++) {
                            freeMemoryAllocation(&heads_lists[j]);
                        }
                        exit(1);
                    }

                    // Store data in the nodes
                    newNode->data = (char *)malloc(strlen(str) + 1);
                    if (newNode->data == NULL) {
                        printf("Memory Allocation Unsuccessful\n");
                        free(newNode); 
                        freeMemoryAllocation(&head);
                        for (int j = 0; j < number_of_lists; j++) {
                            freeMemoryAllocation(&heads_lists[j]);
                        }
                        exit(1); 
                    }
                    strcpy(newNode->data, str);
                    newNode->next = NULL;

                    // Allocate head and tail of node
                    if (head == NULL) {
                        head = newNode;
                        tail = newNode;
                    } else {
                        tail->next = newNode;
                        tail = tail->next;
                    }
                }

                heads_lists[number_of_lists] = head;
                number_of_lists++; // Increase total number of lists

                // Display properties
                printf("List %d: ", number_of_lists - 1);
                displayLinkedList(head); 

            // Case 2 VIEW
            } else if (strcmp(token, "VIEW") == 0) {
                
                // VIEW <null>
                if (argument == NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                
                // If user types VIEW-AlL
                } else if (strcmp(argument, "ALL") == 0) {
                    int counter = 0;
                    for (int i = 0; i < number_of_lists; i++) {
                        if (heads_lists[i] != NULL) {
                            counter++;
                        } 
                    }
                    // Print total number of exisiting lists then interate over all their indexes
                    printf("Number of lists: %d\n", counter);
                    for (int i = 0; i < number_of_lists; i++) {
                        if (heads_lists[i] != NULL) {
                            printf("List %d\n", i);
                        } 
                    }
                } else {

                    // Validate argument is a digit and within the bounds 
                    if (!isdigit(*argument) || atoi(argument) < 0 || atoi(argument) >= number_of_lists) {
                       printf("INVALID COMMAND: %s\n", token);
                        continue;
                    }
                    // Convert the value into an index
                    int indicator = atoi(argument);
                    if (heads_lists[indicator] != NULL) { // Validate list existance
                        displayLinkedList(heads_lists[indicator]);
                    } else {
                        printf("INVALID COMMAND: %s\n", token);
                    }
                }
            
            // Case 3 TYPE
            } else if (strcmp(token, "TYPE") == 0) {
                
                // TYPE <null>
                if (argument == NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }
                // View the index of the list provided but check if it exists first
                int indicator = atoi(argument);
                if (indicator >= 0 && indicator < number_of_lists && heads_lists[indicator] != NULL) {
                    viewType(heads_lists[indicator]);
                    printf("\n");
                } else {
                    printf("INVALID COMMAND: %s\n", token);
                }

            // Case 4 REMOVE
            } else if (strcmp(token, "REMOVE") == 0) {
                
                // REMOVE <null>
                if (argument == NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }
                // Convert argument to an integer 
                char* endptr;
                long indicator = strtol(argument, &endptr, 10);

                // Ensure no non numeric characters
                if (*endptr != '\0') {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Ensure the list exists
                if (indicator < 0 || indicator >= number_of_lists) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Removing the specified list
                if (indicator >= 0 && indicator < number_of_lists) {
                    if (heads_lists[indicator] != NULL) { 
                        removeList(indicator);
                        printf("\n");

                        // Counting amount of lists left
                        int counter = 0;
                        for (int i = 0; i < number_of_lists; i++) {
                            if (heads_lists[i] != NULL) {
                                counter++;
                            }
                        }

                        printf("Number of lists: %d\n", counter);

                        // Printing all lists that exist with associated index
                        for (int i = 0; i < number_of_lists; i++) {
                            if (heads_lists[i] != NULL) {
                                printf("List %d\n", i);
                            }
                        }
                    } else {
                       printf("INVALID COMMAND: %s\n", token);
                    }
                } else {
                    printf("INVALID COMMAND: %s\n", token);
                }
            
            // Case 5 INSERT
            } else if (strcmp(token, "INSERT") == 0) {
                
                // INSERT <null> <null>
                if (argument == NULL || extraArgCheck == NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Convert argument to int
                char* endptr;
                long listId = strtol(argument, &endptr, 10);
                
                // Validate list exists and no non numeric characters after arguments
                if (*endptr != '\0' || listId < 0 || listId >= number_of_lists) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Taking the index value
                char *indexStr = extraArgCheck;
                // Find the space character between the argument and val
                while (*indexStr != ' ' && *indexStr != '\0') indexStr++; 
                    if (*indexStr == ' ') indexStr++; 

                char *value = indexStr;
                indexStr = extraArgCheck;
                long index = strtol(indexStr, &endptr, 10);

                // Successful Parsing
                // Error for testcase part 2 with negative indexing (index >= 0)
                    // Couldnt do the negative indexing without memory leak
                if (*endptr == ' ' && index >= 0) { 
                    insertList(listId, index, value);
                } else {
                    printf("INVALID COMMAND: %s\n", token);
                }

            // Case 6 DELETE
            } else if (strcmp(token, "DELETE") == 0) {
                char *listIdStr = argument;

                // DELETE <null> <null>
                if (argument == NULL || extraArgCheck == NULL) {
                    printf("INVALID COMMAND: DELETE\n");
                    continue;
                }

                // Extract index as string
                char *indexStr = strtok(extraArgCheck, " "); 
                if (indexStr == NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Check for unexpected arguements
                char *extraCheck = strtok(NULL, "");
                if (extraCheck != NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                char *endptr;
                int listId = strtol(listIdStr, &endptr, 10);
                // Validate existance of list and no non numeric input
                if (*endptr != '\0' || listId < 0 || listId >= number_of_lists) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                // Parse and Validate index
                int index = strtol(indexStr, &endptr, 10);
                if (*endptr != '\0') {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }

                deleteList(listId, index); 

            // Case 7 VIEW-NESTED
            } else if (strcmp(token, "VIEW-NESTED") == 0) {
                
                // VIEW-NESTED <null>
                if (!argument) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }
                // Convert argument to an integer
                int listId = atoi(argument);
                // Validating existance of list
                if (listId < 0 || listId >= number_of_lists || heads_lists[listId] == NULL) {
                    printf("INVALID COMMAND: %s\n", token);
                    continue;
                }
                nested(heads_lists[listId], 0);
                printf("\n"); 
            } else {
                printf("%s", "INVALID COMMAND: INPUT\n");
                }
        } else {
            printf("%s", "INVALID COMMAND: INPUT\n");
        }
    } 

    // Free Memory Allocation
    for (int i = 0; i < number_of_lists; i++) {
        freeMemoryAllocation(&heads_lists[i]);
    }

    return 0;
}
