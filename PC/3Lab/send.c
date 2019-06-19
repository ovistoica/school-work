#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

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

//Send until the correct message is received
void send_correct(msg *m) {
	msg r;
	while(1) {
		send_message(m);
		if (recv_message(&r)<0){
			perror("receive error");
		}
		if(r.len == 4){
			return;
		}
	}
}

int main(int argc,char** argv){
	init(HOST,PORT);
	msg t;
	struct my_pkg p;

	//Send filename
	memset(&p, 0, sizeof(p));
	strcpy(p.my_payload, argv[1]);
	p.nr_bytes = strlen(argv[1]);
	p.parity = total_parity(p.my_payload, p.nr_bytes);
	memcpy(t.payload, &p, sizeof(p));
	t.len = sizeof(p);
	send_correct(&t);

	FILE *fp = fopen(argv[1], "rb");

	while(1) {
		memset(&p, 0, sizeof(p));
		p.nr_bytes = fread(p.my_payload, 1, sizeof(p.my_payload), fp);


		//send msg
		memcpy(t.payload, &p, sizeof(p));
		t.len = sizeof(p);
		send_correct(&t);
		
		//If file end
		if(p.nr_bytes == 0) {
			break;
		}
	}
	fclose(fp);
	return 0;
}
