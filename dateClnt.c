/*************************************************************************
	> File Name: dateClnt.c
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Tue 21 Oct 2014 07:37:46 PM CST
 ************************************************************************/

#include <stdio.h>
#include "rpc_clnt.h"

void printdate() {
	printf("now print the date of the server!\n");
}

int main(int argc, char **argv) {
	RPCCLIENT *client;
	client = Clnt_Create("127.0.0.1", 8011);
	if (NULL == client)
		return FAILED;
	RpcCall(client, "date", printdate);
}
	
