#include "traceroute.h"


int set_ttl(int sockfd, int ttl_val);

int main(int argc, char **argv)
{
    t_destination destination;
    t_flags flags;
    int sstatus;

    if (argc < 2){
        usage(argv[0]);
        return (-1);
    }

   	// init program start.
	if (init(argc, argv, &flags, &destination) != 0){
		return (2);
	}
	if (flags.h == 1){
		help();
		return (0);
	}

    // create the socket.
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0 ){
		fprintf(stderr, "ft_ping: socket creation: %s", gai_strerror(sockfd));
		return (1);
	}

    struct timeval time_out;
	int RECV_TIMEOUT = 1;

	time_out.tv_sec = RECV_TIMEOUT;
	time_out.tv_usec = 0;

	sstatus = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&time_out, sizeof time_out);
	if (sstatus != 0){
		fprintf(stderr, "Error setting timeout value: %s", gai_strerror(sstatus));
		return (1);
	}

    // set the ttl.

    int hop_limit = 30;
    int hop = 1;

    printf("Traceroute to %s (%s) , 30 hops max, 64 byte packets\n",
                destination.dest_str, destination.ipstr);
    while (hop < hop_limit){
        if (set_ttl(sockfd, hop) != 0) return -1;

        printf("%d", hop++);
        if (trace(sockfd, &destination) == 1) break;
        printf("\n");
    }


    return (0);
}
