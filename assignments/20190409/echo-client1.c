#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

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
   
   while(1)
   {
   		printf("speak: ");
   		gets(str);//����client1���ܡAŪ��client1����J 
		send(sd, str, strlen(str)+1, 0);//�e��server 
   		printf("send: %s (%d bytes)\n" ,str,strlen(str)+1);
   		n=recv(sd, str_r, MAXLINE, 0);//�����Ӧ�client2�����e 
		printf("recv from client 2: %s (%d bytes)\n",str_r,n); 
		n=recv(sd, str_r, MAXLINE, 0);//�����Ӧ�client3�����e 
		printf("recv from client 3: %s (%d bytes)\n",str_r,n);
   }   
  
   closesocket(sd); //����TCP socket
    
   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");
   
   return 0;
}

