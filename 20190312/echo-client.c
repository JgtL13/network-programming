#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

   	SOCKET        	sd;     
   	struct sockaddr_in serv;
   	char  		str[1024], str_r[1024], response[MAXLINE], sGuess[MAXLINE]/*, trash[MAXLINE]*/;
   	WSADATA 		wsadata;
   	int n, m, myAnswer, round = 0;
   	char trash;

	printf("Enter your answer for the server to guess : ");
	scanf("%d", &myAnswer); //輸入要給server猜的答案 
	while(1)
	{
		++round;
   		WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  
   		sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   		serv.sin_family       = AF_INET; 
   		serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   		serv.sin_port         = htons(5678);
   		
		printf("Round %d : Guess the answer : ", round);
		scanf("%s", &str); //自己猜的server的答案 
	   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
	
	   	send(sd, str, strlen(str)+1, 0); //傳送答案給server 
	   
	   	n = recv(sd, str_r, MAXLINE, 0); //server回傳的回覆 答案是否正確 
		m = recv(sd, sGuess, MAXLINE, 0); //接收 server猜你的答案 
	   	printf("Server says %s. Server guessed %s. Your response : ", str_r, sGuess);
	   	if(strcmp(str_r, "correct") == 0) //若正確 停止遊戲 
	   	{
	   		break;
		}
	   	scanf("%c", &trash); //防止gets抓取前面的空格 
		gets(response); //讀取你給server的回覆 
		send(sd, response, strlen(response)+1, 0); //傳送你的回覆給server 
		if(strcmp(response, "correct") == 0) //若正確 停止遊戲 
		{ 
			break;
		} 
	}
	  
	closesocket(sd); //關閉TCP socket    
	WSACleanup();  // 結束 WinSock DLL 的使用
   	system("pause");
   	return 0;
}


