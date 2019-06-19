#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

//Parity of the message
int byte_parity(unsigned char x) {
	int rez = 0;
	for(int i = 0; i < 8; i++)
		if(x & (1 << i))
			rez ^= 1;
	return rez;
}

int total_parity(unsigned char *msg, size_t len) {
	int i, rez;
	for (i = 0; i < len;i++) {
		rez ^= byte_parity(msg[i]);
	}
	return rez;
}

void sendACK(msg *t) {
	printf("ACK\n");
	t->len = 4;
	send_message(t);
}

void sendNACK(msg *t) {
	printf("NACK\n");
	t->len = 17;
	send_message(t);
}

int main(int argc,char** argv){
	msg r,t;
	my_pkg p;
	int parity;
	FILE *fp;
	char filename[50];
	init(HOST,PORT);

	//Get filename;
	while(1) {
		if (recv_message(&r)<0){
			perror("Receive message");
			return -1;
		}
		memcpy(&p, r.payload, r.len);

		parity = total_parity((unsigned char*)p.my_payload, p.nr_bytes);
		if(parity == p.parity){
			sendACK(&t);
			break;
		}
		sendNACK(&t);
	}
	strncpy(filename, r.payload, p.nr_bytes);
	strcat(filename, ".rec");

	fp = fopen(filename, "wb");

	while(1) {
		while(1) {
			if (recv_message(&r)<0){
				perror("Receive message");
				return -1;
			}
			memcpy(&p, r.payload, r.len);

			parity = total_parity((unsigned char*)p.my_payload, p.nr_bytes);
			if(parity == p.parity){
				sendACK(&t);
				break;
			}
			sendNACK(&t);
		}
		if(p.nr_bytes == 0) {
			break;
		}
		fwrite(p.my_payload, 1, p.nr_bytes, fp);
	}
	fclose(fp);

	return 0;
}
