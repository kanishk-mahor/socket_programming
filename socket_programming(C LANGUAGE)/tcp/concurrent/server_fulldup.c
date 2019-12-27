#include<stdio.h>	//printf and scanf
#include<sys/types.h>	//socket system cell
#include<sys/socket.h>	//socket system
#include<strings.h>
#include <unistd.h>
#include<netinet/in.h>
#include<stdlib.h> //exit
void error (char *msg)
{
	perror(msg);
	exit(1);
}
int connfd;	//server port number and client address len declration
//main function
int main(int argc, char *argv[])
{
	int sockfd;	//socket descripter for accept system call to perform read and write operation
			//connfd descripter will be used for data exchange betrween client and server
	
	int portnumber,clilen;	//buffer to read and write the data b/w client & server . ensure to clear the buffer once you perform read/write and subsequently needs read/write operations
	char sendbuffer[1024];
	char recvbuffer[1024];

//fork system call return type///
pid_t cpid;	


//server /client structure declaration
	struct sockaddr_in serv_addr, cli_addr; //declration for bytes read at the server and written by the client  
	int readbytes;	//condition check for commandline arguments
   if(argc<2)
	{	
	error("error !!!!!! enter the port number while running the program ./.out <port number> \n");
	}
	//creation of master socket for bind, listen and accept system calls 
		//refer man page socket(2) 
	//AF_INET for IPv4 internetprotocols
	//SOCK_STREAM -TCP based stream
	//0 -protocol(decided by system/kernel/os) (imp to mention if TCP/UDP protocol is not used for socket type)

	sockfd = socket(AF_INET,SOCK_STREAM, 0); 	//sockfd is socket descripter 
	//condition check for socket return type
	if(sockfd < 0)
		{	error("socket is not created ");
		}
	else 
		{printf("socket is created succesfully\n");
		}
	//clear/clean the structure buffer with -either be zero or member set to avoid any garbage value
	bzero((char *)&serv_addr,sizeof(serv_addr));
	portnumber = atoi(argv[1]);	//initialize the member of structure
	serv_addr.sin_family = AF_INET; 	//IPv4 internet family 
	// INADDR_ANY -binds to all the available
	//interfaces of host machine/work staion
	//else specific inrterfaces can be initilazided
	//like : local host 127.0.0.1
	//wifi - ijnterface eg 192.168.75.1
	//layman termi: client can connect to srver with all interface of server
	serv_addr.sin_addr.s_addr = INADDR_ANY;    //
	//htons - host to network byte order(short) //network wide order BigEndian
	serv_addr.sin_port = htons(portnumber); 	//bind the socket with server address/domain

	int ret = bind(sockfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret <0)
	{
	error("error in binding the socket ");
	}
	else
	{
	printf("socket binding is succesfull");
	}
	
	int backlog = 5;
	int ret1 = listen(sockfd,backlog);
	if(ret1 < 0)
	{
	printf("server satrted successfully");
	}
	
	clilen =sizeof(cli_addr);
	connfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
	if(connfd <0)
	{
	error("error in accepting the request");
	}
	else
	{
	printf("request accepted successfully with connefd:%d\n", connfd);
	}


	cpid =fork();
	if(cpid==0)
	{
		while(1)
		{	bzero(&recvbuffer, sizeof(recvbuffer));
			readbytes = read(connfd, recvbuffer ,sizeof(recvbuffer));
			if(readbytes < 0)
			{
				error("No data is read from the server");
			}
			printf("msg recieved from client: %s\n", recvbuffer);
		}
	}
	else
	{
	while(1)
		{
			bzero(&sendbuffer, sizeof(sendbuffer));	
			char successmsg[200] ; //"cheers !!!, recieved the message from the client";
			printf("Enter Reply for client: ");
			int succesmsg_count=0;
			while((successmsg[succesmsg_count++]=getchar())!='\n');
			int writebytes;
			writebytes=write(connfd,successmsg,sizeof(successmsg));
			if (writebytes < 0)
			{
				error("error in writting the data");
			}
			
		}
	}
	close(sockfd);
}
