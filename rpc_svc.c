/*************************************************************************
	> File Name: rpc_svc.c
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Sun 19 Oct 2014 12:21:48 AM CST
 ************************************************************************/

#include "rpc_svc.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

RPCSVC *svc;

int RpcSvcInit(port_t port) {
 if (svc == NULL) 
 {
	 svc = (RPCSVC *)malloc(sizeof(RPCSVC));
	 if (svc == NULL)
		 goto err;
 }

 svc->port = port;
 svc->head = NULL;
 return SUCCESSED;

err:
 return FAILED;
}

static RPCPROC *RpcSvcFindProc(RPCPROC *head, char *procname) {
	if (NULL == head)
		return NULL;

	RPCPROC *p;
	for (p = head; p != NULL; p = p->next)
		if (strcmp(p->name, procname) == 0)
			break;
	return p;
}

static void RpcSvcRemoveProc(RPCPROC *head, char *procname) {

}

int RpcSvcRegister(char *procname, rpcproc_t proc) {
	if (NULL == svc)
	  return FAILED;

	int namelen = strlen(procname) + 1;
	if (namelen > MAXNAMELENGTH)
		return FAILED;

	RPCPROC *procnode = RpcSvcFindProc(svc->head, procname);
	if (NULL == procnode) 
	{
		procnode = (RPCPROC *)malloc(sizeof(RPCPROC));
		if (NULL == procnode)
			goto err;
		strcpy(procnode->name, procname);
		procnode->proc = proc;
	} else
		return FAILED;
	procnode->next = svc->head;
	svc->head = procnode;
	return SUCCESSED;

err:
	return FAILED;	
}

int RpcSvcUnRegister(char *procname) {
	if (NULL == svc)
		return FAILED;

	RPCPROC *procnode = RpcSvcFindProc(svc->head, procname);
	if (NULL == procnode)
		return FAILED;

	RpcSvcRemoveProc(svc->head, procname);
	return SUCCESSED;
}

static void RpcSvcExec(char *buffer, char *result, int length) {
	printf("current buffer: %s\n", buffer);
	char *procname = buffer;
	RPCPROC *procnode = RpcSvcFindProc(svc->head, procname);
	if (NULL == procnode)
		return "Not Find Proc";

	rpcproc_t proc = procnode->proc;
	(*proc)(result, length);
}

void RpcSvcRun() {
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buffer[BUFFER_SIZE], result[BUFFER_SIZE];
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(svc->port);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);
	printf("start listenning\n");

	while(1) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
		bzero(buffer, BUFFER_SIZE);
		len = recv(connfd, buffer, BUFFER_SIZE, 0);
		if (len < 0)
			break;

		/* resolve buffer */
		
		RpcSvcExec(buffer, result, BUFFER_SIZE);
		send(connfd, result, strlen(result) + 1, 0);
		close(connfd);
	}
}
