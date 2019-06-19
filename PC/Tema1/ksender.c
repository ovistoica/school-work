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
void create_filePack(char *filename, kerm_pack *p) {
	strcpy(p->DATA, filename);
	p->LEN = strlen(p->DATA);
	inc_seq(p->SEQ);
	p->TYPE = File_Header;
	p->CHECK = get_CHECK(*p);
	p->MARK = DEFAULT_EOL;
}

//Create a package for sending Data
void create_dataPack(FILE *fp, kerm_pack *p) {
	size_t chunk = fread(p->DATA, 1, MAX_DATA, fp);
	p->LEN = chunk;
	inc_seq(p->SEQ);
	p->TYPE = Data;
	p->CHECK = get_CHECK(*p);
	p->MARK = DEFAULT_EOL;
}

//Send message until receive ACK
int send_until_correct(const msg *t) {
	msg *r;
	kerm_pack p;
	int timeout_times;
	while(1) {
		if(timeout_times == 3) {
			return -1;
		}
		send_message(t);
		r = receive_message_timeout(5000);
		if(r == NULL) {
			++timeout_times;
			continue;
		}else {
			memcpy(&p, r->payload, r->len);
			if(p.TYPE == ACK){
				return 0;
			} else if(p.TYPE == NAK) {
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
	pack.SEQ = 0x0;
	memset(pack.DATA, 0, MAX_DATA);
	memcpy(pack.DATA, &start_transm, sizeof(start_transm));
	pack.CHECK= get_CHECK(pack);
	pack.MARK = DEFAULT_EOL;

	//Sending send_init package
	memcpy(t.payload, &pack, sizeof(pack));
	t.len = sizeof(pack);
	send_until_correct(&t);

	//Starting to send files
	for(i = 1; i < argc; i++) {

		fp = fopen(argv[i], "rb");
		create_filePack(argv[i], &pack);
		wrap_pack(&t, &pack);
		send_until_correct(&t);

		while(1) {
			size_t chunk_size = fread(pack.DATA, 1, MAX_DATA, fp);

			//If file ended
			if(chunk_size == 0) {
				//Sending EOF
				pack.TYPE = EOFile;
				pack.CHECK = get_CHECK(pack);
				wrap_pack(&t, &pack);
				send_until_correct(&t);
				if(send_until_correct(&t) == -1) {
					perror("timeout error\n");
					return -1;
				}
				fclose(fp);
				break;
			}

			//Making Data pack
			pack.LEN = chunk_size;
			pack.SOH = DEFAULT_HEADER;
			inc_seq(pack.SEQ);
			pack.TYPE = Data;
			pack.CHECK = get_CHECK(pack);
			pack.MARK = DEFAULT_EOL;
			ZERO(t);

			//Sending data chunk
			t.len = sizeof(pack);
			memcpy(t.payload, &pack, t.len);
			if(send_until_correct(&t) == -1) {
				perror("timeout error\n");
				return -1;
			}

		}

	}

	//Terminating transmission
	pack.TYPE = EOT;
	pack.CHECK = get_CHECK(pack);
	wrap_pack(&t, &pack);
	if(send_until_correct(&t) == -1) {
		perror("timeout error\n");
		return -1;
	}

	return 0;
}
