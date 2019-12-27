/*
UDP based Client Application
*/

#include <stdio.h>
/*
Socket Header files
*/
#include <sys/types.h>          
#include <sys/socket.h>
#include <strings.h>		
#include <stdlib.h>	
#include <netinet/in.h>	
#include <arpa/inet.h>
#include <unistd.h>
#define MAX_SIZE 1024
#define PORT 4000
void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, serverlen;
	char sendbuffer[MAX_SIZE];
	char recvbuffer[MAX_SIZE];

	sockfd = socket(AF_INET, SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		error("Socket is not created");
		exit(1);
	}

	else
	{
		printf("Socket is created \n");
	}

	struct sockaddr_in serv_addr;
	serverlen = sizeof(serv_addr);
	bzero((char *)&serv_addr,serverlen);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(PORT);

	connect(sockfd, (struct sockaddr*)&serv_addr,serverlen);

	while(1)
	{
		printf("enter the message \n");
		fgets(sendbuffer, sizeof(sendbuffer),stdin);

		sendto(sockfd,sendbuffer,MAX_SIZE,0, (struct sockaddr*)&serv_addr, serverlen);
		recvfrom(sockfd, recvbuffer, MAX_SIZE, 0, NULL, NULL);

		printf("echo message from server: %s \n",recvbuffer);
	}
}
