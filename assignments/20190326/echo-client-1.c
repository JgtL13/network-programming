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
   
   	WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
  
 
   	sd=socket(AF_INET, SOCK_DGRAM, 0);
   
   	serv.sin_family       = AF_INET; 
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(5678);
   	
   	serv_len = sizeof(serv);
 
	
   	for (i = 0; i < 64; i++)  //���B�����h�j�骺�ηN����ֵe����s�t�v 
   	{
   		clock_t t;
		t = clock();  //�Ұʭp�ɾ� 
   		for(j = 0; j < 16384; ++j)
		{
	   		n += sendto(sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len); //�ǰe
		}	
		t = clock() - t;  //�p��Ҫ�ɶ� 
	   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
	   	speed = 16384 / time_taken / 1024;  //�p��t�v 
	   	printf("Sending speed:%0.2f mbps\n", speed);
	   	if(i == 63)  //�Y�ǰe���A�^��end�������ݡA�i������ 
	   	{
	   		strcpy(str, "end");
	   		sendto(sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len);
		}
   	}
   	printf("Total sent : %d bits.\n", n);  //�L�X�`�@�e�X����ƶq 
   	
   	
	//����洫	
	serv_len = sizeof(serv);
	printf("Server waiting for Client\n");  		
	
	clock_t t;  
	t = clock();  //�Ұʭp�ɾ� 
		
	while(1)
	{
		
	   	m += recvfrom(sd, str_r, MAXLINE, 0, (LPSOCKADDR) &serv, &serv_len); //���� 
	   	if(strcmp(str_r, "end") == 0) //�Y�Q�i�������hbreak 
	   	{
	   		break;
		}	
		if(m % 16777216 == 0)  //�H16777216���@���i��B��A��ֵe����s�W�v 
		{
	    	t = clock() - t;  //�p��Ҫ᪺�ɶ� 
		   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
		   	speed = 16384 / time_taken / 1024;  //�p��t�v 
		   	printf("Receiving speed:%0.2f mbps\n", speed);
		   	t = clock();  //���]�p�ɾ� 
		}

	}
	printf("Total received : %d bits.\n", m); //�`�@��������ƶq 
	WSACleanup();
	system("pause");
   	return 0;
}


