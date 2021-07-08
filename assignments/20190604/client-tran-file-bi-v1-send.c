//client端(傳送)
//client -> server 二位元檔
#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

#define MAX 50

int main(int argc, char** argv) {

   	SOCKET        	sd;
   	struct sockaddr_in serv;
   	char  		str[1024];
   	char 		ready[1024];
   	char 		eof[1024] = "EOF";
   	WSADATA 		wsadata;
   	int n=0,bytes;
   	FILE *fptr1;
   	char ch;
   	fptr1=fopen("c:\\temp\\a.JPG","rb");
   	
   	if( fptr1!=NULL)
   	{
   	
	   	WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	   	sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.
	   	//為連線作準備，包含填寫 sockaddr_in 結構 (serv) 。
	   	//內容有：server 的 IP 位址，port number 等等。
	   	serv.sin_family       = AF_INET;
	   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
	   	serv.sin_port         = htons(5678);
	   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
	   	
		recv(sd, ready, MAXLINE, 0); //接收所有client都連入的通知 
	
		if(strcmp(ready, "ready") == 0)
		{
			while (!feof(fptr1))
			{
	    		bytes=fread(str,sizeof(char),MAX,fptr1); //讀取圖片的資料 
	    		send(sd, str, bytes, 0);
			}
	   		sleep(1);
	   		send(sd, eof, strlen(eof)+1, 0); //傳送EOF至server
	  	 	printf("send :%s\n",eof);
	   		printf("sent complete!!\n");
	  	}//end if
	   	system("pause");
	   	closesocket(sd); //關閉TCP socket
	   	WSACleanup();  // 結束 WinSock DLL 的使用
	   	fclose(fptr1);
	   return 0;
	}
}


