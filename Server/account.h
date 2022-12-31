#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <stdbool.h>

typedef struct Account {
    char username[20];
    char password[20];
    int status;
} Account;

typedef struct node
{
    Account infor;
    int SignIn;
    struct node* next;
} node;

void printList();
void insertFirst(Account account);
struct node* deleteFirst();
bool isEmpty();
void wrileFile();
void readFile();
node* checkUsername(char* username);

#endif