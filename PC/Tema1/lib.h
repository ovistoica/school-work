#ifndef LIB
#define LIB

#define MAX 1400
#define MAX_DATA 250
#define MAX_SEQ 1
#define DEFAULT_HEADER 0x01
#define DEFAULT_TIMEOUT 5
#define DEFAULT_EOL 0x0D
#define DEFAULT_LEN 255

#define inc_seq(k) if (k < MAX_SEQ) k = k + 1; else k = 0
#define ZERO(m) memset(&m, 0, sizeof(m));



enum Type {Send_Init = 'S', File_Header = 'F', Data = 'D',
			EOFile = 'Z', ACK = 'Y', NAK = 'N', EOT = 'B'};

typedef struct {
    int len;
    char payload[1400];
} msg;

typedef struct __attribute__((__packed__)) kerm_pack {
	char SOH; 		//Start of header
	unsigned char LEN;		//Length of packet
	unsigned char SEQ;		//Sequence number
	char TYPE;		//Type of packet
	char DATA[MAX_DATA];
	unsigned short CHECK; //Control sum
	char MARK;			//End of packet
}kerm_pack;

typedef struct __attribute__((__packed__)) send_init {
	unsigned int MAXL; //Max size of DATA
	unsigned short TIME; //Timeout in seconds
	unsigned int NPAD; //number of padding chars
	char PADC; //char used for padding
	char EOL; //char used in MARK

	char QCTL;
	char QBIN;
	char CHKT;
	char REPT;
	char CAPA;
	char R;
}send_init;



void init(char* remote, int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);
msg* receive_message_timeout(int timeout); //timeout in milliseconds
unsigned short crc16_ccitt(const void *buf, int len);

//Calculate the control sum for kerm_packet
unsigned short get_CHECK(kerm_pack pack) {
	size_t len = sizeof(pack) - sizeof(short) - sizeof(char);

	//Size of package without CHECK and MARK
	char buff[len];

	memcpy(buff, &pack, len);

	return crc16_ccitt(buff, len);
}


void wrap_pack(msg *t, const kerm_pack *p) {
	ZERO(t->payload);
	t->len = sizeof(*p);
	memcpy(t->payload, p, t->len);
}

#endif

