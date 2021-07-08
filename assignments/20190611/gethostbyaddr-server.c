#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE];
  	struct 	sockaddr_in  serv, cli;
  	struct in_addr sAddr;
  	char serv_name[100] = "echo";
  	WSADATA wsadata;
  	LPHOSTENT hp;
  	LPSERVENT sp;
  	LPPROTOENT pp;
	
	   	
	   	
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
	cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //建立連線 

	//查IP
	n = recv(cli_sd, str_r, MAXLINE, 0);//讀取來自client的內容 
	sAddr.s_addr = inet_addr(str_r);
	hp = gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);
	snprintf(str, sizeof(str), "host name:%s\n", hp->h_name);//將結果放入str 
	send(cli_sd, str, strlen(str)+1, 0);//將結果傳送給client 
	
	//查主機名稱
	n = recv(cli_sd, str_r, MAXLINE, 0);//讀取來自client的內容 
	hp = gethostbyname(str_r);
	snprintf(str, sizeof(str), "host IP:%s\n", inet_ntoa(*(LPIN_ADDR)(hp->h_addr)));//將結果放入str 
	send(cli_sd, str, strlen(str)+1, 0);//將結果傳送給client 
	
	//查service的port
	n = recv(cli_sd, str_r, MAXLINE, 0);//讀取來自client的內容 
	char proto[100] = "tcp";
	sp = getservbyname(str_r, proto);
	snprintf(str, sizeof(str), "port:%d\n", ntohs(sp -> s_port));//將結果放入str 
	send(cli_sd, str, strlen(str)+1, 0);//將結果傳送給client 
	
	//在特定port的service
	n = recv(cli_sd, str_r, MAXLINE, 0);//讀取來自client的內容 
	int port = atoi(str_r);
	port = (int)str_r;
	char proto1[100] = "tcp";
	sp = getservbyport(htons((unsigned short)str_r), proto1);
	snprintf(str, sizeof(str), "Serve name:%s\n", (LPSTR) serv_name);//將結果放入str 
	send(cli_sd, str, strlen(str)+1, 0);//將結果傳送給client 
	
	//查protocol的編號
	n = recv(cli_sd, str_r, MAXLINE, 0);//讀取來自client的內容 
	pp = getprotobyname(str_r);
	snprintf(str, sizeof(str), "number:%d\n", pp -> p_proto);//將結果放入str 
	send(cli_sd, str, strlen(str)+1, 0);//將結果傳送給client 
	
	//查在特定編號的protocol
	n = recv(cli_sd, str_r, MAXLINE, 0);//讀取來自client的內容 
	int number = atoi(str_r);
	pp = getprotobynumber(number);
	snprintf(str, sizeof(str), "protocol name:%s\n", pp -> p_name);//將結果放入str 
	send(cli_sd, str, strlen(str)+1, 0);//將結果傳送給client 
	
	
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
}
