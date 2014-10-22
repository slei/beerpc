/*************************************************************************
	> File Name: datesvc.c
	> Author: leiss
	> Mail: lss.linux@gmail.com 
	> Created Time: Tue 21 Oct 2014 05:54:58 PM CST
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include "rpc_svc.h"

void date(char *result, int length) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	strftime(result, length, "%D", &tm);
}

int main(int argc, char **argv) {
	
	RpcSvcInit(8011);
	RpcSvcRegister("date", date);
	RpcSvcRun();
}
