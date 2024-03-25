#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MAX_BUF_LEN 1024

void errExt(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

int main(int argc, char* argv[])
{
	int sockfd, listenfd;
	struct sockaddr_in srvAddr;
	char buf[MAX_BUF_LEN] = {0};
	time_t ticks;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errExt("socket failed");


	memset(&srvAddr, 0, sizeof(srvAddr));

	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(13);
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) < 0)
		errExt("bind error");

	if(listen(sockfd, 5) < 0)
		errExt("listen failed");

	for(;;)
	{
		printf("waiting to accept connection\n");
		listenfd = accept(sockfd, (struct sockaddr*)NULL, NULL);
		printf("connection accepted\n");
		
		ticks = time(NULL);
		snprintf(buf, MAX_BUF_LEN, "%.24s\r\n", ctime(&ticks));
		write(listenfd, buf, sizeof(buf));
		close(listenfd);
	}

	return 0;
}
