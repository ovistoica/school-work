#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFLEN 256

void error(char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  fd_set read_fds;
  fd_set temp_fd;
  int maxfd, i;

  char buffer[BUFLEN];
  if (argc < 3) {
    fprintf(stderr,"Usage %s server_address server_port\n", argv[0]);
    exit(0);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  error("ERROR opening socket");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[2]));
  inet_aton(argv[1], &serv_addr.sin_addr);
  FD_ZERO(&read_fds);
  FD_ZERO(&temp_fd);
  FD_SET(STDIN_FILENO, &read_fds);


  if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
  error("ERROR connecting");

  FD_SET(sockfd, &read_fds);
  maxfd = sockfd;

  while(1){
    temp_fd = read_fds;
    if(select(maxfd + 1, &temp_fd, NULL, NULL, NULL) == -1){
      error("ERROR in select");
    }
    for(i = 0; i <= maxfd; i++){
      if(FD_ISSET(i, &temp_fd)){
        if(i == STDIN_FILENO){
          // Citesc de la tastatura
          memset(buffer, 0 , BUFLEN);
          fgets(buffer, BUFLEN-1, stdin);
          if( !strcmp("exit", buffer) || !strcmp("exit\n", buffer)) {
            exit(0);
          }
          //trimit mesaj la server
          n = send(sockfd,buffer,strlen(buffer), 0);
          if (n < 0){
            error("ERROR writing to socket");
          }
        } else {
          printf("Acum citesc\n");
            if ((n = recv(i, buffer, sizeof(buffer), 0)) < 0) {
              error("ERROR in recv");
            }
            printf("%s\n", buffer);
        }
      }
    }
  }
  return 0;
}
