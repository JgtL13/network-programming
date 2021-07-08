// broadcast multi-thread client
// each channel has its port number


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <winsock.h>

#define MAXLINE 1024

SOCKET        	sd;
struct sockaddr_in serv,cli;
char  		str[1024];
char  		str_r[1024];
char broadcast;
WSADATA 		wsadata;
int timeout = 50,n,serv_len,cli_len,channel=1, BROADCAST = 8813, changePort;


void *recvMess(void *argu) {
    while (1)
	{
        cli_len= sizeof(cli); 
		memset(str, "\0", sizeof(str));     
		n=recvfrom(sd, str, MAXLINE, 0,(LPSOCKADDR) &cli,&cli_len ); //由echo server接收 
		if (n > 0 && n == 20) 
		{
			printf("client(from:%s):%s,%d\n",inet_ntoa(cli.sin_addr),str,n);  
		}
		if(n != 20) //若接收到非平常傳的20個數字或字母(也就是接收到port的號碼) 
		{
			changePort = atoi(str);
			BROADCAST = changePort; //將新的port number assign 給 BROADCAST 
			closesocket(sd); //利用新的BROADCAST重新bind 
			sd=socket(AF_INET, SOCK_DGRAM, 0);
    		broadcast = 'a';
    		if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
				printf("setsockopt() broadcast error!\n");
		   			
			serv.sin_family       = AF_INET;
    		serv.sin_addr.s_addr  = 0;
			serv.sin_port  = htons(BROADCAST);
					
    		if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) < 0 )    				
   				printf("bind error!(%d)\n", WSAGetLastError ());    
		}
    }
}

int main(void) {
	
    int n,i,j,total=0;
    pthread_t thread1;

    WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用


    sd=socket(AF_INET, SOCK_DGRAM, 0);
    broadcast = 'a';
    if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		printf("setsockopt() broadcast error!\n");
	
    serv.sin_family       = AF_INET;
    serv.sin_addr.s_addr  = 0;   
    serv.sin_port         = htons(BROADCAST);
    if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) < 0 )
   		printf("bind error!\n");
   	
    serv_len=sizeof(serv);

    pthread_create(&thread1, NULL, &recvMess, NULL);
    

	while(1)
	{
		scanf("%d",&channel);
		printf("switch to channel %d\n\n",channel);
		switch(channel)
		{
			case 1:
				closesocket(sd);
			    sd=socket(AF_INET, SOCK_DGRAM, 0);
    			broadcast = 'a';
    			if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   			printf("setsockopt() broadcast error!\n");
		   			
		       	serv.sin_family       = AF_INET;
    			serv.sin_addr.s_addr  = 0;
				serv.sin_port  = htons(BROADCAST);
					
    			if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) < 0 )    				
   					printf("bind error!(%d)\n", WSAGetLastError ());      
		   	   	break;
			case 2:
				closesocket(sd);
			    sd=socket(AF_INET, SOCK_DGRAM, 0);
    			broadcast = 'a';
    			if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   			printf("setsockopt() broadcast error!\n");
		   			
		       	serv.sin_family       = AF_INET;
    			serv.sin_addr.s_addr  = 0;
				serv.sin_port  = htons(BROADCAST+1);
    			if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) < 0 )
   					printf("bind error!\n");
  		   	   	break;
			case 3:
				closesocket(sd);
			    sd=socket(AF_INET, SOCK_DGRAM, 0);
			        
    			broadcast = 'a';
    			if(setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   			printf("setsockopt() broadcast error!\n");
		   			
		       	serv.sin_family       = AF_INET;
    			serv.sin_addr.s_addr  = 0;
				serv.sin_port  = htons(BROADCAST+2);
    			if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) < 0 )
   					printf("bind error!\n");    
		   	   	break;
		}
	}

   	closesocket(sd); //關閉TCP socket

   	WSACleanup();  // 結束 WinSock DLL 的使用
   	system("pause");

   	return 0;
}
