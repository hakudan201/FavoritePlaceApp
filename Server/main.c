#include <stdio.h>          /* These are the usual header files */
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

//#include "account.h"

#define PORT 5500   /* Port that will be opened */
#define BACKLOG 2   /* Number of allowed connections */
#define BUFF_SIZE 1024

#define REQUEST1 "LOGIN"
#define REQUEST2 "CLOSE"

#define MESSAGE1 "LOGIN SUCCESSFUL\n"
#define MESSAGE2 "LOGIN FAIL\n"

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

struct node* head = NULL;
struct node* current = NULL;

void printList() {
    struct node* ptr = head;
    printf("\n[ ");
    int i = 0;
    while (ptr != NULL) {
        printf("(%d %s,%s,%d) \n", i, ptr->infor.username, ptr->infor.password, ptr->infor.status);
        ptr = ptr->next;
        i++;
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



int main()
{
    readFile();
    Account account;
    int listen_sock, conn_sock; /* file descriptors */
    char recv_data[BUFF_SIZE];
    char request[BUFF_SIZE];
    int bytes_sent, bytes_received;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    int sin_size;

    //Step 1: Construct a TCP socket to listen connection request
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  /* calls socket() */
        perror("\nError: ");
        return 0;
    }

    //Step 2: Bind address to socket
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
    server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */
    if (bind(listen_sock, (struct sockaddr*)&server, sizeof(server)) == -1) { /* calls bind() */
        perror("\nError: ");
        return 0;
    }

    //Step 3: Listen request from client
    if (listen(listen_sock, BACKLOG) == -1) {  /* calls listen() */
        perror("\nError: ");
        return 0;
    }

    //Step 4: Communicate with client
    while (1) {
        //accept request
        sin_size = sizeof(struct sockaddr_in);
        if ((conn_sock = accept(listen_sock, (struct sockaddr*)&client, &sin_size)) == -1)
            perror("\nError: ");

        printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */

        //start conversation
        while (1) {
            //receives message from client
            bytes_received = recv(conn_sock, recv_data, BUFF_SIZE - 1, 0); //blocking
            if (bytes_received <= 0) {
                printf("\nConnection closed");
                break;
            }
            else {
                recv_data[bytes_received] = '\0';
                printf("\nReceive: %s Length: %d", recv_data, bytes_received);
                sscanf(recv_data, "%s %s %s", request, account.username, account.password);
                printf("\n %s %s %s", request, account.username, account.password);

                if (strncmp(request, REQUEST1, strlen(REQUEST1)) == 0)
                {
                    printf("\nRequest1: %s Length: %ld", REQUEST1, strlen(REQUEST1));
                    struct node* temp = checkUsername(account.username);
                    if ((temp != NULL) && (strncmp(temp->infor.password, account.password, strlen(temp->infor.password)) == 0)) {
                        //echo to client
                        bytes_sent = send(conn_sock, MESSAGE1, strlen(MESSAGE1), 0); /* send to the client welcome message */
                        if (bytes_sent <= 0) {
                            printf("\nConnection closed");
                            break;
                        }
                        printf("\nSend1: %s Length: %d", MESSAGE1, bytes_sent);
                    }
                    else {
                        //echo to client
                        bytes_sent = send(conn_sock, MESSAGE2, strlen(MESSAGE2), 0); /* send to the client welcome message */
                        if (bytes_sent <= 0) {
                            printf("\nConnection closed");
                            break;
                        }
                        printf("\nSend2: %s Length: %d", MESSAGE1, bytes_sent);

                    }
                }
                else {
                    //echo to client
                    bytes_sent = send(conn_sock, recv_data, bytes_received, 0); /* send to the client welcome message */
                    if (bytes_sent <= 0) {
                        printf("\nConnection closed");
                        break;
                    }
                    printf("\nSend3: %s Length: %d", recv_data, bytes_sent);
                }

            }


        }//end conversation
        close(conn_sock);
    }

    close(listen_sock);
    return 0;
}
