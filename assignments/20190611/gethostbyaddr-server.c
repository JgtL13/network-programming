#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE];
  	struct 	sockaddr_in  serv, cli;
  	struct in_addr sAddr;
  	char serv_name[100] = "echo";
  	WSADATA wsadata;
  	LPHOSTENT hp;
  	LPSERVENT sp;
  	LPPROTOENT pp;
	
	   	
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(1234);	// ���wport
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));	
   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
   	struct sockaddr_in tAddr; 
   	int lentAddr;
   	lentAddr = sizeof(tAddr);
   	cli_len = sizeof(cli);		
	cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //�إ߳s�u 

	//�dIP
	n = recv(cli_sd, str_r, MAXLINE, 0);//Ū���Ӧ�client�����e 
	sAddr.s_addr = inet_addr(str_r);
	hp = gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);
	snprintf(str, sizeof(str), "host name:%s\n", hp->h_name);//�N���G��Jstr 
	send(cli_sd, str, strlen(str)+1, 0);//�N���G�ǰe��client 
	
	//�d�D���W��
	n = recv(cli_sd, str_r, MAXLINE, 0);//Ū���Ӧ�client�����e 
	hp = gethostbyname(str_r);
	snprintf(str, sizeof(str), "host IP:%s\n", inet_ntoa(*(LPIN_ADDR)(hp->h_addr)));//�N���G��Jstr 
	send(cli_sd, str, strlen(str)+1, 0);//�N���G�ǰe��client 
	
	//�dservice��port
	n = recv(cli_sd, str_r, MAXLINE, 0);//Ū���Ӧ�client�����e 
	char proto[100] = "tcp";
	sp = getservbyname(str_r, proto);
	snprintf(str, sizeof(str), "port:%d\n", ntohs(sp -> s_port));//�N���G��Jstr 
	send(cli_sd, str, strlen(str)+1, 0);//�N���G�ǰe��client 
	
	//�b�S�wport��service
	n = recv(cli_sd, str_r, MAXLINE, 0);//Ū���Ӧ�client�����e 
	int port = atoi(str_r);
	port = (int)str_r;
	char proto1[100] = "tcp";
	sp = getservbyport(htons((unsigned short)str_r), proto1);
	snprintf(str, sizeof(str), "Serve name:%s\n", (LPSTR) serv_name);//�N���G��Jstr 
	send(cli_sd, str, strlen(str)+1, 0);//�N���G�ǰe��client 
	
	//�dprotocol���s��
	n = recv(cli_sd, str_r, MAXLINE, 0);//Ū���Ӧ�client�����e 
	pp = getprotobyname(str_r);
	snprintf(str, sizeof(str), "number:%d\n", pp -> p_proto);//�N���G��Jstr 
	send(cli_sd, str, strlen(str)+1, 0);//�N���G�ǰe��client 
	
	//�d�b�S�w�s����protocol
	n = recv(cli_sd, str_r, MAXLINE, 0);//Ū���Ӧ�client�����e 
	int number = atoi(str_r);
	pp = getprotobynumber(number);
	snprintf(str, sizeof(str), "protocol name:%s\n", pp -> p_name);//�N���G��Jstr 
	send(cli_sd, str, strlen(str)+1, 0);//�N���G�ǰe��client 
	
	
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
}
