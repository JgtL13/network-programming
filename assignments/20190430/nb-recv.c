#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd[10], new_sd;        /* socket �y�z�l */
  	int   	cli_len, n, i, j, x, num_client;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
   	
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���w IPPORT_ECHO �� echo port

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    	
   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
   	
   	cli_len = sizeof(cli);
	
	printf("server: waiting for client\n");
	
	cli_sd[0] = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	num_client = 1;
	u_long iMode = 1;
	ioctlsocket(serv_sd, FIONBIO, &iMode);
	ioctlsocket(cli_sd[0], FIONBIO, &iMode);
	
   	while (1) {
   		if((new_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len)) != -1) //�����s��client 
   		{
   			printf("server gets a new client connection.(%d)\n", num_client + 1);
			cli_sd[num_client] = new_sd; //�N�s��client�[�J�}�C�� 
			ioctlsocket(cli_sd[num_client], FIONBIO, &iMode);
			num_client++; //client�`�ƶq�W�[ 
		}
       		
		for (i = 0; i < num_client; ++i)
		{       		
	        n=recv(cli_sd[i], str, MAXLINE, 0);
			if (n > 0 ){
	        	printf("cli[%d] recv and send: %s\n", i + 1, str);    	// ��ܱq client �ǨӪ��r��
	        	send(cli_sd[i], str, strlen(str)+1, 0);  //echo 
	        }
			int nError=WSAGetLastError();
			if(nError!=WSAEWOULDBLOCK && nError!=0)
			{
				printf("cli[%d] disconnected!\n", i + 1);
				--num_client; //�Y��client�_�u�h���client�`�ƶq 
				closesocket(cli_sd[i]); //�����_�u��client 
				for(j = i; j < num_client; ++j)
				{
					printf("client %d is now renamed as client %d\n", j + 2, j + 1);
					cli_sd[j] = cli_sd[j + 1];	//�N�_�u��client���᪺client���e���� 
				}
			}
        } 
    }
 
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	WSACleanup();
}
