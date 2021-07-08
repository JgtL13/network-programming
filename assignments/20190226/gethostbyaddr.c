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
	int a1, b1, c1, d1, a2, b2, c2, d2;  //�إ��x�sIP��m�U�ӼƭȪ��ܼ�
	char dot;  //�إ��x�sIP��m���I���ܼ�
	char inputS[15];  //�Ω�j�MIP��string
	printf("Please input domain name range\n");  //��J�n�d�ߪ�IP���d��
	printf("From: ");
	scanf("%d""%c""%d""%c""%d""%c""%d", &a1, &dot, &b1, &dot, &c1, &dot, &d1);  //�̧�Ū�J�_�lIP���Ʀr,�I,�Ʀr,�I,�Ʀr,�I,�Ʀr
	printf("To: ");
	scanf("%d""%c""%d""%c""%d""%c""%d", &a2, &dot, &b2, &dot, &c2, &dot, &d2);  //�̧�Ū�J����IP���Ʀr,�I,�Ʀr,�I,�Ʀr,�I,�Ʀr
	printf("\n");
	
	int i = d1;  //�o���ܼƱN�|�ΨӶi��j��PIP��m�����
	while(i <= d2)
	{
		sprintf(inputS, "%d""%c""%d""%c""%d""%c""%d", a1, dot, b1, dot, c1, dot, i);  //�N���eŪ�J���U���ܼƵ��X���@��string,�Ω�j�MIP
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
		i = i + 1;  //�N�n�d�ߪ�IP��m�[1
	}
}

