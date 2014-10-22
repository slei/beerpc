/*************************************************************************
	> File Name: rpc_clnt.h
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Sun 19 Oct 2014 12:19:44 AM CST
 ************************************************************************/

#ifndef _RPC_CLNT_H
#define _RPC_CLNT_H

#include "rpc.h"
#include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct RPCCLIENT_T RPCCLIENT;
struct RPCCLIENT_T {
	addr_t addr;
	port_t port;
};

RPCCLIENT * Clnt_Create(char *servaddr, port_t servport);
int RpcCall(RPCCLIENT *client, const char *procname,
		rpcproc_t *proc);

#endif

