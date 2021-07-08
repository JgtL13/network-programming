#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) 
{  

   	SOCKET        	sd;     
   	struct sockaddr_in serv;
   	char  		str[1024];
   	char  		str_r[1024];;
   	WSADATA 		wsadata;
   	int n = 1;

   	WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
   	sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.
   	serv.sin_family       = AF_INET; 
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   	serv.sin_port         = htons(1234);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
   	
   	//�dIP
   	printf("�dIP: ");
   	gets(str);//������J
	send(sd, str, strlen(str)+1, 0);//�e��server 
   	n = recv(sd, str_r, MAXLINE, 0);//�����Ӧ�server���^�� 
   	printf("%s\n\n", str_r);
   	
   	//�d�D���W��
   	printf("�d�D���W��: ");
	gets(str);//������J
	send(sd, str, strlen(str)+1, 0);//�e��server 
   	n = recv(sd, str_r, MAXLINE, 0);//�����Ӧ�server���^�� 
   	printf("%s\n\n", str_r);
   	
   	//�dservice��port
   	printf("�dservice��port: ");
	gets(str);//������J
	send(sd, str, strlen(str)+1, 0);//�e��server 
   	n = recv(sd, str_r, MAXLINE, 0);//�����Ӧ�server���^�� 
   	printf("%s\n\n", str_r);
   	
   	//�b�S�wport��service
   	printf("�d�b�S�wport��service: ");
	gets(str);//������J
	send(sd, str, strlen(str)+1, 0);//�e��server 
   	n = recv(sd, str_r, MAXLINE, 0);//�����Ӧ�server���^�� 
   	printf("%s\n\n", str_r);
   	
   	//�dprotocol���s��
   	printf("�dprotocol���s��: ");
	gets(str);//������J
	send(sd, str, strlen(str)+1, 0);//�e��server 
   	n = recv(sd, str_r, MAXLINE, 0);//�����Ӧ�server���^�� 
   	printf("%s\n\n", str_r);
   	
   	//�d�b�S�w�s����protocol
   	printf("�d�b�S�w�s����protocol: ");
	gets(str);//������J
	send(sd, str, strlen(str)+1, 0);//�e��server 
   	n = recv(sd, str_r, MAXLINE, 0);//�����Ӧ�server���^�� 
   	printf("%s\n\n", str_r);
   		
  
   	closesocket(sd); //����TCP socket
   	WSACleanup();  // ���� WinSock DLL ���ϥ�
   	system("pause");
   
   	return 0;
}


