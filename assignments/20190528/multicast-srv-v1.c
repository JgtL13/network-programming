#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 15    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, serv_brod_sd;        /* socket 描述子 */
  	int   	cli_len, brod_len, n,i=1;
  	char  	str[MAXLINE];
  	char    bc[200] = "群組IP : 224.1.1.1~224.1.1.3\n群組PORT : 8813\n\n頻道1 : 頻道1介紹(請按1選擇收看，按a選擇停止收看)\n頻道2 : 頻道2介紹(請按2選擇收看，按b選擇停止收看)\n頻道3 : 頻道3介紹(請按3選擇收看，按c選擇停止收看)\n";  //節目單 

  	struct 	sockaddr_in   	serv, cli, brod;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// 開啟 UDP socket
   	serv_brod_sd = socket(AF_INET, SOCK_DGRAM, 0);
   	
   	//用來廣播的設定
   	char broadcast = 'a';
	setsockopt(serv_brod_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
	brod.sin_family      = AF_INET;
   	brod.sin_addr.s_addr = inet_addr("255.255.255.255");
   	brod.sin_port        = htons(0103);

   	    /* Set TTL of multicast packet */
   	int multicastTTL=1;
    if (setsockopt(serv_sd, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &multicastTTL, 
          sizeof(multicastTTL)) == SOCKET_ERROR)
    printf("setsockopt() failed");
   	
   	
   	cli_len = sizeof(cli);
   	brod_len= sizeof(brod);
   	
   	
   	printf("server will multicastcast.\n");
   	               
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("224.1.1.1");
   	cli.sin_port        = htons(8813);
   		
while(1){	
	
		sendto(serv_brod_sd, bc, strlen(bc), 0,(LPSOCKADDR)&brod,brod_len);  //廣播節目選單 
		
		cli.sin_addr.s_addr = inet_addr("224.1.1.1"); //頻道1 
		memset(str, i%10 +'0', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %s\n",str);		// 顯示送去client 的字串	
        
        cli.sin_addr.s_addr = inet_addr("224.1.1.2"); //頻道2 
        memset(str, (i - 1) % 26 +'a', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %s\n",str);		// 顯示送去client 的字串	
        
        cli.sin_addr.s_addr = inet_addr("224.1.1.3"); //頻道3 
        memset(str, (i - 1) % 26 +'A', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %s\n",str);		// 顯示送去client 的字串
			
        sleep(1);
        i++;
    }
        
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
