#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n, temp = 50, round = 0, left = 1, right = 100;
  	char  	str[MAXLINE], str_r[MAXLINE], sResponse[MAXLINE], cResponse[MAXLINE], sGuess[MAXLINE];
	srand(time(NULL));
  	struct 	sockaddr_in   	serv, cli;
  	int min = 1;
  	int max = 100;
  	int answer = rand() % (max - min + 1) + min;
  	sprintf(sGuess, "%d", temp);
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
   	
  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport


	while(1)//����i��C�� 
   	{
   		++round;
	    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
	   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
		   	
		cli_len = sizeof(cli);
	 		
		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	   	n=recv(cli_sd, str_r, MAXLINE, 0); //��server���� 
	   	printf("Round %d : ", round);
	   	printf("Client guessed %s, ",str_r);
	
		int input = atoi(str_r);//�Nstr_r��string�ରint ��K����p�� 
		
		if(input == answer) //�Y���ץ��T 
	   	{
	   		strcpy(sResponse, "correct");
	   		printf("%s. ", sResponse);
	   		send(cli_sd, sResponse, strlen(sResponse) + 1, 0);
	   		break;
		}
		else if(input < answer) //�Y�p�󵪮� 
		{
			strcpy(sResponse, "too small");
			printf("%s. ", sResponse);
			send(cli_sd, sResponse, strlen(sResponse) + 1, 0);
		}
		else if(input > answer) //�Y�j�󵪮� 
		{
			strcpy(sResponse, "too large");
			printf("%s. ", sResponse);
			send(cli_sd, sResponse, strlen(sResponse) + 1, 0);
		}	
		
		printf("Server guesses %s.\n", sGuess);
		send(cli_sd, sGuess, strlen(sGuess) + 1, 0); //�Nserver�q���Ʀr�^�Ǧ�client�� 
		n=recv(cli_sd, cResponse, MAXLINE, 0); //����client�^�Ǫ��^�� ���׬O�_���T 
		if(strcmp(cResponse, "too large") == 0)
		{
			right = temp;
			temp = temp - ((temp - left) / 2); //�G���j�M�k 
			sprintf(sGuess, "%d", temp);
		}
		else if(strcmp(cResponse, "too small") == 0)
		{
			left = temp;
			//printf("here2");
			temp = temp + ((right - temp) / 2); //�G���j�M�k 
			sprintf(sGuess, "%d", temp);
		}
		else if(strcmp(cResponse, "correct") == 0) //�Y���ץ��T ����C�� 
		{
			break;
		}
	}
    
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
   	return 0;
}
