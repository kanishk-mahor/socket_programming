

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#define MAX_SIZE 1024
#include<unistd.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}


int main(int args, char *argv[])
{
	int sockfd, portnumber, clilen, recvbytes;

	char buffer[MAX_SIZE];

	if (args < 2)
	{
		printf("errro !! enter port number");
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sockfd < 0)
	{
		error("socket is not created");
	}
	else
	{
		printf("socket is created\n");
	}

	struct sockaddr_in serv_addr, cli_addr;
	bzero((char*)&serv_addr, sizeof(serv_addr));
	portnumber = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnumber);

	int ret = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	if (ret < 0)
	{
		error("error in building with the address");
	}
	else
	{
		printf("server started \n");
	}

	while(1)
	{
		clilen = sizeof(cli_addr);
		recvbytes = recvfrom(sockfd,buffer,MAX_SIZE,0,(struct sockaddr*)&cli_addr, &clilen);
		printf("the msg from client : %s\t", buffer);

		sendto(sockfd,buffer,MAX_SIZE,0,(struct sockaddr*)&cli_addr,clilen);
	}
close(sockfd);
}

