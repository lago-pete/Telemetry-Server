#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"


void startServer(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("Error Retrieving File Descriptor");
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("\n\nGot a socket fd: %d\n\n", sock);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3434);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    int binder = bind(sock, (struct sockaddr *) &addr, sizeof(addr));

    if(binder == -1){
        perror("Binder Error");
        exit(EXIT_FAILURE);
    }
    printf("Binder Successful\n\n");

    int list = listen(sock, 5);

    if(list == -1){
        perror("Listening Error");
        exit(EXIT_FAILURE);
    }

    printf("Now Listening on Port: %d \n\n", ntohs(addr.sin_port));



    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);

    if(client_fd == -1){
        perror("Accept Error");
        exit(EXIT_FAILURE);
    }

    printf("New Client Accepted: %d fd\n\n", client_fd);


}

