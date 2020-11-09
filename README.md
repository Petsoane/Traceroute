# Traceroute
A recreation of he traceroute program

# What is traceroute
Traceroute is a computer diagnostic comman that displays the possible routes and packet will take to
reach its destination. It also measures the transit delays of packets. It uses the ip protocol.

#  How does traceroute work
Traceroute sends ICMP packets to to a destination. It sets the ttl value of each packet start at 1 and incrementing 
untill it reaches a destination.
Although other versions of the traceroute command use a series of UPD packets to get to the same result.

# What is a TTL value
TTL value, also called hop limit, is the number of routers the packet is permited to go through before reaching
its destination.

# Important instructions and constraints
* Use a Makefile for project compilaion.
* Handle errors. THe program should not quite in an unexpected manner.
* The results should be identical to the original traceroute.
* Allowed functions.
    * getpid
    * getuid
    * getaddrinfo
    * gettimeofday
    * inet_ntoa
    * inet_pton
    * exit
    * select
    * setsockopt
    * recvfrom
    * sendto
    * sendto
    * htons
    * ntohs
    * bind
    * socket
    * bind
    * the functions of the printf familly
    * libft functions

# Side notes
I am going to use ICMP packets to implement this program.