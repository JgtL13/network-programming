#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024

int main(int argc, char** argv) {

   	SOCKET        	sd;
   	struct sockaddr_in serv;
   	char  		str[1024]="abcdefghijklmnopqrstuvwxyz";
   	char  		str_r[1024];
   	WSADATA 		wsadata;
   	int n;
   	unsigned long int bytes = 26;

   	WSAStartup(0x101,(LPWSADATA) &wsadata);

   	sd=socket(AF_INET, SOCK_STREAM, 0);

   	serv.sin_family       = AF_INET;
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(9);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

	clock_t t;  //�إ߭p�ɾ�
	t = clock();

	printf("Testing upload speed...(will take about 10 seconds)\n");
	int i = 1;
	while(i <= 3000000)  //�Q�ζ]�h���j��H�F�쩵�����ծɶ��ϱo���G�����T
	{
		send(sd, str, strlen(str)+1, 0);
		bytes += 26;
		++i;
	}

   	t = clock() - t;   //��X�Ҫ�ɶ�
    float time_taken = ((float)t)/CLOCKS_PER_SEC;  //�N�Ҫ�ɶ�������ର��
    printf("Upload speed : ");
	printf("%0.4f", bytes/time_taken/1000000);//�p���I����ĥ|�� �Q�θ�ƶq���H�Ҫ�O�ɶ���X�ǿ�t�� �åB�N����ରMB
	printf(" MB/s\n");


   	closesocket(sd);

   	WSACleanup();
   	system("pause");

   	return 0;
}


