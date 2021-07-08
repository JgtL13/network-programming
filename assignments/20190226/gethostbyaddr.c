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
	int a1, b1, c1, d1, a2, b2, c2, d2;  //建立儲存IP位置各個數值的變數
	char dot;  //建立儲存IP位置中點的變數
	char inputS[15];  //用於搜尋IP的string
	printf("Please input domain name range\n");  //輸入要查詢的IP的範圍
	printf("From: ");
	scanf("%d""%c""%d""%c""%d""%c""%d", &a1, &dot, &b1, &dot, &c1, &dot, &d1);  //依序讀入起始IP的數字,點,數字,點,數字,點,數字
	printf("To: ");
	scanf("%d""%c""%d""%c""%d""%c""%d", &a2, &dot, &b2, &dot, &c2, &dot, &d2);  //依序讀入結束IP的數字,點,數字,點,數字,點,數字
	printf("\n");
	
	int i = d1;  //這個變數將會用來進行迴圈與IP位置的更改
	while(i <= d2)
	{
		sprintf(inputS, "%d""%c""%d""%c""%d""%c""%d", a1, dot, b1, dot, c1, dot, i);  //將先前讀入之各個變數結合成一個string,用於搜尋IP
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
		i = i + 1;  //將要查詢的IP位置加1
	}
}

