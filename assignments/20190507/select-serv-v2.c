#include<stdio.h>
#include<winsock.h>
#define MAXRECV 1024  
#define MAXCLI 6 
int main(int argc , char *argv[])
{
WSADATA wsadata;
SOCKET serv_sd , new_socket,cli_sd[MAXCLI];
struct sockaddr_in serv, cli;

int activity, cli_len, i, j, n, client_num=0;
fd_set readfds;
char str[MAXRECV];
char reject[MAXRECV] = "This room is currently full, please try again later.\n";
char newMember[MAXRECV] = "A new member has entered the chat.\n";

for(i=0;i<MAXCLI;i++)
	cli_sd[i]=0;

WSAStartup(0x101, &wsadata);
   	
serv_sd=socket(AF_INET, SOCK_STREAM, 0);

serv.sin_family = AF_INET;
serv.sin_addr.s_addr = INADDR_ANY;
serv.sin_port = htons( 5678 );

bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

listen(serv_sd , 3);


while(TRUE)
{
	printf("[1]clear the socket fd set. \n");
	FD_ZERO(&readfds);
	
	printf("[2]add serv_sd  to fd set \n");
	FD_SET(serv_sd, &readfds);
	
	printf("[2]add cli_sd[]  to fd set \n");
	for(i=0;i<MAXCLI;i++)
	{
		if(cli_sd[i]>0)
		{
			FD_SET(cli_sd[i], &readfds);
		}
			
	}
		
	printf("[3]call select() and waiting \n");
	activity = select( 0 , &readfds , NULL , NULL , NULL);
	printf("[4]wake up from select()\n");
	
	if ( activity == SOCKET_ERROR ){
		printf("select call failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	if (FD_ISSET(serv_sd , &readfds)){
		cli_len = sizeof(cli);
		new_socket = accept(serv_sd , (struct sockaddr *)&cli, (int *)&cli_len);
		printf("New connection: socket fd is %d , ip is : %s , port : %d \n" , new_socket , 
				inet_ntoa(cli.sin_addr) , ntohs(cli.sin_port));
		for(i=0;i<MAXCLI;i++){
			if(cli_sd[i]==0){
				cli_sd[i]=new_socket;
				client_num ++;
				if(client_num == MAXCLI) //判斷當前加入的使用者是否超出上限
				{
					send( cli_sd[i] , reject , strlen(reject)+1 , 0 ); //傳送斷線通知 
					closesocket(cli_sd[i]); //斷線 
					cli_sd[i] = 0;  
					client_num --;
					break;
				}
				for(j = 0; j < client_num; ++j) //若有新使用者加入，通知其他在線使用者 
				{
					if(cli_sd[j] != 0)
					{
						send( cli_sd[j] , newMember , strlen(newMember)+1 , 0 );
					}
				}
				printf("The %d client socket is in cli_sd[%d]\n",client_num,i);
				break;
			}
		}
	}
	
	for(i=0;i<MAXCLI;i++){
		if(FD_ISSET( cli_sd[i] , &readfds) ){
			n = recv( cli_sd[i] , str, MAXRECV, 0);
			if( n == SOCKET_ERROR){
				int error_code = WSAGetLastError();
				if(error_code == WSAECONNRESET){
					printf("Host disconnected unexpectedly\n");
					closesocket( cli_sd[i] );	
					cli_sd[i] = 0;
					client_num --;
				}
				else
					printf("recv failed with error code : %d" , error_code);				
			}
			if ( n == 0){
				printf("Host disconnected. \n" );
					closesocket( cli_sd[i] );	
					cli_sd[i] = 0;
					client_num --;
			}
			if (n > 0) {
				for(j = 0; j < MAXCLI; ++j) //若有使用者發言，其他使用者也會收到訊息 
				{
					if(cli_sd[j] != 0)
					{
						send( cli_sd[j] , str , strlen(str)+1 , 0 );
					}
				}
			}
		}
	}
}
closesocket(serv_sd);

WSACleanup();
system("pause");

return 0;
}
