#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

   	SOCKET        	serv_sd, cli_sd, sd;     
   	struct sockaddr_in serv, cli;
   	char  		str[1024];
   	char  		str_r[1024];
   	float speed;
   	int n, m, i, j, cli_len, counter = 0;
   	WSADATA 		wsadata;
   
   	memset(str,1,MAXLINE);
   
   	WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  
 
   	sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.
   
   	serv.sin_family       = AF_INET; 
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(5678);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
	
   	for (i = 0; i < 64; i++)  //此處用雙層迴圈的用意為減少畫面更新速率 
   	{
   		clock_t t;
		t = clock();  //啟動計時器 
   		for(j = 0; j < 16384; ++j)
		{
	   		n = send(sd, str, MAXLINE, 0); //傳送
		}	
		t = clock() - t;  //計算所花時間 
	   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
	   	speed = 16384 / time_taken / 1024;  //計算速率 
	   	printf("Sending speed:%0.2f kbps\n", speed);
   	}
 
   	closesocket(sd); //關閉TCP socket
   	
   	
	//角色交換
	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   	
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定port

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    	
   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態	
	cli_len = sizeof(cli);
	printf("Client waiting for Server\n");  
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	
	clock_t t;
	t = clock();  //啟動計時器 
	
	while(1)
	{
		m=recv(cli_sd, str_r, MAXLINE, 0); //由server接收 
	   	++counter;  //計算接收了幾次，此動作是為了之後降低畫面的更新速率 
	    if(counter == 16384)
	    {
			counter = 0; 
			t = clock() - t;  //計算所花的時間 
			float time_taken = ((float)t) / CLOCKS_PER_SEC;
			speed = 16384 / time_taken / 1024;  //計算速率 
			printf("Receiving speed:%0.2f kbps\n", speed);
			t = clock();  //重設計時器
		}
		if(m == 0)	
			break;
			
	}
	
	closesocket(cli_sd);    
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	WSACleanup();  // 結束 WinSock DLL 的使用
   	system("pause");
   
   	return 0;
}


