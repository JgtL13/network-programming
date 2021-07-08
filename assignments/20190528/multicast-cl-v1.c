#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <winsock.h>

#define MAXLINE 1024

SOCKET        	sd, sd_brod;
struct sockaddr_in serv,cli, brod;
char  		str[1024];
char  		str_brod[1024];
int cli_len, brod_len, n;
WSADATA 		wsadata;
int n, m, serv_len;
int flag=1,len=sizeof(int); 
char channel = 0, trash;

void *recvMess(void *argu) {    // �C�j�@�����L�X�@�����쪺�T�� 
    while (1) {
        cli_len= sizeof(cli);        
        memset(str, "\0", sizeof(str));
		n=recvfrom(sd, str, MAXLINE, 0,(LPSOCKADDR) &cli,&cli_len ); //��echo server���� 
		if (n > 0)
        	printf("client(from:%s):%s,%d\n",inet_ntoa(cli.sin_addr),str,n);  
    }
}

int main(int argc, char** argv) {  

	pthread_t thread1;
   
   	WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
  
   	sd=socket(AF_INET, SOCK_DGRAM, 0);
   	sd_brod=socket(AF_INET, SOCK_DGRAM, 0); //�]�w�����s���Ϊ�socket 
   
    if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, len) < 0 )
        printf("setsockopt() failed\n");
   	
	char broadcast = 'a'; //�]�w�����s���Ϊ�socket 
    if(	setsockopt(sd_brod, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   printf("setsockopt() broadcast error!\n");
   	
   	cli.sin_family       = AF_INET;
   	cli.sin_addr.s_addr  = 0;
   	cli.sin_port         = htons(8813);
   	
   	brod.sin_family       = AF_INET;//�]�w�����s���Ϊ�socket 
    brod.sin_addr.s_addr  = 0;   
    brod.sin_port         = htons(0103);
   	
  	if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 )
   		printf("bind error!\n");
   	
   	if( bind(sd_brod, (LPSOCKADDR) &brod, sizeof(brod)) <0 ) //�]�w�����s���Ϊ�socket 
   		printf("brodcast bind error!\n");
   		

   	
	struct ip_mreq multicastRequest;  /* Multicast address join structure */ 	
    /* Specify the multicast group */
    multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
    /* Accept multicast from any interface */
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    /* Join the multicast address */

    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    	printf("setsockopt() failed\n");

 	serv_len=sizeof(serv);
 	pthread_create(&thread1, NULL, &recvMess, NULL);
 	
 	setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)); //�@�}�l����ܸ`�س����ϥΪ̿�� 
 	brod_len= sizeof(brod);
 	m=recvfrom(sd_brod, str_brod, MAXLINE, 0,(LPSOCKADDR) &brod,&brod_len ); //��echo server���� 
	if (m > 0)
		printf("%s", str_brod); 

	while(1){
		channel = getchar(); //�����ϥΪ̪���J 
		trash = getchar();
		printf("switch to channel %c\n\n", channel);
		switch(channel)
		{
			case 'x': //��ܸ`�س����ϥΪ̭��s��� 
					multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
					setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest));
    				multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.2");
					setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest));
    				multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.3");
					setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest));
				      
					m=recvfrom(sd_brod, str_brod, MAXLINE, 0,(LPSOCKADDR) &brod,&brod_len ); //��echo server���� 
					if (m > 0)
			        	printf("%s", str_brod); 
		   			break;
			case '1': //��1�W�D 
					multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
					if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    					printf("setsockopt() failed\n");
    				break;
    		case 'a': //�h�X��1�W�D 
    				multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
					if (setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    					printf("setsockopt() failed\n");
    				break;
    		case '2'://��2�W�D
					multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.2");
					if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    					printf("setsockopt() failed\n");
    				break;
    		case 'b'://�h�X��2�W�D 
					multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.2");
					if (setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    					printf("setsockopt() failed\n");
    				break;
    		case '3'://��3�W�D
					multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.3");
					if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    					printf("setsockopt() failed\n");
    				break;
    		case 'c'://�h�X��3�W�D 
					multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.3");
					if (setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    					printf("setsockopt() failed\n");
    				break;
		} 
	}
	
  	closesocket(sd); //���� socket
    WSACleanup();  // ���� WinSock DLL ���ϥ�
   
   	return 0;
}


