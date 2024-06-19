#include "echo_service.h"
#include "packet.h"
#include <iostream>
#include <vector>

void EchoService::result(Packet *p)
{
    std::string m = "received \"" + p->dataString() + "\" from " + p->srcAddress().toString() + ":" + std::to_string(p->srcPort()) + " send reply with same data";
    log(m);
    send(p);
    delete p;
}

void EchoService::send(Packet *p)
{
    packets = new Packet(host_->address(), p->srcAddress(), port_, p->srcPort(), p->data());
    host_->send(packets);
}