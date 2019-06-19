#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"

#include <time.h>

static char* dns_log_fname =        "dns.log";
static char* message_log_fname =    "message.log";
static char* dns_servers_fname =    "dns_servers.conf";

static char dns_servers[10][100];

// Reading host name from DNS server answer
unsigned char* getName(unsigned char *name_position, unsigned char *buffer,
   int *count)
{
  uint32_t offset, compressed = 0, i = 0, j;
  unsigned char *name;
  name = (unsigned char *)malloc(256);
  while (*name_position!= 0){
    // Message compression case 11000000 = 192
    if (*name_position>=192)
    {
      // Getting offset from beggining of buffer
      // TODO this might be wrong
      offset = (int)(*name_position - 192) * 256 + *(name_position + 1);
      name_position = buffer + offset;
      compressed = 1;
    }else {
      name[i++] = *name_position;
    }
    name_position++;

    if (compressed == 0)
    {
      // How much we parsed if message wasn't compressed
      *count = *count + 1;
    }
  }
  if(compressed == 1)
  {
    *count = 2; // If message was compressed we only moved two octets
  }
  name[i] = '\0';

  // Changing name to host format
  for(i = 0; i < strlen((char*)name); i++)
  {
    // ex 3www, w_len = 3;
    uint32_t w_len = name[i];
    for(j = 0; j < w_len; j++){
      name[i] = name[i + 1];
      i++;
    }
    name[i] = '.';
  }
  name[i-1] = '\0';

  return name;
}

/*
 * Convrt name to dns format www.google.com => 3www6google3com
 * */
void hostname_to_dns(char* host, unsigned char *dns)
{
  uint32_t j = 0, i = 0;

  // Without this the program stops before .com
  size_t h_size = strlen(host);
  host[h_size] = '.';
  host[h_size + 1] = '\0';

  dns = (unsigned char *)malloc(256);

  for(; i < strlen(host); i++){
    if(host[i] == '.'){
      *dns++ = (i - j) + '0';
      for(;j < i; j++){
        *dns++ = host[j];
      }
      j = i + 1;
    }
  }
}

void get_dns_servers(const char *fname)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Error reading file %s\n", fname);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        if(line[0] == '#') {
            continue;
        }
        printf("Line: %s\n", line);
        // TODO: didn't figure what to do with dns_servers yet.
    }
}

/*
 * Perform a DNS query
 * */
void perform_dns_query(char *host , int query_type, char *answer_out_buff)
{
    /* todo: build and perform query: */
    /**
        1. fill in "to_send" query buffer ()
        2. open a socket
        3. sendto the dns_header_t struct on that socket
        4. recv from the socket
        5. unpack answer and fill in answer_out_buff
        6. close socket
    */
   struct sockaddr_in serv_addr, dest_addr;
   dns_header_t *dns_header = NULL;
   dns_question_t *dns_question = NULL;

   unsigned char query_buff[65536], *qname;
   int sockfd;

   sockfd = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);
   if (sockfd < 0) {
       printf("Error openning socket. Abort\n");
       return;
   }

   dest_addr.sin_family = AF_INET;
   dest_addr.sin_port = htons(53);
   // TODO: replace 8.8.8.8 with the ones from resolv.conf
   dest_addr.sin_addr.s_addr = inet_addr("8.8.8.8");

   dns_header = (dns_header_t *) &query_buff;
   dns_header->id = (unsigned short) htons(getpid());
   dns_header->qr = 0; //query
   dns_header->opcode = 0; //This is a standard query
   dns_header->aa = 0; //Not Authoritative
   dns_header->tc = 0; //This message is not truncated
   dns_header->rd = 1; //Recursion Desired
   dns_header->ra = 0;
   dns_header->z = 0;
   dns_header->rcode = 0;

   dns_header->qdcount = htons(1); //we have only 1 question
   dns_header->ancount = 0;
   dns_header->nscount = 0;
   dns_header->arcount = 0;
   qname = (unsigned char *)&query_buff[sizeof(dns_header_t)];

   if(query_type == PTR){
     strcat(host, ".in-addr.arpa");
   }

   hostname_to_dns(host,qname);
   printf("QNAME: %s\n", qname);
   int num_bytes_to_send = sizeof(dns_header_t) + sizeof(dns_header_t) + strlen((const char *) qname);

   dns_question = (dns_question_t*) &query_buff[sizeof(dns_header_t) + (strlen((const char *) qname) + 1)];

   dns_question->qtype = htons( query_type );
   dns_question->qclass = htons(1);

    printf("\nSending Packet...\n");
    if( sendto(sockfd, query_buff, num_bytes_to_send, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
    {
        perror("sendto failed");
    }
    printf("Done\n");

    //Receive the answer
    unsigned char recv_buff[65536];
    socklen_t dest_addr_size = sizeof(dest_addr);
    printf("\nReceiving answer...\n");
    while (1) {
        int ret = recvfrom (sockfd, recv_buff , sizeof(recv_buff), 0 , (struct sockaddr *)&dest_addr , &dest_addr_size );
        if (ret < 0) {
            printf("Err on recv: %s\n", strerror(ret));
        } else {
            printf("Done\n");
            break;
        }
        // TODO: Remove this after finish debug
        sleep(1);
    }

    dns_header = (dns_header_t *) &recv_buff;

    printf("\nThe response contains : ");
    printf("\n %d Questions.",ntohs(dns_header->qdcount));
    printf("\n %d Answers.",ntohs(dns_header->ancount));
    printf("\n %d Authoritative Servers.",ntohs(dns_header->nscount));
    printf("\n %d Additional records.\n\n",ntohs(dns_header->arcount));
    printf("\n\n%s\n", recv_buff);
    printf("RCODE: %d\n", atoi(dns_header->rcode));
  }

void log_answer(unsigned char *recv_buff, unsigned char *qname)
{
    /* todo: write out_buf into log file */
    dns_header_t *header = (dns_header_t *)&recv_buff;
    dns_answer_t answers[header->ancount], authorities[header->nscount];
    dns_answer_t additional[header->arcount];
    uint32_t i,j, offset;
    u_char *helper;
    int step;

    // Skipping header querry
    offset = sizeof(dns_header_t) + strlen((char*)qname) + 1 + sizeof(dns_question_t);
    helper = recv_buff + offset;
    step = 0;

    // Parsing answers
    for (i = 0; i < header->ancount; i++){
      answers[i].name = getName(helper, recv_buff, &step);
      helper = helper + step;

      answers[i].dns_ans_info = (dns_rr_t *)helper;
      helper = helper + sizeof(dns_rr_t);

      // If it is IPv4
      if(ntohs(answers[i].dns_ans_info->rtype) == 1)
      {
        uint32_t data_len = answers[i].dns_ans_info->rdlength;
        answers[i].rdata = (unsigned char*)malloc(data_len);
        for(j = 0; j < data_len; j++){
          answers[i].rdata[j] = *helper++;
        }
        answers[i].rdata[data_len] = '\0';
      } else{
        answers[i].rdata = getName(helper, recv_buff, &step);
        helper += step;
      }
    }

    // Parsing authorities
    for (i = 0; i < header->nscount; i++){
      authorities[i].name = getName(helper, recv_buff, &step);
      helper = helper + step;

      answers[i].dns_ans_info = (dns_rr_t *)helper;
      helper = helper + sizeof(dns_rr_t);

      uint32_t data_len = answers[i].dns_ans_info->rdlength;
      answers[i].rdata = (unsigned char*)malloc(data_len);
      for(j = 0; j < data_len; j++){
        answers[i].rdata[j] = *helper++;
      }
      answers[i].rdata[data_len] = '\0';
    }

    for (i = 0; i < header->arcount; i++){
      additional[i].name = getName(helper, recv_buff, &step);
      helper = helper + step;

      additional[i].dns_ans_info = (dns_rr_t *)helper;
      helper = helper + sizeof(dns_rr_t);

      // If it is IPv4
      if(ntohs(additional[i].dns_ans_info->rtype) == 1)
      {
        uint32_t data_len = additional[i].dns_ans_info->rdlength;
        additional[i].rdata = (unsigned char*)malloc(data_len);
        for(j = 0; j < data_len; j++){
          additional[i].rdata[j] = *helper++;
        }
        additional[i].rdata[data_len] = '\0';
      } else{
        additional[i].rdata = getName(helper, recv_buff, &step);
        helper += step;
      }
    }

    // Name Class Type Addr
    // TODO: Scris strucuri in fisiere


    return;
}

void print_to_file(dns_answer_t *answer, unsigned short size, char *filename)
{
  FILE *fp = fopen(filename, "a");
  unsigned int i;
  char class[2];
  char type[5];
  fprintf(fp, ";;  ANSWER SECTION:\n");
  for(i = 0; i < size; i++)
  {
    fprintf(fp, "%s ",answer[i].name);

    if(answer[i].dns_ans_info->rclass == 1) strcpy(class, "IN");
    else if(answer[i].dns_ans_info->rclass == 3) strcpy(class,"CH");
    else if(answer[i].dns_ans_info->rclass == 4) strcpy(class, "HS");

    if(answer[i].dns_ans_info->rtype == A) strcpy(type, "A");
    else if(answer[i].dns_ans_info->rtype == NS) strcpy(type, "NS");
    else if(answer[i].dns_ans_info->rtype == PTR) strcpy(type, "PTR");
    else if(answer[i].dns_ans_info->rtype == MX) strcpy(type, "MX");
    else if(answer[i].dns_ans_info->rtype == CNAME) strcpy(type, "CNAME");
    else if(answer[i].dns_ans_info->rtype == SOA) strcpy(type, "SOA");
    else if(answer[i].dns_ans_info->rtype == TXT) strcpy(type, "TXT");

    fprintf(fp, "%s %s %s\n",class, type, answer[i].rdata);
  }

  fclose(fp);

}


int get_query_type_from_arg(char *query_arg)
{
    if (!strcmp("A", query_arg)) return A;
    else if (!strcmp("NS", query_arg)) return NS;
    else if (!strcmp("CNAME", query_arg)) return CNAME;
    else if (!strcmp("MX", query_arg)) return MX;
    else if (!strcmp("SOA", query_arg)) return SOA;
    else if (!strcmp("TXT", query_arg)) return TXT;
    else if (!strcmp("PTR", query_arg)) return PTR;

    else // invalid query_arg, return err;
        return -1;
}

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME> <QUERY>\n\t%s -a <IP> <QUERY>\n", name, name);
	return 1;
}

int main (int argc, char **argv)
{
    char answer_out_buff[65536];
    char *host, *query_arg;
    unsigned char *qname = NULL;
    int query_type;

    // If bad num of params passed, abort
    if (argc < 3) {
	    return usage(argv[0]);
	}

    host = argv[1];
    query_arg = argv[2];

    // Get query int value
    query_type = get_query_type_from_arg(query_arg);
    if (query_type == -1) {
        printf ("Invalid query type, abort ...\n");
        return -1;
    }

    // TODO: Check if host is in right format:
    // ip (e.g. 1.1.1.1) or address (myawesomednsserver.com)

    // get_dns_servers(dns_servers_fname);

	// Perform query
    perform_dns_query(host, query_type,  answer_out_buff);

	return 0;
}
