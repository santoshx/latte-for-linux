#include "latte.h"

void do_server(void)
{

	int sockfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cli;
	char buf[MSGSIZE];
	int i;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		perror("bind: ");
		exit(0);
	}

	if ((listen(sockfd, 5)) != 0) {
		perror("listen :");
		exit(0);
	}
	len = sizeof(cli);

	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0) {
		perror("accept: ");
		exit(0);
	}

	bzero(buf, MSGSIZE);
	read(connfd, buf, sizeof(buf));
	if ((buf[0] == 0xffffffd0) && (buf[1] == 0x14)) {
		write(connfd, buf, sizeof(buf));
		for (i = -1; i < iter; i++) {
			bzero(buf, MSGSIZE);
			read(connfd, buf, sizeof(buf));
			write(connfd, buf, sizeof(buf));
		}
	}

	close(connfd);
	close(sockfd);
}
