#include "latte.h"

char ipv4_addr[20];
int port;
int iter;

int main(int argc, char *argv[])
{
	int opt;
	bool client_mode = false;

	if (argc < 2) {
		printf("How to use it? (bing Windows Latte)\n");
		exit(1);
	}

	while((opt = getopt(argc, argv, "csa:i:")) != -1) {
		switch(opt) {
			case 'c':
				client_mode = true;
				break;
			case 's':
				client_mode = false;
				break;
			case 'a': {
					int colon_location = strchr(optarg, ':') - optarg;
					if (NULL == memcpy(ipv4_addr, optarg, colon_location)) {
						perror("ipv4_addr");
						exit(1);

					}
					printf("ipv4_addr = %s\n", ipv4_addr);
					port = atoi(optarg + colon_location + 1);
					printf("port = %d\n", port);
				}
				break;
			case 'i':
				iter = atoi(optarg);
				printf("iterations = %d\n", iter);
				break;
		}
	}

	if (client_mode)
		do_client();
	else
		do_server();

	return 0;
}
