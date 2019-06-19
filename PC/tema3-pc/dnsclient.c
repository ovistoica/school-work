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

FILE *fptr;
FILE *fptr_messages;

// helper function that shows the hex repr of the bytes in buffer
static void hex_dump(unsigned char *buffer, size_t len) {
    int it;

    for (it = 0; it < len; it ++) {
        printf("%02x ", buffer[it]);
    }

    printf("\n");
}

//  convert from www.google.com to 3www6google3com
static int convert_url_to_labels_format(unsigned char *buffer, char *name) {

    if (NULL == buffer || NULL == name) {
        return 0;
    }

    int it;
    char *token,
         name_cpy[strlen(name) + 1];

    memcpy(name_cpy, name, strlen(name) + 1);

    unsigned char *buff_cpy = buffer;
    token = strtok(name_cpy, ".");

    while (NULL != token) {
        *buff_cpy = strlen(token);
        memcpy(buff_cpy + 1, token, strlen(token));
        buff_cpy += sizeof(unsigned char) + strlen(token);
        token = strtok(NULL, ".");
    }

    return strlen((char*) buffer + 1);
}

// fetch dns servers from dns_Servers.conf
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

    int it = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if(line[0] == '#') {
            continue;
        }
        strncpy(dns_servers[it], line, strlen(line));
        it ++;
    }
}

// Build the query to be sent to server
int build_dns_querry(char *host, int query_type, unsigned char *dns_query)
{
    dns_header_t    *dns_header = NULL;
    dns_question_t  *dns_question = NULL;
    size_t query_len = sizeof(dns_header_t);

    dns_header = (dns_header_t *) dns_query;
    dns_header->id = 43690; // aa aa in hex ( dummy )
    dns_header->qr = 0;     //query
    dns_header->opcode = 0; //This is a standard query
    dns_header->aa = 0;     //Not Authoritative
    dns_header->tc = 0;     //This message is not truncated
    dns_header->rd = 1;     //Recursion Desired
    dns_header->ra = 0;
    dns_header->z = 0;
    dns_header->rcode = 0;

    dns_header->qdcount = htons(1); //we have only 1 question
    dns_header->ancount = 0;
    dns_header->nscount = 0;
    dns_header->arcount = 0;

    unsigned char *qname = dns_query + sizeof(dns_header_t);
    convert_url_to_labels_format(qname, host);
    query_len += strlen((char *) qname) + 1;

    dns_question = (dns_question_t *) &dns_query[sizeof(dns_header_t) + strlen((char*) qname) + 1];
    dns_question->qtype = htons(query_type);
    dns_question->qclass = htons(1);
    query_len += sizeof(dns_question_t);

    return query_len;
}

// helper function that decodes format such as 3www5yahoo3com into www.yahoo.com
int get_name_from_answer(unsigned char *buffer, unsigned char *dns_query)
{
    unsigned char *helper = dns_query;
    unsigned char *buf_helper = buffer;
    uint8_t idx = *helper;
    uint8_t query_idx = 0;

    while (idx != 0) {
        memcpy(buf_helper, helper + 1, idx);

        buf_helper += idx;
        *buf_helper = '.';
        helper += idx + 1;
        buf_helper ++;

        idx = *(helper);
        query_idx += idx + 1;
    }

    return strlen((char *)buffer);
}

// helper function that concatenates 2 bytes into one unsigned short value
unsigned short fetch_u_short(unsigned char *answer, int index)
{
    return (answer[index] << 8) | (answer[index + 1]);
}

// helper function to ret the string repr of qtype
char *get_type_from_int(unsigned short type)
{
    switch (type) {
        case A: return "A";
        case NS: return "NS";
        case CNAME: return "CNAME";
        case MX: return "MX";
        case SOA: return "SOA";
        case TXT: return "TXT";
        case PTR: return "PTR";
    }

    return "";
}

// helper function that retuns the string repr of qclsas
char *get_class_from_int(unsigned short class)
{
    return (class == 1) ? "IN" : "OUT"; // i think :P
}

// helper function that builds a string val ip from its hex bytes representative
void get_ip_from_answer(unsigned char *answer, int index, char *ip_buf)
{
    unsigned char x = answer[index];
    unsigned char y = answer[index + 1];
    unsigned char z = answer[index + 2];
    unsigned char t = answer[index + 3];

    sprintf(ip_buf, "%u.%u.%u.%u", x, y, z, t);
}

// Parse answer received from DNS and write output in dns.log file
void process_answer(unsigned char *dns_query, int index) {

    unsigned char *answer = dns_query + index;
    unsigned short answer_name = fetch_u_short(answer, 0);
    unsigned short name_idx = answer_name & 0x00FF;
    unsigned char name[64];
    int len = get_name_from_answer(name, dns_query + name_idx);
    // name[strlen((char *) name) - 1] = '\0';

    unsigned short type = fetch_u_short(answer, sizeof(short));
    char *type_str = get_type_from_int(type);

    unsigned short class = fetch_u_short(answer, 2 * sizeof(short));
    char *class_str = get_class_from_int(class);

    unsigned short data_len = fetch_u_short(answer, 5 * sizeof(short));
    printf("data len: %hu\n", data_len);

    // log common ones such as name, qtype, qclass
    fprintf(fptr, "%s\t%s\t%s\t", name, class_str, type_str);

    // each query_type comes back with different info, try to parse and log that here.
    switch (type) {
        case A: {
            char ip[16];
            get_ip_from_answer(answer, 6 * sizeof(short), ip);

            fprintf(fptr, "%s\n", ip);
        }
        case MX: {
            unsigned char addr[128];
            int len2 = get_name_from_answer(addr, (answer + (7 * sizeof(short))));
            // addr[strlen((char *) addr) - 1] = '\0';

            fprintf(fptr, "%s\n", addr);
        }
        case NS: {

        }
        case SOA: {

        }
        case TXT: {

        }
        case PTR: {

        }
        default:
            break;
    }

    fprintf(fptr, "\n");
}

// helper function to write in folder the query hex values that are being set to server
void write_query_message(unsigned char *msg, int size) {

    int i;
    for (i = 0; i < size; i ++) {
        fprintf(fptr_messages, "%02x ", msg[i]);
    }

    fprintf(fptr_messages, "\n\n");
}

/*
 * Perform a DNS query
 * */
void perform_dns_query(char *host, int query_type)
{
    struct sockaddr_in dest_addr;
    dns_header_t    *dns_header = NULL;

    unsigned char dns_query[512] = {0}; // Messages carried by UDP are restricted to 512 bytes
    int sockfd, querry_num_bytes = build_dns_querry(host, query_type, dns_query);

    // write query in messages.log
    write_query_message(dns_query, querry_num_bytes);

    // open socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        printf("Error openning socket. Abort\n");
        return;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(53);
    dest_addr.sin_addr.s_addr = inet_addr("8.8.8.8"); // TODO: replace 8.8.8.8 with the ones from resolv.conf

    // Send dns query
    printf("\nSending DNS query...\n");
    if (sendto(sockfd, dns_query, querry_num_bytes, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
    {
        perror("sendto failed");
    }
    printf("Done\n");

    //Receive the answer
    socklen_t dest_addr_size = sizeof(dest_addr);
    printf("\nReceiving answer...\n");
    // busy waiting for a response
    while (1)
    {
        int ret = recvfrom(sockfd, dns_query, sizeof(dns_query), 0, (struct sockaddr *)&dest_addr, &dest_addr_size);
        if (ret < 0)
        {
            printf("Err on recv: %s\n", strerror(ret));
        }
        else
        {
            printf("Done\n");
            break;
        }
        // TODO: Remove this after finish debug
        sleep(1);
    }

    dns_header = (dns_header_t *)&dns_query;

    printf("\nThe response contains : ");
    printf("\n %d Questions.", ntohs(dns_header->qdcount));
    printf("\n %d Answers.", ntohs(dns_header->ancount));
    printf("\n %d Authoritative Servers.", ntohs(dns_header->nscount));
    printf("\n %d Additional records.\n\n", ntohs(dns_header->arcount));

    int it;
    // Reading answers
    fprintf(fptr, ";; ANSWER SECTION:\n");
    dns_answer_t *answer_data = (dns_answer_t *) &dns_query[querry_num_bytes];
    printf("name index: %hu\n", htons(answer_data->name));
    printf("rtype: %hu\n", htons(answer_data->dns_ans_info.rtype));
    printf("rclass: %hu\n", htons(answer_data->dns_ans_info.rclass));
    printf("ttl: %hu\n", htons(answer_data->dns_ans_info.ttl));
    for(it = 0; it < ntohs(dns_header->ancount); it++)
    {
        process_answer(dns_query, querry_num_bytes);
    }

    // Reading Authoritative Servers
    for(it = 0; it < ntohs(dns_header->nscount); it++)
    {

    }

    // Reading Aditional records
    for(it = 0; it < ntohs(dns_header->arcount); it++)
    {

    }

    fprintf(fptr, "\n\n");
}


int get_query_type_from_arg(char *query_arg)
{
    if (!strcmp("A", query_arg)) return A;
    else if (!strcmp("NS", query_arg)) return NS;
    else if (!strcmp("CNAME", query_arg)) return CNAME;
    else if (!strcmp("MX", query_arg)) return MX;
    else if (!strcmp("SOA", query_arg)) return SOA;
    else if (!strcmp("TXT", query_arg)) return TXT;
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
    char buffer[256];

    // If bad num of params passed, abort
    if (argc < 3)
    {
        return usage(argv[0]);
    }

    host = argv[1];
    query_arg = argv[2];

    // Sanitize input
    // Get query int value
    query_type = get_query_type_from_arg(query_arg);
    if (query_type == -1)
    {
        printf("Invalid query type, abort ...\n");
        return -1;
    }

    // Open needed files
    fptr = fopen(dns_log_fname, "a");
    if (fptr == NULL)
    {
        printf("Error opening %s\n", dns_log_fname);
        exit(1);
    }

    fptr_messages = fopen(message_log_fname, "a");
    if (fptr_messages == NULL)
    {
        printf("Error opening %s\n", message_log_fname);
        exit(1);
    }

    fprintf(fptr, "; %s - %s %s\n\n", dns_servers[0], host, query_arg);
    // perform query
    perform_dns_query(host, query_type);

    fclose(fptr);
    fclose(fptr_messages);

    return 0;
}
