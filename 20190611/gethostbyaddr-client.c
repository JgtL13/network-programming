#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) 
{  

   	SOCKET        	sd;     
   	struct sockaddr_in serv;
   	char  		str[1024];
   	char  		str_r[1024];;
   	WSADATA 		wsadata;
   	int n = 1;

   	WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   	sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.
   	serv.sin_family       = AF_INET; 
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(1234);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   	
   	//查IP
   	printf("查IP: ");
   	gets(str);//接受輸入
	send(sd, str, strlen(str)+1, 0);//送至server 
   	n = recv(sd, str_r, MAXLINE, 0);//接收來自server的回覆 
   	printf("%s\n\n", str_r);
   	
   	//查主機名稱
   	printf("查主機名稱: ");
	gets(str);//接受輸入
	send(sd, str, strlen(str)+1, 0);//送至server 
   	n = recv(sd, str_r, MAXLINE, 0);//接收來自server的回覆 
   	printf("%s\n\n", str_r);
   	
   	//查service的port
   	printf("查service的port: ");
	gets(str);//接受輸入
	send(sd, str, strlen(str)+1, 0);//送至server 
   	n = recv(sd, str_r, MAXLINE, 0);//接收來自server的回覆 
   	printf("%s\n\n", str_r);
   	
   	//在特定port的service
   	printf("查在特定port的service: ");
	gets(str);//接受輸入
	send(sd, str, strlen(str)+1, 0);//送至server 
   	n = recv(sd, str_r, MAXLINE, 0);//接收來自server的回覆 
   	printf("%s\n\n", str_r);
   	
   	//查protocol的編號
   	printf("查protocol的編號: ");
	gets(str);//接受輸入
	send(sd, str, strlen(str)+1, 0);//送至server 
   	n = recv(sd, str_r, MAXLINE, 0);//接收來自server的回覆 
   	printf("%s\n\n", str_r);
   	
   	//查在特定編號的protocol
   	printf("查在特定編號的protocol: ");
	gets(str);//接受輸入
	send(sd, str, strlen(str)+1, 0);//送至server 
   	n = recv(sd, str_r, MAXLINE, 0);//接收來自server的回覆 
   	printf("%s\n\n", str_r);
   		
  
   	closesocket(sd); //關閉TCP socket
   	WSACleanup();  // 結束 WinSock DLL 的使用
   	system("pause");
   
   	return 0;
}


