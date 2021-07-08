#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MAXCLI 5
#define MAXLINE 1024

typedef unsigned int bool;
#define false 0
#define true 1

void *ThreadMain(void *arg);
int broadcast_sd;
struct sockaddr_in bc;
int clients[MAXCLI] = {0};
int i, j, n, bc_len, timer = 60, clientNumber = 0; 
int answer[4];
char reject[100] = "Server is currently full, please try again later.\n";
char rules[MAXLINE] = "By guessing a 4 non repeative digit code, you will get a response telling you how your guess was.\nFor each A is a number that is the correct number and the correct position.\nFor each B is a number that is correct but in the wrong position.\nChallenge your friends and see who gets the correct answer first!\n\n";
char leaveGame[MAXLINE];
char gameOver[100];
char userName[MAXLINE];
char str_bc[MAXLINE];
char respond[MAXLINE];
char startMenu[MAXLINE];
char timeLeft[MAXLINE];

struct ThreadArgs
{
    int clntSock;
};

/*thread for game start countdown*/
void *countdown(void *argu)
{
    while(1)
    {
    	for(i = 0; i < MAXCLI; ++i)
    	{
    		if(clients[i] != 0)
    		{
    			bc.sin_port = htons(i + 0103);
    			snprintf(startMenu, sizeof(startMenu), "You are player #%d.\n\n", i + 1);
    			strcat(startMenu, rules);
    			strcat(startMenu, "Players online :\n");
    			for(j = 0; j < MAXCLI; ++j)
    			{
    				if(clients[j] != 0)
    				{
    					snprintf(userName, sizeof(userName), "Player #%d\n", j + 1);
    					strcat(startMenu, userName);
					}
				}
    			snprintf(timeLeft, sizeof(timeLeft), "\nTime until game starts : %d second(s)\n", timer);
    			strcat(startMenu, timeLeft);
    			sendto(broadcast_sd, startMenu, strlen(startMenu), 0, (LPSOCKADDR)&bc, sizeof(bc));
			}
		}
		--timer;
		sleep(1);
		if(timer == -1)
		{
			for(i = 0; i < MAXCLI; ++i)
			{
				bc.sin_port = htons(i + 0103);
				sendto(broadcast_sd, "start", strlen("start"), 0, (LPSOCKADDR)&bc, sizeof(bc));
			}			
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	struct ThreadArgs *threadArgs;
    DWORD  threadID;
	int servSock;
    int clntSock;
    WSADATA wsaData;
	struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
 	unsigned int clntLen;
 	pthread_t thread;
 	
	/*�]�w����*/
	srand(time(NULL));//�]�w�|�Ӥ����ƼƦr������ 
	i = 0;
	while(i < 4)
	{
		bool valid = true;
		answer[i] = rand() % 10;
		for(j = 0; j < i; ++j)
		{
			if(answer[j] == answer[i])
			{
				valid = false;
				break;
			}
		}
		if(j == i && valid == true)
		{
			++i;
		}
	}
	/*�]�w����*/
	//printf("%d%d%d%d\n", answer[0], answer[1], answer[2], answer[3]);
	
	
	/*WSA Startup*/
	if (WSAStartup(0x101, &wsaData) != 0)
    {
        printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
        exit(1);
    }
    /*WSA Startup*/
    
    
    /*�]�wtcp�ǿ�Ϊ�socket*/
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
    	printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
	}
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(5678);
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    {
        printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
    }
    /*�]�wtcp�ǿ�Ϊ�socket*/
	
	
	/*�]�w�s��udp�ǿ�Ϊ�socket*/
	if((broadcast_sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)// �}�� UDP socket
	{
		printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
	}
   	char broadcast = 'a';
	setsockopt(broadcast_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
	bc.sin_family      = AF_INET;
   	bc.sin_addr.s_addr = inet_addr("255.255.255.255");
   	bc.sin_port        = htons(0103);
   	bc_len = sizeof(bc);
   	/*�]�w�s��udp�ǿ�Ϊ�socket*/


    if (listen(servSock, 3) < 0)
        printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
    printf("Waiting for players.\n");
    pthread_create(&thread, NULL, &countdown, NULL);
    
    for (;;)
    {  	
    	/*�Nthreadmain�[�J�s�[�J��client��*/
	    clntLen = sizeof(echoClntAddr);
		if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
		{
		    printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
		}
		threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
		threadArgs -> clntSock = clntSock;
		if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, threadArgs, 0, (LPDWORD) &threadID) == NULL)
		{
		    printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
		}
		/*�Nthreadmain�[�J�s�[�J��client��*/
		
		
		/*�s�[�J���ϥΪ̥[�Jclients[]�x�}��*/
		for(i = 0; i < MAXCLI; i++)
		{
			if(clients[i] == 0)
			{
				clients[i] = clntSock;
				++clientNumber;
				if(clientNumber == MAXCLI) //�P�_��e�[�J���ϥΪ̬O�_�W�X�W��
				{
					send(clients[i] , reject , strlen(reject)+1 , 0); //�ǰe�_�u�q�� 
					clients[i] = 0;  
					--clientNumber;
					break;
				}
				else
				{
					printf("Player #%d is in the game with socket %d.\n", i + 1, clients[i]);
					break;
				}
			}
		}
		/*�s�[�J���ϥΪ̥[�Jclients[]�x�}��*/
	}
}

/*�D�n�Ψӱ����T����threadmain*/
void *ThreadMain(void *threadArgs)
{
    int clntSock;
    char echoBuffer[1000];
    int recvMsgSize = 1;
    
    clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
	
	//printf("%d%d%d%d\n", answer[0], answer[1], answer[2], answer[3]);
	
	/*�Y������T���n�i�檺�ʧ@*/
    while (recvMsgSize > 0) 
    {  	
    	/*�����T��*/
    	recvMsgSize = recv(clntSock, echoBuffer, 1000, 0);
    	/*�����T��*/
    	
    	
    	/*�T�����e�P�_*/ 
    	if(recvMsgSize == SOCKET_ERROR) //�X�{���~ 
		{
			int error_code = WSAGetLastError();
			if(error_code == WSAECONNRESET) //�Y���~���L�wĵ�_�u 
			{
				for(i = 0; i < MAXCLI; ++i)
				{
					
					if(clients[i] == clntSock)
					{	
						snprintf(leaveGame, sizeof(leaveGame), "Player #%d left the game.\n", i + 1);
						printf("Player #%d disconnected unexpectedly\n", i + 1);
						for(j = 0; j < MAXCLI; ++j) //�i���j�a���a�w�_�u 
						{
							if(clients[j] != 0 && clients[j] != clntSock)
							{
								send(clients[j], leaveGame, strlen(leaveGame) + 1, 0);
							}
						}
						clients[i] = 0;
						--clientNumber;
						break;
					}
				}
			}
			else
			{
				printf("Oops! Something went wrong, please start again or there might be some malfunctions.\n");
			}
			continue;						
		}	
		else //�i��AB���p�� 
		{
			printf("from %d : %s\n", clntSock, echoBuffer);
			for(i = 0; i < MAXCLI; ++i)
	    	{
	    		echoBuffer[i] -= '0';
			}
			int A = 0, B = 0;
			for(i = 0; i < MAXCLI; ++i)
			{
				for(j = 0; j < MAXCLI; ++j)
				{
					if(echoBuffer[i] == answer[j])
					{
						if(i == j)
						{
							++A;
						}
						else
						{
							++B;
						}
					}
				}
			}
			snprintf(respond, sizeof(respond), "Result: %dA%dB", A, B); 
			send(clntSock, respond, strlen(respond)+1, 0); //�N�P�_���G�Ǧ^��client   
			
			if(A == 4) //�Y���H�q�ﵪ�׭n�����C�� 
			{
				for(i = 0; i < MAXCLI; ++i)
				{
					if(clients[i] == clntSock)
					{
						snprintf(gameOver, sizeof(gameOver), " Player #%d won!", i + 1);
					}
				}
				for(i = 0; i <= MAXCLI; ++i)
				{
					if(clients[i] != clntSock)
					{
						bc.sin_port = htons(i + 0103);
						sendto(broadcast_sd, "Game over!", strlen("Game over!"), 0, (LPSOCKADDR)&bc, sizeof(bc));
						sendto(broadcast_sd, gameOver, strlen(gameOver), 0, (LPSOCKADDR)&bc, sizeof(bc));
					}	
				}
				exit(1);
			}
			A = 0;
			B = 0;
		}
		/*�T�����e�P�_*/ 
    }
    /*�Y������T���n�i�檺�ʧ@*/
    closesocket(clntSock);
    return (NULL);
}
/*�D�n�Ψӱ����T����threadmain*/
