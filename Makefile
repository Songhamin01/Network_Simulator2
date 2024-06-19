CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first second third forth

simulator.o: simulator.cpp simulator.h
	$(CC) $(CFLAGS) -c -o simulator.o simulator.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c -o object.o object.cpp

node.o: node.cpp node.h packet.h object.h
	$(CC) $(CFLAGS) -c -o node.o node.cpp

host.o: host.cpp host.h node.h
	$(CC) $(CFLAGS) -c -o host.o host.cpp

router.o: router.cpp router.h	node.h
	$(CC) $(CFLAGS) -c -o router.o router.cpp

manual_router.o: manual_router.cpp manual_router.h router.h
	$(CC) $(CFLAGS) -c -o manual_router.o manual_router.cpp

link.o: link.cpp link.h object.h
	$(CC) $(CFLAGS) -c -o link.o link.cpp

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c -o link_installer.o link_installer.cpp

service_installer.o:service_installer.cpp service_installer.h
	$(CC) $(CFLAGS) -c -o service_installer.o service_installer.cpp

message_service.o: message_service.cpp message_service.h service.h
	$(CC) $(CFLAGS) -c -o message_service.o message_service.cpp
	
message_service_installer.o: message_service_installer.cpp message_service_installer.h service_installer.h
	$(CC) $(CFLAGS) -c -o message_service_installer.o message_service_installer.cpp

echo_service.o: echo_service.cpp echo_service.h service.h
	$(CC) $(CFLAGS) -c -o echo_service.o echo_service.cpp
	
echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h service_installer.h
	$(CC) $(CFLAGS) -c -o echo_service_installer.o echo_service_installer.cpp

first.o: scenarios/first.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h simulator.h
	$(CC) $(CFLAGS) -c -o first.o scenarios/first.cpp

second.o: scenarios/second.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h simulator.h
	$(CC) $(CFLAGS) -c -o second.o scenarios/second.cpp

third.o: scenarios/third.cpp echo_service.h echo_service_installer.h host.h link.h link_installer.h auto_router.h message_service_installer.h bulk_send_service.h packet_sink_service.h simulator.h
	$(CC) $(CFLAGS) -c -o third.o scenarios/third.cpp

forth.o: scenarios/forth.cpp echo_service.h message_service.h echo_service_installer.h host.h link.h link_installer.h auto_router.h message_service_installer.h bulk_send_service.h packet_sink_service.h simulator.h
	$(CC) $(CFLAGS) -c -o forth.o scenarios/forth.cpp

first: first.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o
	$(CC) $(CFLAGS) -o first first.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o

second: second.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o
	$(CC) $(CFLAGS) -o second second.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o

third: third.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o
	$(CC) $(CFLAGS) -o third third.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o

forth: forth.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o
	$(CC) $(CFLAGS) -o forth forth.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o simulator.o object.o

clean:
	rm -f *.o first second third forth