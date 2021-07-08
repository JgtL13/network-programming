#include <stdio.h>
#include <string.h>
#include <time.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {

	SOCKET        	sd;
	struct sockaddr_in serv;
	char  		str[1024]="abc";
	char  		str_r[1024];
	WSADATA 		wsadata;
	unsigned long int n = 0;

	WSAStartup(0x101,(LPWSADATA) &wsadata);

	sd=socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family       = AF_INET;
	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
	serv.sin_port         = htons(19);

	connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

	clock_t t; //建立計時器
	t = clock();

   	printf("Testing download speed...(will take about 10 seconds)\n");
   	int i = 1;
   	while(i <= 5000000) //利用跑多次迴圈以達到延長測試時間使得結果較正確
   	{
   		n+=recv(sd, str_r, MAXLINE, 0);
		++i;
	}

  	t = clock() - t; //算出所花時間
    float time_taken = ((float)t)/CLOCKS_PER_SEC; //將所花時間的單位轉為秒
    printf("");
   	printf("Download speed : ");
	printf("%0.4f", n/time_taken/1000000); //小數點取到第四位 利用資料量除以所花費時間算出傳輸速度 並且將單位轉為MB
	printf(" MB/s\n");

   	closesocket(sd);

   	WSACleanup();
   	system("pause");
	return 0;
}
