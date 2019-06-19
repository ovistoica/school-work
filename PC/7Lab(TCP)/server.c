/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * server.c
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define BUFLEN 1500

int main(int argc, char *argv[])
{
    int listenfd = 0, client1fd = 0, client2fd = 0;
    char buf[BUFLEN];
    struct sockaddr_in serv_addr;
    int rc;

    if(argc != 3)
    {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // deschidere socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
      perror("Socket opening");
      exit(-1);
    }


    // completare informatii despre adresa serverului
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((unsigned short)atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // legare proprietati de socket
    int enable = 1;
    rc = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    if(rc < 0){
      perror("setsockopt");
      exit(-1);
    }

    rc = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(rc < 0){
      perror("bind");
      exit(-1);
    }


    // ascultare de conexiuni
    listen(listenfd, 5);

    // Notify first client to connect
    client1fd = accept(listenfd, NULL, NULL);
    if(client1fd < 0){
      perror("accept1");
      exit(-1);
    }
    buf[0] = 1;
    send(client1fd, buf, 1, 0);

    client2fd = accept(listenfd, NULL, NULL);
    if(client2fd < 0){
      perror("accept1");
      exit(-1);
    }
    buf[0] = 0;
    send(client1fd, buf, 1, 0);

    // acceptarea unei conexiuni, primirea datelor, trimiterea raspunsului

    while(1){
      memset(buf, 0, BUFLEN);

      // Send the message of client1 to client2
      rc = recv(client1fd, buf, sizeof(buf), 0);
      if(rc == 0){
        printf("S-a inchis conexiunea\n");
        break;
      }else if(rc < 0){
        perror("recv");
        exit(-1);
      }

      rc = send(client2fd, buf, rc, 0);
      if(rc == 0){
        printf("S-a inchis conexiunea\n");
        break;
      }else if(rc < 0){
        perror("send");
        exit(-1);
      }

      memset(buf, 0, BUFLEN);
      // Send the message of client2 to client1
      rc = recv(client2fd, buf, BUFLEN, 0);
      if(rc == 0){
        printf("S-a inchis conexiunea\n");
        break;
      }else if(rc < 0){
        perror("recv");
        exit(-1);
      }

      rc = send(client1fd, buf, rc, 0);
      if(rc == 0){
        printf("S-a inchis conexiunea\n");
        break;
      }else if(rc < 0){
        perror("send");
        exit(-1);
      }
    }

    // inchidere socket(i)
    close(listenfd);
    close(client1fd);
    close(client2fd);

    return 0;
}
