// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result, *p;

	// Set hints
	hints.ai_family = INADDR_ANY; // doar IPv4
	hints.ai_socktype = SOCK_STREAM; // doar TCP


	// Get addresses
	if(getaddrinfo("google.ro", NULL, &hints, &result) != 0) {
		perror("getaddrinfo");
	}

	// Iterate through addresses and print them

	for(p = result; p != NULL; p = p->ai_next){
		if(p->ai_family == AF_INET){
			char ip[INET_ADDRSTRLEN];
			struct sockaddr_in * addr = (struct sockaddr_in*) p->ai_addr;

			const char *x = inet_ntop(p->ai_family, &(addr->sin_addr), ip, sizeof(ip));

			if(x != NULL){
				printf("IP is %s\nPort is %d\n",ip, ntohs(addr->sin_port));
			}
		} else {
			char ip[INET6_ADDRSTRLEN];
			struct sockaddr_in6 * addr = (struct sockaddr_in6*) p->ai_addr;

			const char *x = inet_ntop(p->ai_family, &(addr->sin6_addr), ip, sizeof(ip));

			if(x != NULL){
				printf("IP is %s\nPort is %d\n",ip, ntohs(addr->sin6_port));
			}

		}
	}
	// Free allocated data
	freeaddrinfo(result);
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	// TODO: fill in address data
	inet_aton(ip, (struct in_addr *)&addr.sin_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);

	// TODO: get name and service
	if (getnameinfo((struct sockaddr *)&addr, sizeof(addr), host, sizeof(host),
      service, sizeof(service), 0) != 0){
				printf("getnameinfo\n");
				exit(-1);
			}

	// TODO: print name and service
	printf("Host is %s\nService is %s\n",host, service );
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
