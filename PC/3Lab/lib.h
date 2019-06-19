#ifndef LIB
#define LIB

#define TYPE1		1
#define TYPE2		2
#define TYPE3		3
#define TYPE4		4
#define ACK_T1		"ACK(TYPE1)"
#define ACK_T2		"ACK(TYPE2)"
#define ACK_T3		"ACK(TYPE3)"

#define MSGSIZE		1400
#define PKTSIZE		1396

typedef struct {
  	int len;
  	char payload[MSGSIZE];
} msg;

//Struct that includes parity and number of bytes
typedef struct __attribute__((__packed__)) my_pkg {
	int parity;
	int nr_bytes;
	char my_payload[1400 - 2*sizeof(int)];
}my_pkg;


void init(char* remote,int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);

#endif

