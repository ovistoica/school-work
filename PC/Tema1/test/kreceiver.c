#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

void send_ACK(msg *m, kerm_pack pack) {
	if(pack.TYPE != Send_Init) {
		ZERO(pack.DATA);
	}
	ZERO(*m);
	pack.TYPE = ACK;
	m->len = sizeof(pack);
	
	//Sending ACK with same SEQ number as message received
	memcpy(m->payload, &pack,m->len );
	send_message(m);
}

void send_NAK(msg *m, kerm_pack pack) {
	if(pack.TYPE != Send_Init) {
		ZERO(pack.DATA);
	}
	ZERO(*m);
	pack.TYPE = NAK;
	m->len = sizeof(pack);
	
	//Sending NAK with same SEQ number as message received
	memcpy(m->payload, &pack,m->len );
	send_message(m);
}

int main(int argc, char** argv) {
	unsigned short crc, exit = 0;
	msg r, t;
	kerm_pack pack;
	FILE *fp;
	char filename[50];
	send_init transm_rules; //Stores the rules of communication
	unsigned char last_SEQ; //Last received sequence number

	init(HOST, PORT);


	while (1) {
		//Initiating communication
		if (recv_message(&r) < 0) {
			perror("Receive message");
			return -1;
		}
		memcpy(&pack, r.payload, r.len);
		memcpy(&transm_rules, pack.DATA, sizeof(transm_rules));

		crc = get_CHECK(pack);
		if(crc == pack.CHECK) {
			//Send ACK for type 'S'
			send_ACK(&t, pack);
			break;
		} else {
			//Send NAK for type 'S'
			send_NAK(&t, pack);
		}
	}
	last_SEQ = pack.SEQ;

	while(1) {

		if (recv_message(&r) < 0) {
			perror("Receive message");
			return -1;
		}

		memcpy(&pack, r.payload, r.len);

		//Message is correct
		crc = get_CHECK(pack);
		if(crc == pack.CHECK) {
			send_ACK(&t, pack);
		} else {
			send_NAK(&t, pack);
			continue;
		}

		//Check if sender didn't resend an already gotten message
		if(pack.SEQ == last_SEQ) {
			continue;
		} else {
			last_SEQ = pack.SEQ;
		}


		switch(pack.TYPE) {
			
			case File_Header :
				strcpy(filename, "recv_");
				strcat(filename, pack.DATA);
				fp = fopen(filename, "wb");
				break;

			case EOT:
				exit = 1;
				break;

			case EOFile:
				fclose(fp);
				break;

			case Data:
				if(fp == NULL) {
					break;
				} else {
					fwrite(pack.DATA, 1, (size_t)pack.LEN, fp);
				}
				break;
		}
		if(exit == 1) {
			break;
		}
	}
	return 0;
}
