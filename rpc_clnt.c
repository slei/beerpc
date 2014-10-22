/*************************************************************************
	> File Name: rpc_clnt.c
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Sun 19 Oct 2014 12:19:52 AM CST
 ************************************************************************/

#include "rpc_clnt.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

RPCCLIENT * Clnt_Create(char *servaddr, port_t servport) {
	RPCCLIENT *cl;
	cl = (RPCCLIENT *)malloc(sizeof(RPCCLIENT));
	if (NULL == cl)
		return NULL;

	cl->port = servport;
	if (inet_aton(servaddr, &cl->addr) == 0)
	{
		printf("Server IP Address Error!\n");
		free(cl);
		return NULL;
	}
	return cl;
}

int RpcCall(RPCCLIENT *client, const char *procname, rpcproc_t *proc) {
	if (NULL == client)
		return FAILED;
	printf("RPC Proc Name: %s\n", procname);

	struct sockaddr_in cliaddr;
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = htons(INADDR_ANY);
	cliaddr.sin_port = htons(0);

	int clisocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clisocket < 0) {
		printf("Create socket Failed!\n");
		return FAILED;
	}

	if (bind(clisocket, (struct sockaddr *)&cliaddr, sizeof(cliaddr)))
	{
		printf("Create Bind Port Failed!\n");
		return FAILED;
	}

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = client->addr;
	servaddr.sin_port = htons(client->port);

	if (connect(clisocket, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("Can't Connect to server!\n");
		return FAILED;
	}

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	strncpy(buffer, procname, strlen(procname) > BUFFER_SIZE ? BUFFER_SIZE:strlen(procname));
	send(clisocket, buffer, BUFFER_SIZE, 0);

	bzero(buffer, BUFFER_SIZE);
	int length = 0;
	while (length = recv(clisocket, buffer, BUFFER_SIZE, 0))
	{
		if (length < 0)
		{
			printf("Receive Data From Server Failed!\n");
			break;
		}
		printf("%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}
	printf("\n");

//	if (NULL != proc)
//		*proc;

	return SUCCESSED;
}

