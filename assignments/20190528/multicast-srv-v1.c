#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 15    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, serv_brod_sd;        /* socket �y�z�l */
  	int   	cli_len, brod_len, n,i=1;
  	char  	str[MAXLINE];
  	char    bc[200] = "�s��IP : 224.1.1.1~224.1.1.3\n�s��PORT : 8813\n\n�W�D1 : �W�D1����(�Ы�1��ܦ��ݡA��a��ܰ����)\n�W�D2 : �W�D2����(�Ы�2��ܦ��ݡA��b��ܰ����)\n�W�D3 : �W�D3����(�Ы�3��ܦ��ݡA��c��ܰ����)\n";  //�`�س� 

  	struct 	sockaddr_in   	serv, cli, brod;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
	
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// �}�� UDP socket
   	serv_brod_sd = socket(AF_INET, SOCK_DGRAM, 0);
   	
   	//�ΨӼs�����]�w
   	char broadcast = 'a';
	setsockopt(serv_brod_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
	brod.sin_family      = AF_INET;
   	brod.sin_addr.s_addr = inet_addr("255.255.255.255");
   	brod.sin_port        = htons(0103);

   	    /* Set TTL of multicast packet */
   	int multicastTTL=1;
    if (setsockopt(serv_sd, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &multicastTTL, 
          sizeof(multicastTTL)) == SOCKET_ERROR)
    printf("setsockopt() failed");
   	
   	
   	cli_len = sizeof(cli);
   	brod_len= sizeof(brod);
   	
   	
   	printf("server will multicastcast.\n");
   	               
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("224.1.1.1");
   	cli.sin_port        = htons(8813);
   		
while(1){	
	
		sendto(serv_brod_sd, bc, strlen(bc), 0,(LPSOCKADDR)&brod,brod_len);  //�s���`�ؿ�� 
		
		cli.sin_addr.s_addr = inet_addr("224.1.1.1"); //�W�D1 
		memset(str, i%10 +'0', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %s\n",str);		// ��ܰe�hclient ���r��	
        
        cli.sin_addr.s_addr = inet_addr("224.1.1.2"); //�W�D2 
        memset(str, (i - 1) % 26 +'a', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %s\n",str);		// ��ܰe�hclient ���r��	
        
        cli.sin_addr.s_addr = inet_addr("224.1.1.3"); //�W�D3 
        memset(str, (i - 1) % 26 +'A', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %s\n",str);		// ��ܰe�hclient ���r��
			
        sleep(1);
        i++;
    }
        
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
