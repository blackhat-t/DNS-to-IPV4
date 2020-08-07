#include <stdio.h>	
#include <string.h> 
#include <stdlib.h> 
#include <sys/socket.h>
#include <errno.h> 
#include <netdb.h> 
#include <arpa/inet.h>
#define BUFSIZE 1000

int hostname_to_ip(char *, char *);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please provide a hostfile to resolve");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	char buff[BUFSIZE];
	while (fgets(buff, BUFSIZE - 1, fp) != NULL)
	{
		char *hostname = buff;
		char ip[100];
		hostname_to_ip(hostname, ip);
		printf("%s ==>  %s\n", hostname, ip);
	}
	fclose(fp); 

}
/*
	Get ip from domain name
 */

int hostname_to_ip(char *hostname, char *ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		// get the host info
		herror("gethostbyname");
		return 1;
	}

	addr_list = (struct in_addr **)he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return 0;
	}

	return 1;
}