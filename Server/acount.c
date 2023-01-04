#include <stdio.h>          /* These are the usual header files */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "account.h"

void printList() {
    struct node* ptr = head;
    printf("\n[ ");

    while (ptr != NULL) {
        printf("(%s,%s,%d) \n", ptr->infor.username, ptr->infor.password, ptr->infor.status);
        ptr = ptr->next;
    }

    printf(" ]");
}

void insertFirst(Account account) {
    struct node* link = (struct node*)malloc(sizeof(struct node));

    strcpy(link->infor.username, account.username);
    strcpy(link->infor.password, account.password);
    link->infor.status = account.status;
    link->SignIn = 0;

    link->next = head;
    head = link;
}

struct node* deleteFirst() {
    struct node* tempLink = head;
    head = head->next;
    return tempLink;
}

bool isEmpty() {
    return head == NULL;
}

void wrileFile() {
    FILE* outfile;
    outfile = fopen("account.txt", "w");
    struct node* temp = head;
    while (temp != NULL)
    {
        fprintf(outfile, "%s %s %d\n", temp->infor.username, temp->infor.password, temp->infor.status);
        temp = temp->next;
    }
    fclose(outfile);
}

void readFile() {
    FILE* file;
    file = fopen("account.txt", "r");
    Account temp;
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit(1);
    }
    while (fscanf(file, "%s %s %d", temp.username, temp.password, &temp.status) != EOF)
    {
        insertFirst(temp);
    }
    fclose(file);
}

node* checkUsername(char* username) {
    node* temp = head;
    while (temp != NULL)
    {
        if (strncmp(temp->infor.username, username, strlen(temp->infor.username)) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}