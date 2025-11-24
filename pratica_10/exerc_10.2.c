#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "address.h"

struct address {
    char *line;
    int number;
    int zipcode;
};

struct address *create_address(const char *input) {
    int position = 0, j = 0;
    char temp[strlen(input) + 1];
    struct address *addr = (struct address*)malloc(sizeof(struct address));
    for(int i = 0; i < strlen(input); i++) {
        temp[j] = input[i];
        if(input[i] == '|' || input[i] == '\0') {
            temp[j] = '\0';
            position++;
        }

        j++;

        if(position == 1) {
            addr->line = (char*)malloc(strlen(temp) + 1);
            strcpy(addr->line, temp);
            j = 0;
        }
        if(position == 2) {
            addr->number = atoi(temp);
            j = 0;
        }
        if(position == 3) {
            addr->zipcode = atoi(temp);
            j = 0;
        }
        
    }
    return addr;
}

struct address *create_address(const char *input) {
    struct address *addr = (struct address*)malloc(sizeof(struct address));
    char temp[strlen(input) + 1]; 
    int j = 0;
    int position = 0;

    for(int i = 0; i <= strlen(input); i++) {

        if(input[i] == '|' || input[i] == '\0') {
            
            temp[j] = '\0';

            if(position == 0) {
                addr->line = (char*)malloc(strlen(temp) + 1);
                strcpy(addr->line, temp);
            }
            else if(position == 1) {
                addr->number = atoi(temp);
            }
            else if(position == 2) {
                addr->zipcode = atoi(temp);
            }

            j = 0; 
            position++; 

        } else {
            temp[j] = input[i];
            j++;
        }
    }
    return addr;
}

void free_address(struct address *addr) {
    free(addr->line);
    free(addr);
}