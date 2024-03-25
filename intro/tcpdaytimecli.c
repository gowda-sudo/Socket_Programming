#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUF_LEN 1024

void errExt(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd;
	char buf[MAX_BUF_LEN];
	struct sockaddr_in srvAddr;
	int num = 0;

	if(2 != argc)
		errExt("usage: ./tcpdaytimecli <ip_addr>");

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errExt("socket error, exit");

	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(13);

	if((inet_pton(AF_INET, argv[1], (struct sockaddr*)&srvAddr.sin_addr)) <= 0)
		errExt("inet_pton failed");

	if(connect(sockfd, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) < 0)
		errExt("connect error");

	printf("socket connected to server\n");

	while((num = read(sockfd, buf, MAX_BUF_LEN)) > 0)
	{
		buf[num] = 0;
		fprintf(stdout, "%s\n", buf);
	}

	if(-1 == num)
		errExt("read failed");

	return 0;
}

