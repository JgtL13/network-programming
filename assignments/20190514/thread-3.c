#include <stdio.h>      /* for printf(), fprintf() */
#include <winsock.h>    /* for socket(),... */
#include <stdlib.h>     /* for exit() */
#define MAXCLI 6

void *ThreadMain(void *arg);             /* Main program of a thread */
int clientNumber = 0;
int clients[MAXCLI] = {};
char logIn[100] = "A new client has been added.\n";
char reject[100] = "Chat room is currently full, please try again later.\n";

struct ThreadArgs /* Structure of arguments to pass to client thread */
{
    int clntSock;                      /* Socket descriptor for client */
};


int main(int argc, char *argv[])

{
	struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */
    DWORD  threadID;                 /* Thread ID from CreateThread() */

	int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    WSADATA wsaData;                 /* Structure for WinSock setup communication */
	struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
 	unsigned int clntLen;            /* Length of client address data structure */

	if (WSAStartup(0x101, &wsaData) != 0) /* Load Winsock 2.0 DLL */
    {
        printf("WSAStartup() failed");
        exit(1);
    }

	/* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("socket() failed");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(5678);              /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        printf("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, 3) < 0)
        printf("listen() failed");

    printf("Server is waiting for clients.\n");
    for (;;) /* Run forever */
    {
	    clntLen = sizeof(echoClntAddr);
	
	    /* Wait for a client to connect */
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
		    printf("accept() failed");
		
		/* Create separate memory for client argument */
		threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
		threadArgs -> clntSock = clntSock;
		
		if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, threadArgs, 0, (LPDWORD) &threadID) == NULL)
		    printf("thread_create() failed");
		
		clients[clientNumber] = clntSock; //將新加入的client之socket存入矩陣 
		++clientNumber;  //client數量加一 
		if(clientNumber == MAXCLI) //判斷人數是否已滿 
		{
		    send(clients[clientNumber - 1] , reject , strlen(reject)+1 , 0 ); //傳送斷線通知 
			closesocket(clients[clientNumber - 1]); //斷線 
			clients[clientNumber - 1] = 0;  
			--clientNumber;  //client數量減一 
			continue;
		}
		printf("New client with thread ID: %ld and socket:%d\n", threadID,clntSock);
		    
		int i;
		for(i = 0; i < clientNumber; ++i) //向所有在線的client發出有新client連入的通知 
		{
		    if(clients[i] != clntSock)
		    	send(clients[i], logIn, strlen(logIn)+1, 0);  
		        
		}
	}
}// end main



void *ThreadMain(void *threadArgs)
{
    int clntSock;                   /* Socket descriptor for client connection */
    /* Extract socket file descriptor from argument */
    clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;


	char echoBuffer[1000];        /* Buffer for echo string */
    int recvMsgSize = 1;                    /* Size of received message */
	
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {  	
        /* Receive message from client */
	    if ((recvMsgSize = recv(clntSock, echoBuffer, 1000, 0)) < 0)
    		printf("recv() failed");
        int i;
        for(i = 0; i < clientNumber; ++i) //將訊息傳送至所有在線的client 
        {
        	if(clients[i] == clntSock) //若迴圈對應到當前client自己的話則略過 
        		continue;
        	else
        	{
        		send(clients[i], echoBuffer, strlen(echoBuffer)+1, 0);
			}
		}
    }
    closesocket(clntSock);    /* Close client socket */    
    return (NULL);
}
