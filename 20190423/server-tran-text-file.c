//client傳個檔123.txt到server
//v1：每秒送一個char
#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n,counter=1;
  	char  	str[MAXLINE], fName[1024];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
  	FILE *fptr1;

	while(1)//可連續收多個檔案 
	{
		printf("Enter destination file name : ");
		gets(fName); //讀取希望的目的地檔案名稱 
		fptr1=fopen(fName,"w");
		if(fptr1!=NULL)
		{
	
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
			
			cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
			
			while( 1 ) 
			{
			    n=recv(cli_sd, str, MAXLINE, 0); //收取字元 
			    if (n == 0)
				{
					puts("receive complete!!\n\n");
			    	break;
				}
				str[n]='\0';
			    printf("[%d] recv:%s  (size:%d) \n",counter,str,n);
				
				int i;
				for(i = 0; i < n; ++i) //一次將多個字元寫入檔案 
				{
					putc(str[i],fptr1);
				}
				sleep(1); //達成一次收多個字元  
			    counter++;
			}
		}
		fclose(fptr1);
		closesocket(cli_sd);
	   	closesocket(serv_sd);
	   	WSACleanup();
	}
   	system("pause");
   	return 0;
}
