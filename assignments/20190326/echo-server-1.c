#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET serv_sd;        /* socket �y�z�l */
  	int i, j, serv_len, n = 0, m = 0, total = 0;
  	char str[MAXLINE];
	char str_r[MAXLINE];
  	float speed;

  	struct sockaddr_in serv;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
   	
  	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));   	
	    	
	serv_len = sizeof(serv);
	printf("Server waiting for Client\n");  		
	
	clock_t t;  
	t = clock();  //�Ұʭp�ɾ� 
		
	while(1)
	{
	   	n += recvfrom(serv_sd, str_r, MAXLINE, 0, (LPSOCKADDR) &serv, &serv_len); //���� 
	   	if(strcmp(str_r, "end") == 0) //�Y�Q�i�������hbreak 
	   	{
	   		break;
		}
		if(n % 16777216 == 0)  //�H16777216���@���i��B��A��ֵe����s�W�v  
		{
	    	t = clock() - t;  //�p��Ҫ᪺�ɶ� 
		   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
		   	speed = 16384 / time_taken / 1024;  //�p��t�v 
		   	printf("Receiving speed:%0.2f mbps\n", speed);
		   	t = clock();  //���]�p�ɾ� 
		}	
	}
	printf("Total received : %d bits.\n", n);  //�`�@��������ƶq  
	
	
	//����洫 
	memset(str,1,MAXLINE);   	
   	serv_len = sizeof(serv);
	
   	for (i = 0; i < 64; i++)  //���B�����h�j�骺�ηN����ֵe����s�t�v 
   	{
   		clock_t t;
		t = clock();  //�Ұʭp�ɾ� 
   		for(j = 0; j < 16384; ++j)
		{
	   		m += sendto(serv_sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len); //�ǰe
		}	
		t = clock() - t;  //�p��Ҫ�ɶ� 
	   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
	   	speed = 16384 / time_taken / 1024;  //�p��t�v 
	   	printf("Sending speed:%0.2f mbps\n", speed);
	   	if(i == 63)  //�Y�ǰe���A�^��end�������ݡA�i������  
	   	{
	   		strcpy(str, "end");
	   		sendto(serv_sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, serv_len);
		}
   	}
   	printf("Total sent : %d bits.\n", m);  //�L�X�`�@�e�X����ƶq  
   	WSACleanup();
   	system("pause");
   	return 0;
}
