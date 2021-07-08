#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd[10], new_sd;        /* socket 描述子 */
  	int   	cli_len, n, i, j, x, num_client;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   	
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定 IPPORT_ECHO 為 echo port

    	bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    	
   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態
   	
   	cli_len = sizeof(cli);
	
	printf("server: waiting for client\n");
	
	cli_sd[0] = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	num_client = 1;
	u_long iMode = 1;
	ioctlsocket(serv_sd, FIONBIO, &iMode);
	ioctlsocket(cli_sd[0], FIONBIO, &iMode);
	
   	while (1) 
	{
   		if((new_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len)) != -1) //接受新的client 
   		{
   			printf("server gets a new client connection.(%d)\n", num_client + 1);
			cli_sd[num_client] = new_sd; //將新的client加入陣列中 
			ioctlsocket(cli_sd[num_client], FIONBIO, &iMode);
			num_client++; //client總數量增加 
		}
       		
		for (i = 0; i < num_client; ++i)
		{       		
	        	n=recv(cli_sd[i], str, MAXLINE, 0);
			if (n > 0 )
			{
				printf("cli[%d] recv and send: %s\n", i + 1, str);    	// 顯示從 client 傳來的字串
				send(cli_sd[i], str, strlen(str)+1, 0);  //echo 
	        	}
			int nError=WSAGetLastError();
			if(nError!=WSAEWOULDBLOCK && nError!=0)
			{
				printf("cli[%d] disconnected!\n", i + 1);
				--num_client; //若有client斷線則減少client總數量 
				closesocket(cli_sd[i]); //關閉斷線的client 
				for(j = i; j < num_client; ++j)
				{
					printf("client %d is now renamed as client %d\n", j + 2, j + 1);
					cli_sd[j] = cli_sd[j + 1];	//將斷線的client之後的client往前遞補 
				}
			}
        	} 
    	}
 
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	WSACleanup();
}
