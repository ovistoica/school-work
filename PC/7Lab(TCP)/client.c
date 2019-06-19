/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * client.c
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define BUFLEN 1500

int main(int argc, char *argv[])
{
    int sockfd = 0;
    char buf[BUFLEN];
    struct sockaddr_in serv_addr;
    int rc;
    int first_client = 3;

    if(argc != 3)
    {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // deschidere socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("socket");
        exit(-1);
    }


    // completare informatii despre adresa serverului
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((unsigned short)atoi(argv[1]));
    rc = inet_aton("127.0.0.1", &serv_addr.sin_addr);
    if(rc < 0) {
        perror("socket");
        exit(-1);
    }

    // conectare la server
    rc = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(rc < 0) {
        perror("connect");
        exit(-1);
    }

    // Check number of client
    rc = recv(sockfd, buf, BUFLEN, 0);
    if(rc < 0) {
        perror("recv");
        exit(-1);
    }

    if(buf[0] == '1') {
        first_client = 1;
    } else {
        first_client = 0;
    }
    // citire de la tastatura, trimitere de cereri catre server, asteptare raspuns
    if(first_client) {
        printf("I am the first client\n");
        while(1) {
            fgets(buf, BUFLEN, stdin);
            rc = send(sockfd, buf, strlen(buf), 0);
            if(rc < 0) {
                perror("send");
                exit(-1);
            }

            rc = recv(sockfd, buf, BUFLEN, 0);
            if(rc == 0) {
                printf("S-a inchis conexiunea\n");
                break;
            } else if(rc < 0) {
                perror("send");
                exit(-1);
            }
            printf("%s\n", buf);
        }
    } else {
        printf("I am not the first client\n");
        while(1) {
            rc = recv(sockfd, buf, BUFLEN, 0);
            if(rc == 0) {
                printf("S-a inchis conexiunea\n");
                break;
            } else if(rc < 0) {
                perror("send");
                exit(-1);
            }
            printf("%s\n", buf);

            fgets(buf, BUFLEN, stdin);
            rc = send(sockfd, buf, strlen(buf), 0);
            if(rc < 0) {
                perror("send");
                exit(-1);
            }
            memset(buf, 0, BUFLEN);
        }
    }

    // inchidere socket
    close(sockfd);

    return 0;
}
