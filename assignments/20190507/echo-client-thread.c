#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <winsock.h>

#define MAXLINE 1024

SOCKET        	sd;
struct sockaddr_in serv;
char  		str[1024];
char  		str_r[1024];
char 		reject[1024] = "This room is currently full, please try again later.\n";
WSADATA 		wsadata;
int timeout = 50,n;

void *recvMess(void *argu) {
    while (1) {
        setsockopt(sd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
		n=recv(sd, str_r, MAXLINE, 0); 
		if(strcmp(str_r, reject) == 0) //判斷收到的訊息是否為人數已滿的訊息 
		{
			printf("%s\n", reject); //告知使用者人數已滿 
			closesocket(sd); //斷線 
		   	WSACleanup();
		   	system("pause");
		}
		if(n!=-1)
            printf("recv: %s (%d bytes)\n",str_r,strlen(str_r)+1);
    }
}

int main(int argc, char** argv) {
   int n,i,j,total=0;
    pthread_t thread1;

   WSAStartup(0x101,(LPWSADATA) &wsadata);


   sd=socket(AF_INET, SOCK_STREAM, 0);

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv));


    pthread_create(&thread1, NULL, &recvMess, NULL);
    
	while(1){
		gets(str);
		send(sd, str, strlen(str)+1, 0);
	}

   closesocket(sd);

   WSACleanup();
   system("pause");

   return 0;
}

