#include "router.h"
#include <iostream>

Router::~Router()
{
    routingTable_.clear();
}

void Router::receiving(Packet *p)
{
    bool isTrue = false;
    for(int i = 0; i < (int)routingTable_.size(); ++i)
    {
        if(routingTable_[i].destination == p->destAddress())
        {
            isTrue = true;
            std::string m = "forwarding packet: " + p->toString() + " to " + routingTable_[i].nextLink->toString();
            log(m);
            routingTable_[i].nextLink->whatLink(this, p);
            break;
        }
    }

    if (!isTrue)
    {
        std::string m = "no route for packet: " + p->toString();
        log(m);
        delete p;
    }
}

