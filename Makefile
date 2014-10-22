CFLAGS= -c -g -Wall

client: dateclient 
server: dateserver

dateclient: dateClnt.o rpc_clnt.o
	gcc -o dateclient dateClnt.o rpc_clnt.o

dateserver: datesvc.o rpc_svc.o
	gcc -o dateserver datesvc.o rpc_svc.o

dateClnt.o: dateClnt.c rpc_clnt.h
	gcc $(CFLAGS) dateClnt.c rpc_clnt.h

datesvc.o: datesvc.c rpc_svc.h
	gcc  $(CFLAGS) datesvc.c rpc_svc.h

rpc_clnt.o: rpc_clnt.c rpc_clnt.h rpc.h
	gcc  $(CFLAGS) rpc_clnt.c rpc_clnt.h rpc.h

rpc_svc.o: rpc_svc.c rpc_svc.h rpc.h
	gcc  $(CFLAGS) rpc_svc.c rpc_svc.h rpc.h

clean:
	rm -rf *.o *.gch dateclient dateserver
