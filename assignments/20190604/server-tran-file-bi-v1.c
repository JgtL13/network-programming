//server��(����)
//client -> server �G�줸��

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */
#define MAX 50

int main()
{
	SOCKET	serv_sd, cli_sd, cli_sd2;        /* socket �y�z�l */
  	int   	cli_len, n=1, bytes;
  	char  	str[MAXLINE];
  	char str_r[MAXLINE];
  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
    
	WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket
   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���w IPPORT_ECHO �� echo port
    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
   	cli_len = sizeof(cli);

   	while (1) 
	{
   		printf("server: waiting for client\n");
   		cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //�}��client1��socket 
   		cli_sd2 = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //�}��client2��socket 
   		send(cli_sd, "ready", strlen("ready") + 1, 0); //�i��client1�i�H�i��ǰe�F 
        while(1) 
		{
            n=recv(cli_sd, str, MAXLINE, 0); //������� 
            if (strcmp(str,"EOF") == 0) //�ˬd��ƬO�_�ǧ� 
            {
            	send(cli_sd2, "EOF", strlen("EOF") + 1, 0); //�ǵ�client2�i������ 
            	break; 
			}
            memcpy(str_r, str, MAXLINE); //�N���쪺��ƽƻs��t�@�ӯx�}�� 
            send(cli_sd2, str_r, n, 0); //�ǵ�client2 
        }
	    printf("recv EOF:%s\n" ,str);
	    printf("recv complete!! \n");
    }

	//���� WinSock DLL ���ϥ�
	system("pause");
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	closesocket(cli_sd2);

   	WSACleanup();
   	return 0;
}
