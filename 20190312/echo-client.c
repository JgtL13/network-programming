#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

   	SOCKET        	sd;     
   	struct sockaddr_in serv;
   	char  		str[1024], str_r[1024], response[MAXLINE], sGuess[MAXLINE]/*, trash[MAXLINE]*/;
   	WSADATA 		wsadata;
   	int n, m, myAnswer, round = 0;
   	char trash;

	printf("Enter your answer for the server to guess : ");
	scanf("%d", &myAnswer); //��J�n��server�q������ 
	while(1)
	{
		++round;
   		WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
  
   		sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   		serv.sin_family       = AF_INET; 
   		serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   		serv.sin_port         = htons(5678);
   		
		printf("Round %d : Guess the answer : ", round);
		scanf("%s", &str); //�ۤv�q��server������ 
	   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
	
	   	send(sd, str, strlen(str)+1, 0); //�ǰe���׵�server 
	   
	   	n = recv(sd, str_r, MAXLINE, 0); //server�^�Ǫ��^�� ���׬O�_���T 
		m = recv(sd, sGuess, MAXLINE, 0); //���� server�q�A������ 
	   	printf("Server says %s. Server guessed %s. Your response : ", str_r, sGuess);
	   	if(strcmp(str_r, "correct") == 0) //�Y���T ����C�� 
	   	{
	   		break;
		}
	   	scanf("%c", &trash); //����gets����e�����Ů� 
		gets(response); //Ū���A��server���^�� 
		send(sd, response, strlen(response)+1, 0); //�ǰe�A���^�е�server 
		if(strcmp(response, "correct") == 0) //�Y���T ����C�� 
		{ 
			break;
		} 
	}
	  
	closesocket(sd); //����TCP socket    
	WSACleanup();  // ���� WinSock DLL ���ϥ�
   	system("pause");
   	return 0;
}


