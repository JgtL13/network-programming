//server端(接收)
//client -> server 二位元檔

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */
#define MAX 50

int main()
{
	SOCKET	serv_sd, cli_sd, cli_sd2;        /* socket 描述子 */
  	int   	cli_len, n=1, bytes;
  	char  	str[MAXLINE];
  	char str_r[MAXLINE];
  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
    
	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket
   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定 IPPORT_ECHO 為 echo port
    	//bind(serv_sd, &serv, sizeof(serv)) ;
    	bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態
   	cli_len = sizeof(cli);

   	while (1) 
	{
   		printf("server: waiting for client\n");
   		cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //開啟client1的socket 
   		cli_sd2 = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //開啟client2的socket 
   		send(cli_sd, "ready", strlen("ready") + 1, 0); //告知client1可以進行傳送了 
        	while(1) 
		{
            		n=recv(cli_sd, str, MAXLINE, 0); //接收資料 
            		if (strcmp(str,"EOF") == 0) //檢查資料是否傳完 
            		{
            			send(cli_sd2, "EOF", strlen("EOF") + 1, 0); //傳給client2告知結束 
            			break; 
			}
            		memcpy(str_r, str, MAXLINE); //將收到的資料複製到另一個矩陣中 
            		send(cli_sd2, str_r, n, 0); //傳給client2 
        	}
		printf("recv EOF:%s\n" ,str);
		printf("recv complete!! \n");
	}
	
	//結束 WinSock DLL 的使用
	system("pause");
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	closesocket(cli_sd2);

   	WSACleanup();
   	return 0;
}
