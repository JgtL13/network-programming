//client�ǭ���123.txt��server
//v1�G�C��e�@��char
#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n,counter=1;
  	char  	str[MAXLINE], fName[1024];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
  	FILE *fptr1;

	while(1)//�i�s�򦬦h���ɮ� 
	{
		printf("Enter destination file name : ");
		gets(fName); //Ū���Ʊ檺�ت��a�ɮצW�� 
		fptr1=fopen(fName,"w");
		if(fptr1!=NULL)
		{
	
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
			
			cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
			
			while( 1 ) 
			{
			    n=recv(cli_sd, str, MAXLINE, 0); //�����r�� 
			    if (n == 0)
				{
					puts("receive complete!!\n\n");
			    	break;
				}
				str[n]='\0';
			    printf("[%d] recv:%s  (size:%d) \n",counter,str,n);
				
				int i;
				for(i = 0; i < n; ++i) //�@���N�h�Ӧr���g�J�ɮ� 
				{
					putc(str[i],fptr1);
				}
				sleep(1); //�F���@�����h�Ӧr��  
			    counter++;
			}
		}
		fclose(fptr1);
		closesocket(cli_sd);
	   	closesocket(serv_sd);
	   	WSACleanup();
	}
   	system("pause");
   	return 0;
}
