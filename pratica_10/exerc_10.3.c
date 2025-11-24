#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "address.h"
//#include "user.h"

struct address {
    char *line;
    int number;
    int zipcode;
};

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

struct user {
    char *name;
    int idade;
    struct address *addr;
};

struct user *create_user(const char *input) {
    struct user *user = (struct user*)malloc(sizeof(struct user));
    char temp[strlen(input) + 1];
    int position = 0, j = 0;

    for(int i = 0; i <= strlen(input); i++) {
        if(input[i] == '#' || input[i] == '\0') {
            temp[j] = '\0';

            if(position == 0) {
                user->name = (char*)malloc(strlen(temp) + 1);
                strcpy(user->name, temp);
            }
            else if(position == 1) {
                user->idade = atoi(temp);
            }
            else if(position == 2) {
                user->addr = create_address(temp);
            }

            j = 0;
            position++;
        } else {
            temp[j] = input[i];
            j++;
        }
    }
    return user;
}

void free_user(struct user *user) {
    free_address(user->addr);
    free(user->name);
    free(user);
}