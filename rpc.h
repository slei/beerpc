/*************************************************************************
	> File Name: rpc.h
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Sun 19 Oct 2014 12:18:59 AM CST
 ************************************************************************/

#ifndef _RPC_H
#define _RPC_H
#include <stdlib.h>
#include <stdint.h>

typedef void (*rpcproc_t) (char *result, int length);
typedef uint16_t port_t;
typedef int32_t addr_t;

#define SUCCESSED 0
#define FAILED -1

#endif
