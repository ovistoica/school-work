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

int main(int argc,char** argv){
	init(HOST,PORT);
	msg t;
	int i;

	//Send number of files
	t.payload[0] = argc - 1;
	t.len = 1;
	send_message(&t);
	recv_message(&t);

	for(i = 1; i < argc; i++) {


		//Send name of current file
		strcpy(t.payload, argv[i]);
		t.len = strlen(argv[i]) + 1;
		send_message(&t);
		recv_message(&t);

		FILE *fp = fopen(argv[i], "rb");

		while(1) {
			int chunk_size = fread(t.payload + 1, 1, sizeof(t.payload) - 1, fp);

			//If file end
			if(chunk_size == 0) {
				break;
			}

			t.len = chunk_size + 1;
			t.payload[0] = 0;
			send_message(&t);
			recv_message(&t);
		}

		t.len = 1;
		t.payload[0] = 1;
		send_message(&t);
		recv_message(&t);
		fclose(fp);
	}


	return 0;
}
