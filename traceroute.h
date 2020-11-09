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
    struct addrinfo *info;

}           t_destination;

typedef struct s_flags {
    int h;
}       t_flags;


#endif