#include "traceroute.h"

char* reverse_dns_lookup(char *ip_addr);

int trace(int sockfd, t_destination *dest)
{
    int sstatus, addr_len;
    int k;
    int flag;
    int hop_limit = 3;
    int msg_count = 0;

    struct s_pkt pkt;
    struct timespec start, end;


    while (hop_limit--){
        flag = 1;

        // set the packet
        bzero(&pkt, sizeof(pkt));

        pkt.hdr.type = ICMP_ECHO;
        pkt.hdr.un.echo.id = getpid();
        for (k = 0; k < sizeof(pkt.msg) - 1; k++){
            pkt.msg[k] = k + '0';
        }
        pkt.msg[k] = 0;
        pkt.hdr.un.echo.sequence = msg_count++;
        pkt.hdr.checksum = checksum(&pkt, sizeof(pkt));

        clock_gettime(CLOCK_MONOTONIC, &start);
        struct sockaddr *tmp = dest->info->ai_addr;
        sstatus = sendto(sockfd, &pkt, sizeof(pkt), 0, tmp, sizeof(*tmp));
        if (sstatus != 0) flag = 1;

        struct sockaddr_in r_addr;
        addr_len = sizeof(r_addr);

        // recieve info
        sstatus = recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&r_addr, &addr_len);
        if (sstatus <= 0) printf(" *");
        else {
            clock_gettime(CLOCK_MONOTONIC, &end);
            double timeElapsed = ((double)(end.tv_nsec - start.tv_nsec))/1000000.0;
            long double rtt_msec = (end.tv_sec -start.tv_sec) * 1000.0 + timeElapsed;

            if(pkt.hdr.type == 3)
                printf("* ");
            else{
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)&r_addr;
                void *addr = &(ipv4->sin_addr);
                inet_ntop(dest->info->ai_family, addr, dest->ipstr, sizeof(dest->ipstr));
                char *name = reverse_dns_lookup(dest->ipstr);
                if (msg_count == 1){
                    if (name != NULL)
                        printf(" %s (%s) %.3Lf ms", name, dest->ipstr, rtt_msec);
                    else {
                        printf(" %s (%s) %.3Lf ms", dest->ipstr, dest->ipstr, rtt_msec);
                    }
                }
                else {
                    printf(" %.3Lf ms", (rtt_msec/60.0) * 100);
                }
            }
        }
    }
    if (ft_strcmp(dest->dest_str, dest->ipstr))
        return 0;
    return 1;

}


// char* reverse_dns_lookup(char *ip_addr) 
// { 
//     struct sockaddr_in temp_addr;     
//     socklen_t len; 
//     char buf[NI_MAXHOST], *ret_buf; 
  
//     temp_addr.sin_family = AF_INET; 
//     temp_addr.sin_addr.s_addr = inet_addr(ip_addr); 
//     len = sizeof(struct sockaddr_in); 
  
//     if (getnameinfo((struct sockaddr *) &temp_addr, len, buf,  
//                     sizeof(buf), NULL, 0, NI_NAMEREQD))  
//     { 
//         printf("Could not resolve reverse lookup of hostname\n"); 
//         return NULL; 
//     } 
//     ret_buf = (char*)malloc((strlen(buf) +1)*sizeof(char) ); 
//     strcpy(ret_buf, buf); 
//     return ret_buf; 
// } 