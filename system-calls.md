This file explains all the system calls and functions used in socket programming

-----------------------------------------------------------------------------------------------------------------------------

-->SOCKET
The socket() call creates an unnamed socket and returns a file descriptor to the calling process.  The function prototype is as follows:

    int socket(int domain, int type, int protocol);

where domain specifies the address domain, type specifies the socket type, and the third argument is the protocol (this is usually set to 0 to automatically select the appropriate default).  Here is a typicalsocket() call:

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

This establishes a socket in the Internet domain, and configures it for stream-oriented communication using the default TCP protocol. 

-----------------------------------------------------------------------------------------------------------------------------

-->AF_INET
AF_INET is the address family that is used for the socket you're creating (in this case an Internet Protocol address). The Linux kernel, for example, supports 29 other address families such as UNIX sockets and IPX, and also communications with IRDA and Bluetooth (AF_IRDA and AF_BLUETOOTH, but it is doubtful you'll use these at such a low level).

For the most part sticking with AF_INET for socket programming over a network is the safest option.

-----------------------------------------------------------------------------------------------------------------------------

-->BZERO
 bzero((char *) &serv_addr, sizeof(serv_addr));
The function bzero() sets all values in a buffer to zero. It takes two arguments, the first is a pointer to the buffer and the second is the size of the buffer. Thus, this line initializes serv_addr to zeros.

-----------------------------------------------------------------------------------------------------------------------------

-->SOCKADDR_IN
/* a structure to contain an internet address 
   defined in the include file in.h */
struct sockaddr_in {
        short   sin_family; /* should be AF_INET */
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8]; /* not used, must be zero */
};

struct in_addr {
   unsigned long s_addr;
};

-----------------------------------------------------------------------------------------------------------------------------

-->ATOI
     portno = atoi(argv[1]);
The port number on which the server will listen for connections is passed in as an argument, and this statement uses the atoi() function to convert this from a string of digits to an integer.

-----------------------------------------------------------------------------------------------------------------------------

-->BIND

The bind() system call associates a socket with a particular name or address.  In other words, this call specifies the port a server process will listen to.  The function prototype is as follows:

    int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);

where sockfd is the socket file descriptor returned from a previous socket() call, my_addr is a pointer to a structure containing the address to bind to, and addrlen is the size of the structure.  The key to using this call is understanding how to fill in the fields of the sockaddr structure.  This structure (defined in netinet/in.h) contains fields for the address family (sin_family), the IP address of the host (sin_addr.s_addr), the port number (sin_port), and some padding.  Here is a typical bind() call:

    bind (sockfd, (struct sockaddr *) &server, sizeof(server));

This call binds the socket sockfd to the address contained in the structure named server.  Within the structure server, the field family has been set to AF_INET, specifying the Internet address domain.  The port number has been set (using the htons() function for portability) to any currently unused number on that system.  Finally, since this is a server, the IP address has been set to INADDR_ANY, specifying that connections will be accepted from any other host.

-----------------------------------------------------------------------------------------------------------------------------

-->LISTEN
The listen() system call establishes the size of the incoming request queue.  Although the listen() call is not strictly necessary, it is commonly used.  The function prototype is as follows:

    int listen(int s, int backlog);

where s is the socket and backlog is the size of the queue (i.e. the number of connections that can be waiting while the process is handling a particular connection. This should be set to 5, the maximum size permitted by most systems.).  Here is a typical listen() call:

    listen (sockfd, MAXCONNECT);

This call specifies that the socket sockfd will queue up to MAXCONNECT requests. 

-----------------------------------------------------------------------------------------------------------------------------

-->HTONS
Because systems may use different byte-ordering for data objects such as numbers, functions have been created to allow systems to communicate using a standardized network-order format.  Here is the function prototype for one of them:

    uint16_t htons(uint16_t hostshort);

where a short is the value being converted into its network-order version.  As an example of its use, here is the function call used to convert the integer representation of the desired port number into the correct network format:

    server.sin_port = htons ((short) 3000 + BlockedOn);

In this example, the port number 3002 will be converted and assigned to the appropriate field of the sockaddr structure. 

htons() - host to network short
htonl()- host to network long
ntohs()- network to host short
ntohl()- network to host long

-----------------------------------------------------------------------------------------------------------------------------

-->FOR(;;)
It's an infinite loop, equivalent to while(true). When no termination condition is provided, the condition defaults to true.

-----------------------------------------------------------------------------------------------------------------------------

-->ACCEPT
Finally, the accept() system call causes the server process to block until a client attempts to connect.  The function prototype is as follows:

    int accept(int s, struct sockaddr *addr, socklen_t *addrlen);

where s is the socket, addr is a pointer to a structure of type sockaddr, and addrlen is a pointer to a variable containing the size of the structure.  The address pointer is a reference to an address structure containing information about the connecting client, in case that information is desired.  In other words, this call will cause the system to populate the fields of the sockaddr structure with information about the client that has just connected.  For example, this information could be used to determine the hostname of the connecting client process.  The accept() system call returns a new file descriptor that is the one normally used for subsequent communications.  Here is a typical accept() call:

    tempfd = accept (sockfd, (struct sockaddr *) &client, &len);

This will cause the process to wait for a connection request on socket sockfd, then return information about the connecting process in the structure named client, and return a new socket descriptor calledtempfd for communications. 
