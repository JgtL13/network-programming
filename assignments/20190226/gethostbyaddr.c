#include <stdio.h>
#include <winsock.h>

int main(void)
{
	char domain[]="";
	WSADATA 		wsadata;
	int nResult=WSAStartup(0x101,(LPWSADATA) &wsadata);
	if(nResult!=0)
	{
		printf("WSA Initialization failed: %d\n",nResult);
		WSACleanup();
		return 0;
	}
	
	LPHOSTENT hp;
	struct in_addr sAddr;
	int a1, b1, c1, d1, a2, b2, c2, d2;  //ミ纗IP竚计跑计
	char dot;  //ミ纗IP竚い翴跑计
	char inputS[15];  //ノ穓碝IPstring
	printf("Please input domain name range\n");  //块璶琩高IP絛瞅
	printf("From: ");
	scanf("%d""%c""%d""%c""%d""%c""%d", &a1, &dot, &b1, &dot, &c1, &dot, &d1);  //ㄌ弄癬﹍IP计,翴,计,翴,计,翴,计
	printf("To: ");
	scanf("%d""%c""%d""%c""%d""%c""%d", &a2, &dot, &b2, &dot, &c2, &dot, &d2);  //ㄌ弄挡IP计,翴,计,翴,计,翴,计
	printf("\n");
	
	int i = d1;  //硂跑计盢穦ノㄓ秈︽癹伴籔IP竚э
	while(i <= d2)
	{
		sprintf(inputS, "%d""%c""%d""%c""%d""%c""%d", a1, dot, b1, dot, c1, dot, i);  //盢玡弄ぇ跑计挡Θstring,ノ穓碝IP
		sAddr.s_addr=inet_addr(inputS);
		hp=gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);
printf(inputS);
		printf("'s host name: ");
		if(hp==NULL)
		    printf("none\n");
		else
		{
printf(hp->h_name);
		    printf("\n");	
   		}
		i = i + 1;  //盢璶琩高IP竚1
	}
}

