#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n, temp = 50, round = 0, left = 1, right = 100;
  	char  	str[MAXLINE], str_r[MAXLINE], sResponse[MAXLINE], cResponse[MAXLINE], sGuess[MAXLINE];
	srand(time(NULL));
  	struct 	sockaddr_in   	serv, cli;
  	int min = 1;
  	int max = 100;
  	int answer = rand() % (max - min + 1) + min;
  	sprintf(sGuess, "%d", temp);
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   	
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定port


	while(1)//持續進行遊戲 
   	{
   		++round;
	    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
	   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態
		   	
		cli_len = sizeof(cli);
	 		
		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	   	n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收 
	   	printf("Round %d : ", round);
	   	printf("Client guessed %s, ",str_r);
	
		int input = atoi(str_r);//將str_r由string轉為int 方便之後計算 
		
		if(input == answer) //若答案正確 
	   	{
	   		strcpy(sResponse, "correct");
	   		printf("%s. ", sResponse);
	   		send(cli_sd, sResponse, strlen(sResponse) + 1, 0);
	   		break;
		}
		else if(input < answer) //若小於答案 
		{
			strcpy(sResponse, "too small");
			printf("%s. ", sResponse);
			send(cli_sd, sResponse, strlen(sResponse) + 1, 0);
		}
		else if(input > answer) //若大於答案 
		{
			strcpy(sResponse, "too large");
			printf("%s. ", sResponse);
			send(cli_sd, sResponse, strlen(sResponse) + 1, 0);
		}	
		
		printf("Server guesses %s.\n", sGuess);
		send(cli_sd, sGuess, strlen(sGuess) + 1, 0); //將server猜的數字回傳至client端 
		n=recv(cli_sd, cResponse, MAXLINE, 0); //接收client回傳的回覆 答案是否正確 
		if(strcmp(cResponse, "too large") == 0)
		{
			right = temp;
			temp = temp - ((temp - left) / 2); //二元搜尋法 
			sprintf(sGuess, "%d", temp);
		}
		else if(strcmp(cResponse, "too small") == 0)
		{
			left = temp;
			//printf("here2");
			temp = temp + ((right - temp) / 2); //二元搜尋法 
			sprintf(sGuess, "%d", temp);
		}
		else if(strcmp(cResponse, "correct") == 0) //若答案正確 停止遊戲 
		{
			break;
		}
	}
    
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
   	return 0;
}
