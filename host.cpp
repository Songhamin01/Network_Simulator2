#include "host.h"
#include <cstdlib>
#include <iostream>

Host::~Host()
{
    for (int i = 0; i < (int)services_.size(); ++i)
    {
        delete services_[i];
    }
}

// 호스트와 설치된 서비스를 전부 초기화한다.

// 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
void Host::send(Packet *packet)
{
    std::string m = "sending packet: " + packet->toString();
    log(m);
    int num = rand() % links_.size();
    links_[num]->whatLink(this, packet);
}

void Host::receiving(Packet *p)
{
    bool isTrue = false;
    std::string m = "received packet: " + p->toString();
    for(int i = 0; i < (int)services_.size(); ++i)
    {
        if(services_[i]->getPort() == p->destPort())
        {
            m += ", forwarding to " + services_[i]->toString();
            log(m);
            services_[i]->result(p);
            isTrue = true;
            break;
        }
    }

    if (!isTrue)
    {
        m = "no service for packet: " + p->toString();
        log(m);
        delete p;
    }
    
}