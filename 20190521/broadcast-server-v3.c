// broadcast multi-thread server
// each channel has its port number

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 20    /* 字串緩衝區長度 */

typedef unsigned int bool;
#define false 0
#define true 1

void main()
{
	SOCKET	serv_sd;        /* socket 描述子 */
  	int   	cli_len, n,i=1, BROADCAST = 8813, temp;
  	char  	str[MAXLINE], changePort[MAXLINE], buffer[MAXLINE];
  	bool change = false;

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// 開啟 UDP socket
   	char broadcast = 'a';
	setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));   	
   	cli_len = sizeof(cli);
   	printf("server will broadcast.\n");
   	             
   	
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("255.255.255.255");
   	cli.sin_port        = htons(BROADCAST);
   		
	while(1)
	{
		if(i % 7 == 0) //模擬port已被使用時，要求使用者更改port 
		{
			change = true;
			printf("This port is now occupied, please enter a port number to change to: ");
			scanf("%d", &temp);
			itoa(temp, buffer, 10);
		}
		
		
		cli.sin_port = htons(BROADCAST);	
		if(change == true) //將使用者輸入的port number傳給client，讓client可以依照這個port number重新bind 
		{
			memset(str, "\0", sizeof(str));
			strcpy(changePort, buffer);
			sendto(serv_sd, changePort, strlen(changePort), 0,(LPSOCKADDR)&cli,cli_len); 	
		}
		else
		{
			memset(str, i%10 +'0', sizeof(str));
			sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
	        printf("server broadcast: %s\n",str);
		}	
        
        
        cli.sin_port        = htons(BROADCAST+1);
        if(change == true) //將使用者輸入的port number傳給client，讓client可以依照這個port number重新bind 
		{
			memset(str, "\0", sizeof(str));
			strcpy(changePort, buffer);
			sendto(serv_sd, changePort, strlen(changePort), 0,(LPSOCKADDR)&cli,cli_len); 	
		}
		else
		{
			memset(str, (i-1)%26 +'a', sizeof(str));
			sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
	        printf("server broadcast: %s\n",str);
		}	      
        
        
        cli.sin_port        = htons(BROADCAST+2);
        if(change == true) //將使用者輸入的port number傳給client，讓client可以依照這個port number重新bind 
		{
			memset(str, "\0", sizeof(str));
			strcpy(changePort, buffer);
			sendto(serv_sd, changePort, strlen(changePort), 0,(LPSOCKADDR)&cli,cli_len);
			BROADCAST = temp; //最後更改server自己的port number 
			change = false;	
		}
		else
		{
			memset(str, (i-1)%26 +'A', sizeof(str));
			sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
	        	printf("server broadcast: %s\n",str);
	        	sleep(1);
		}
		i++;	
    }
        
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
