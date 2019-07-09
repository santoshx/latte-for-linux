#ifndef LATTE_H
#define LATTE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>


#define MSGSIZE		4
extern char ipv4_addr[20];
extern int port;
extern int iter;

void do_client(void);
void do_server(void);

#endif // LATTE_H
