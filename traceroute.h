#ifndef FT_TRACE
#define FT_TRACE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#include "libft/libft.h"

typedef struct s_tms {
    char *ping_dest;
    char *fqdn;
    char ipstr[INET6_ADDRSTRLEN];
    char dest_str[INET6_ADDRSTRLEN];

    struct addrinfo *info;

}           t_destination;

typedef struct s_flags {
    int h;
}       t_flags;

struct s_pkt {
    struct icmphdr hdr;
    char msg[64 - sizeof(struct icmphdr)];
};

void usage(char *name);
int set_flags(char *in, t_flags *flags);
int get_dest_info(t_destination *node);
void help();


// Core functions
unsigned short checksum (void *b, int len);
int init(int argc, char **argv, t_flags *flags, t_destination *destination);

int set_ttl(int sockfd, int ttl_val);
int trace(int sockfd, t_destination *dest);


#endif