#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv){
	msg r,t;
	init(HOST,PORT);
	char nume_fis[50];
	int n, i;


	//Number of files
	if (recv_message(&r)<0){
		perror("Receive message");
		return -1;
	}
	n = r.payload[0];
	sprintf(t.payload,"ACK(%s)",r.payload);
	t.len = strlen(t.payload+1);
	send_message(&t);


	for(i = 0; i < n; i++) {

		if (recv_message(&r)<0){
			perror("Receive message");
			return -1;
		}

		//Get file name
		strcpy(nume_fis, r.payload);
		strcat(nume_fis, ".received");

		//Send ACK
		sprintf(t.payload,"ACK(%s)",r.payload);
		t.len = strlen(t.payload+1);
		send_message(&t);

		FILE *fp = fopen(nume_fis, "wb");

		while(1) {

			if (recv_message(&r)<0){
				perror("Receive message");
				return -1;
			}

			//Send ACK
			sprintf(t.payload,"ACK(%s)",r.payload);
			t.len = strlen(t.payload+1);
			send_message(&t);

			if(r.payload[0] == 1) {
				break;
			}

			//Write to file
			fwrite(r.payload + 1, 1, r.len - 1, fp);
		}
		fclose(fp);
	}

	return 0;
}
