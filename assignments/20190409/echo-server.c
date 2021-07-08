#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd1, cli_sd2, cli_sd3;        /* socket �y�z�l */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE];
  	struct 	sockaddr_in  serv, cli;
  	WSADATA wsadata;
	   	
	   	
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
   	
   	//����client1 
	printf("server waits for client 1.\n");  		
	cli_sd1=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //�إ߳s�u 
	printf("connection succesful.\n");
	getpeername(cli_sd1, (LPSOCKADDR) &tAddr, &lentAddr);  //���peer name 
	printf("Client 1' IP: %s, port: %d\n", inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port)); //��Xpeer��IP��m��port number 
	
	//����client2
	printf("server waits for client 2.\n");  		
	cli_sd2=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);//�إ߳s�u  
	printf("connection succesful.\n");
	getpeername(cli_sd2, (LPSOCKADDR) &tAddr, &lentAddr);//���peer name
	printf("Client 2' IP: %s, port: %d\n", inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));//��Xpeer��IP��m��port number 
	
	//����client3 
	printf("server waits for client 3.\n");  		
	cli_sd3=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len); //�إ߳s�u 
	printf("connection succesful.\n");
	getpeername(cli_sd3, (LPSOCKADDR) &tAddr, &lentAddr);//���peer name
	printf("Client 3' IP: %s, port: %d\n", inet_ntoa(tAddr.sin_addr), ntohs(tAddr.sin_port));//��Xpeer��IP��m��port number 

	while(1)
	{
		n = recv(cli_sd1, str_r, MAXLINE, 0);//Ū���Ӧ�client1�����e 
    	printf("server recv from client1: %s (%d bytes)\n",str_r,n); 
    	strcpy(str, str_r);
		send(cli_sd2, str, strlen(str)+1, 0);//�ǰe��client2 
		send(cli_sd3, str, strlen(str)+1, 0);//�ǰe��client3
    	printf("server sends to client2: %s (%d bytes)\n", str, strlen(str) + 1);
    	printf("server sends to client3: %s (%d bytes)\n", str, strlen(str) + 1);
    	
    	n = recv(cli_sd2, str_r, MAXLINE, 0);//Ū���Ӧ�client2�����e 
    	printf("server recv from client2: %s (%d bytes)\n",str_r,n); 
    	strcpy(str, str_r);
		send(cli_sd1, str, strlen(str)+1, 0);//�ǰe��client1
		send(cli_sd3, str, strlen(str)+1, 0);//�ǰe��client3
    	printf("server sends to client1: %s (%d bytes)\n", str, strlen(str) + 1);
    	printf("server sends to client3: %s (%d bytes)\n", str, strlen(str) + 1);
    	
    	n = recv(cli_sd3, str_r, MAXLINE, 0);//Ū���Ӧ�client3�����e 
    	printf("server recv from client3: %s (%d bytes)\n",str_r,n); 
    	strcpy(str, str_r);
		send(cli_sd1, str, strlen(str)+1, 0);//�ǰe��client1
		send(cli_sd2, str, strlen(str)+1, 0);//�ǰe��client2
    	printf("server sends to client1: %s (%d bytes)\n", str, strlen(str) + 1);
    	printf("server sends to client2: %s (%d bytes)\n", str, strlen(str) + 1);
	}
    
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	closesocket(cli_sd1);
   	closesocket(cli_sd2);
   	WSACleanup();
   	system("pause");
}

