#include "link.h"
#include "node.h"
#include "router.h"
#include "simulator.h"
#include <iostream>
#include <functional>

void Link::whatLink(Node *n, Packet *p)
{
    std::string m = "packet in: ";
    m += p->toString() + " from " + n->toString();
    log(m);
    std::function<void()> f = [n, p, this]()->void
    {
        std::string m = "packet out: ";
        m += p->toString() + " to " + other(n)->toString();
        log(m);
        other(n)->receiving(p);
    };
    Simulator::schedule(Simulator::now() + delay_, f);
}