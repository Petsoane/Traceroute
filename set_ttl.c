#include "traceroute.h"

int set_ttl(int sockfd, int ttl_val)
{
    int sstatus;

    sstatus = setsockopt(sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val));
	if ( sstatus != 0){
		fprintf(stderr, "ttl_val: %s", gai_strerror(sstatus));
		return 1;
	}


    return sstatus;
}