#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd, sd;        /* socket �y�z�l */
  	int   	i, j, cli_len, n, m, counter = 0;
  	char  	str[MAXLINE],str_r[MAXLINE];
  	float speed;

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
   	
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    	
   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
   	
	    	
	cli_len = sizeof(cli);
	printf("Server waiting for Client\n");  		
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	
	clock_t t;  
	t = clock();  //�Ұʭp�ɾ� 
		
	while(1)
	{
	   	n=recv(cli_sd, str_r, MAXLINE, 0); //��server���� 
	    ++counter;  //�p�Ⱶ���F�X���A���ʧ@�O���F���᭰�C�e������s�t�v 
	    if(counter == 16384)
	    {
	    	counter = 0; 
	    	t = clock() - t;  //�p��Ҫ᪺�ɶ� 
		   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
		   	speed = 16384 / time_taken / 1024;  //�p��t�v 
		   	printf("Receiving speed:%0.2f kbps\n", speed);
		   	t = clock();  //���]�p�ɾ� 
		}
	    
	    if(n == 0)	
			break;
			
	}
	
	closesocket(cli_sd);    
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
	
	
	//����洫 
	memset(str,1,MAXLINE);
   
   	WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
  
 
   	sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.
   
   	serv.sin_family       = AF_INET; 
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(5678);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
	
   	for (i = 0; i < 64; i++)  //���B�����h�j�骺�ηN����ֵe����s�t�v 
   	{
   		clock_t t;
		t = clock();  //�Ұʭp�ɾ� 
   		for(j = 0; j < 16384; ++j)
		{
	   		m = send(sd, str, MAXLINE, 0); //�ǰe
		}	
		t = clock() - t;  //�p��Ҫ�ɶ� 
	   	float time_taken = ((float)t) / CLOCKS_PER_SEC;
	   	speed = 16384 / time_taken / 1024;  //�p��t�v 
	   	printf("Sending speed:%0.2f kbps\n", speed);
   	}
 
   	closesocket(sd); //����TCP socket
   	WSACleanup();
   	system("pause");
}
