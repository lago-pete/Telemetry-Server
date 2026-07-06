#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

void startServer(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Error Retrieving File Descriptor");
        printf("Error");
        exit(EXIT_FAILURE);
    }
    printf("\n\nGot a socket fd: %d\n\n", sock);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3434);
    addr.sin_addr.s_addr = INADDR_ANY;

    int binder = bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    if (binder == -1)
    {
        perror("Binder Error");
        exit(EXIT_FAILURE);
    }
    printf("Binder Successful\n\n");

    int list = listen(sock, 5);

    if (list == -1)
    {
        perror("Listening Error");
        exit(EXIT_FAILURE);
    }

    printf("Now Listening on Port: %d \n\n", ntohs(addr.sin_port));

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd;

    while (1)
    {
        client_len = sizeof(client_addr);
        client_fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);

        if (client_fd == -1)
        {
            perror("Accept Error");
        }
        else
        {
            printf("New Client Accepted: %d fd\n\n", client_fd);

            char buffer[128];
            ssize_t bytes;
            int flag = 0;

            while ((bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) > 0)
            {
                buffer[bytes] = '\0';
                printf("Got: %s\n", buffer);
                const char *message = "This is first contact\n";

                ssize_t sent = send(client_fd, message, strlen(message), 0);

                if (sent == -1)
                {
                    perror("Sending Error");
                    close(client_fd);
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                if (bytes == 0)
                {
                    printf("Client Disconnected\n");

                    int clientClose = close(client_fd);
                    if (clientClose == -1)
                    {
                        perror("Client Closure Error");
                    }
                }
                else
                {
                    perror("Error in the recv data");
                }
            }
        }
    }
}
