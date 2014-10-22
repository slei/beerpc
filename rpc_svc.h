/*************************************************************************
	> File Name: rpc_svc.h
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Sun 19 Oct 2014 12:21:41 AM CST
 ************************************************************************/

#ifndef _RPC_SVC_H
#define _RPC_SVC_H

#include "rpc.h"

#define MAXNAMELENGTH 20
#define BUFFER_SIZE 1024
#define LISTENQ 1024

typedef struct RPCPROC_T RPCPROC;
typedef struct RPCSVC_T RPCSVC;
struct RPCPROC_T {
	char name[MAXNAMELENGTH];
	rpcproc_t proc;
	struct RPCPROC *next;
};

struct RPCSVC_T {
	port_t port;
    RPCPROC *head;	
};

int RpcSvcInit(port_t port);
int RpcSvcRegister(char *procname, rpcproc_t proc);
int RpcSvcUnRegister(char *procname);
void RpcSvcRun();

#endif
