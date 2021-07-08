#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd1, cli_sd2, cli_sd3;        /* socket 描述子 */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE];
  	struct 	sockaddr_in  serv, cli;
  	WSADATA wsadata;
	   	
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(1234);	// 指定port
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));	
   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態
   	struct sockaddr_in tAddr; 
   	int lentAddr;
   	lentAddr = sizeof(tAddr);
   	cli_len = sizeof(cli);
   	
   	//等待client1 
	printf("server waits for client 1.\n");  		
	cli_sd1=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //建立連線 
	printf("connection succesful.\n");
	getpeername(cli_sd1, (LPSOCKADDR) &tAddr, &lentAddr);  //獲取peer name 
	printf("Client 1' IP: %s, port: %d\n", inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port)); //輸出peer的IP位置及port number 
	
	//等待client2
	printf("server waits for client 2.\n");  		
	cli_sd2=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);//建立連線  
	printf("connection succesful.\n");
	getpeername(cli_sd2, (LPSOCKADDR) &tAddr, &lentAddr);//獲取peer name
	printf("Client 2' IP: %s, port: %d\n", inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));//輸出peer的IP位置及port number 
	
	//等待client3 
	printf("server waits for client 3.\n");  		
	cli_sd3=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //建立連線 
	printf("connection succesful.\n");
	getpeername(cli_sd3, (LPSOCKADDR) &tAddr, &lentAddr);//獲取peer name
	printf("Client 3' IP: %s, port: %d\n", inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));//輸出peer的IP位置及port number 

	while(1)
	{
		n = recv(cli_sd1, str_r, MAXLINE, 0);//讀取來自client1的內容 
    	printf("server recv from client1: %s (%d bytes)\n",str_r,n); 
    	strcpy(str, str_r);
		send(cli_sd2, str, strlen(str)+1, 0);//傳送至client2 
		send(cli_sd3, str, strlen(str)+1, 0);//傳送至client3
    	printf("server sends to client2: %s (%d bytes)\n", str, strlen(str) + 1);
    	printf("server sends to client3: %s (%d bytes)\n", str, strlen(str) + 1);
    	
    	n = recv(cli_sd2, str_r, MAXLINE, 0);//讀取來自client2的內容 
    	printf("server recv from client2: %s (%d bytes)\n",str_r,n); 
    	strcpy(str, str_r);
		send(cli_sd1, str, strlen(str)+1, 0);//傳送至client1
		send(cli_sd3, str, strlen(str)+1, 0);//傳送至client3
    	printf("server sends to client1: %s (%d bytes)\n", str, strlen(str) + 1);
    	printf("server sends to client3: %s (%d bytes)\n", str, strlen(str) + 1);
    	
    	n = recv(cli_sd3, str_r, MAXLINE, 0);//讀取來自client3的內容 
    	printf("server recv from client3: %s (%d bytes)\n",str_r,n); 
    	strcpy(str, str_r);
		send(cli_sd1, str, strlen(str)+1, 0);//傳送至client1
		send(cli_sd2, str, strlen(str)+1, 0);//傳送至client2
    	printf("server sends to client1: %s (%d bytes)\n", str, strlen(str) + 1);
    	printf("server sends to client2: %s (%d bytes)\n", str, strlen(str) + 1);
	}
    
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	closesocket(cli_sd1);
   	closesocket(cli_sd2);
   	WSACleanup();
   	system("pause");
}

