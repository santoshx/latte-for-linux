#include "latte.h"

void do_client(void)
{
	int sockfd, numbytes;
	char rbuf[MSGSIZE];
	char sbuf[MSGSIZE];
	int i;
	struct hostent *he;
	struct sockaddr_in their_addr;

	if ((he = gethostbyname(ipv4_addr)) == NULL) {
		herror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(port);

	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	for(i = -1; i < iter; i++) {
		if (i == -1) {
			sbuf[0] = 0xd0;
			sbuf[1] = 0x14;
			sbuf[2] = 0x0;
			sbuf[3] = 0x0;
		} else {
			sbuf[3] = (i >> 24);
			sbuf[2] = (i >> 16);
			sbuf[1] = (i >> 8);
			sbuf[0] = (i /*>> 0*/);
		}

		if (send(sockfd, sbuf, 4, 0) == -1) {
			perror("send");
			exit(1);
		}

		if ((numbytes = recv(sockfd, rbuf, MSGSIZE, 0)) == -1) {
			perror("recv");
		}
	}
}
