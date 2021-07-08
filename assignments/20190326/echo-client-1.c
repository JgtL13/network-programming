#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

   	SOCKET sd;     
   	struct sockaddr_in serv;
   	char str[1024];
   	char str_r[1024];
   	float speed;
   	int n = 0, m = 0, i, j, serv_len, total = 0;
   	WSADATA wsadata;
   
   	memset(str,1,MAXLINE);
   
   	WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  
 
   	sd=socket(AF_INET, SOCK_DGRAM, 0);
   
   	serv.sin_family       = AF_INET; 
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(5678);
   	
   	serv_len = sizeof(serv);
 
	
   	for (i = 0; i < 64; i++)  //此處用雙層迴圈的用意為減少畫面更新速率 
   	{
   		clock_t t;
		t = clock();  //啟動計時器 
   		for(j = 0; j < 16384; ++j)
		{
	   		n += sendto(sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len); //傳送
		}	
		t = clock() - t;  //計算所花時間 
	   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
	   	speed = 16384 / time_taken / 1024;  //計算速率 
	   	printf("Sending speed:%0.2f mbps\n", speed);
	   	if(i == 63)  //若傳送完，回傳end給接收端，告知結束 
	   	{
	   		strcpy(str, "end");
	   		sendto(sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len);
		}
   	}
   	printf("Total sent : %d bits.\n", n);  //印出總共送出的資料量 
   	
   	
	//角色交換	
	serv_len = sizeof(serv);
	printf("Server waiting for Client\n");  		
	
	clock_t t;  
	t = clock();  //啟動計時器 
		
	while(1)
	{
		
	   	m += recvfrom(sd, str_r, MAXLINE, 0, (LPSOCKADDR) &serv, &serv_len); //接收 
	   	if(strcmp(str_r, "end") == 0) //若被告知結束則break 
	   	{
	   		break;
		}	
		if(m % 16777216 == 0)  //以16777216為一單位進行運算，減少畫面更新頻率 
		{
	    		t = clock() - t;  //計算所花的時間 
		   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
		   	speed = 16384 / time_taken / 1024;  //計算速率 
		   	printf("Receiving speed:%0.2f mbps\n", speed);
		   	t = clock();  //重設計時器 
		}

	}
	printf("Total received : %d bits.\n", m); //總共接收的資料量 
	WSACleanup();
	system("pause");
   	return 0;
}


