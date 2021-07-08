#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET serv_sd;        /* socket 描述子 */
  	int i, j, serv_len, n = 0, m = 0, total = 0;
  	char str[MAXLINE];
	char str_r[MAXLINE];
  	float speed;

  	struct sockaddr_in serv;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   	
  	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定port

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));   	
	    	
	serv_len = sizeof(serv);
	printf("Server waiting for Client\n");  		
	
	clock_t t;  
	t = clock();  //啟動計時器 
		
	while(1)
	{
	   	n += recvfrom(serv_sd, str_r, MAXLINE, 0, (LPSOCKADDR) &serv, &serv_len); //接收 
	   	if(strcmp(str_r, "end") == 0) //若被告知結束則break 
	   	{
	   		break;
		}
		if(n % 16777216 == 0)  //以16777216為一單位進行運算，減少畫面更新頻率  
		{
	    	t = clock() - t;  //計算所花的時間 
		   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
		   	speed = 16384 / time_taken / 1024;  //計算速率 
		   	printf("Receiving speed:%0.2f mbps\n", speed);
		   	t = clock();  //重設計時器 
		}	
	}
	printf("Total received : %d bits.\n", n);  //總共接收的資料量  
	
	
	//角色交換 
	memset(str,1,MAXLINE);   	
   	serv_len = sizeof(serv);
	
   	for (i = 0; i < 64; i++)  //此處用雙層迴圈的用意為減少畫面更新速率 
   	{
   		clock_t t;
		t = clock();  //啟動計時器 
   		for(j = 0; j < 16384; ++j)
		{
	   		m += sendto(serv_sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len); //傳送
		}	
		t = clock() - t;  //計算所花時間 
	   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
	   	speed = 16384 / time_taken / 1024;  //計算速率 
	   	printf("Sending speed:%0.2f mbps\n", speed);
	   	if(i == 63)  //若傳送完，回傳end給接收端，告知結束  
	   	{
	   		strcpy(str, "end");
	   		sendto(serv_sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len);
		}
   	}
   	printf("Total sent : %d bits.\n", m);  //印出總共送出的資料量  
   	WSACleanup();
   	system("pause");
   	return 0;
}
