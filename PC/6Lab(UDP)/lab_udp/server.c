/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	if (argc!=3)
		usage(argv[0]);
	
	struct sockaddr_in serveraddr,  clientaddr;
	char buf[250];


	/*Deschidere socket*/
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("Opening socket\n");
		exit(-1);
	}
	
	
	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons((unsigned short)atoi(argv[1]));
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	
	/* Legare proprietati de socket */
	if(bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
		perror("bind");
		exit(-1);
	}


	
	
	/* Deschidere fisier pentru scriere */
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/


	int enable = -1;
	int rc = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	if(rc < 0) {
		perror("setsockopt");
	}
	
	socklen_t clen;
	rc = recvfrom(sockfd, buf, 250, 0, (struct sockaddr *)&clientaddr, &clen);
	if(rc < 0) {
		perror("recv\n");
		exit(-1);
	}

	printf("%s\n", buf);

	char bufff[250] = "Salut si tie";
	rc = sendto(sockfd, bufff, 20, 0, (struct sockaddr *)&clientaddr, clen);
	if( rc < 0) {
		perror("sending back");
		exit(-1);
	}

	/*Inchidere socket*/	
	close(sockfd);

	
	/*Inchidere fisier*/

	return 0;
}
