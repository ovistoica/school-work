/* AUTHOR: Stoica George Ovidiu
 * NOTE: Some of the functions used in sender and receiver
 * are defined in lib.h */
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

//Create a package for the File Header
void create_filePack(char *filename, kerm_pack *p, unsigned char current_SEQ) {
	strcpy(p->DATA, filename);
	p->LEN = strlen(p->DATA);
	p->SEQ = current_SEQ;
	p->TYPE = File_Header;
	p->CHECK = get_CHECK(*p);
	p->MARK = DEFAULT_EOL;
}

//Send message until receive ACK
int send_until_correct(const msg *t) {
	msg *r;
	kerm_pack p;
	int timeout;
	timeout = 0;
	while(1) {
		if(timeout >= 3) {
			return -1;
		}
		send_message(t);
		r = receive_message_timeout(5000);
		if(r == NULL) {
			++timeout;
			continue;
		}else {
			memcpy(&p, r->payload, r->len);
			if(p.TYPE == ACK){
				return 1;
			} else if(p.TYPE == NAK) {
				timeout = 0;
				continue;
			}
		}
	}
}


int main(int argc, char** argv) {
	int i;
	msg t;
	kerm_pack pack;
	send_init start_transm;
	unsigned char current_SEQ = 0x0;

	FILE *fp;
	init(HOST, PORT);



	//Setting initial params for communication
	memset(&start_transm, 0, sizeof(start_transm));
	start_transm.MAXL = MAX_DATA;
	start_transm.TIME = DEFAULT_TIMEOUT;
	start_transm.EOL = DEFAULT_EOL;
	
	//Creating send_init package;
	pack.SOH = DEFAULT_HEADER;
	pack.TYPE = Send_Init;
	pack.SEQ = current_SEQ;
	memset(pack.DATA, 0, MAX_DATA);
	memcpy(pack.DATA, &start_transm, sizeof(start_transm));
	pack.CHECK= get_CHECK(pack);
	pack.MARK = DEFAULT_EOL;

	//Sending send_init package
	memcpy(t.payload, &pack, sizeof(pack));
	t.len = sizeof(pack);
	if (send_until_correct(&t) == -1) {
		perror("Connection timeout error\n");
		return -1;
	}

	//Starting to send files
	for(i = 1; i < argc; i++) {

		fp = fopen(argv[i], "rb");
		printf("File %d\n", i);
		inc_seq(current_SEQ);
		create_filePack(argv[i], &pack, current_SEQ);
		wrap_pack(&t, &pack);
		if (send_until_correct(&t) == -1) {
			perror("Connection timeout error\n");
			return -1;
		}

		while(1) {
			size_t chunk_size = fread(pack.DATA, 1, MAX_DATA, fp);

			//If file ended
			if(chunk_size == 0) {
				//Sending EOF
				pack.TYPE = EOFile;
				inc_seq(current_SEQ);
				pack.SEQ = current_SEQ;
				pack.CHECK = get_CHECK(pack);
				wrap_pack(&t, &pack);
				if (send_until_correct(&t) == -1) {
					perror("Connection timeout error\n");
					return -1;
				}
				fclose(fp);
				break;
			}

			//Making Data pack
			pack.LEN = chunk_size;
			pack.SOH = DEFAULT_HEADER;
			inc_seq(current_SEQ);
			pack.SEQ = current_SEQ;
			pack.TYPE = Data;
			pack.CHECK = get_CHECK(pack);
			pack.MARK = DEFAULT_EOL;
			ZERO(t);

			//Sending data chunk
			t.len = sizeof(pack);
			memcpy(t.payload, &pack, t.len);
			if (send_until_correct(&t) == -1) {
				perror("Connection timeout error\n");
				return -1;
			}
		}

	}

	//Terminating transmission
	pack.TYPE = EOT;
	inc_seq(current_SEQ);
	pack.SEQ = current_SEQ;
	pack.CHECK = get_CHECK(pack);
	wrap_pack(&t, &pack);
	if (send_until_correct(&t) == -1) {
		perror("Connection timeout error\n");
		return -1;
	}

	return 0;
}
