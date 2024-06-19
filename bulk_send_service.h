#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"
#include <vector>
#include <iostream>

#define c_port 1000
#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

private:
  // Packet *p;
  Address destAddr;
  short destP;
  double delay_;
  double startT;
  double stopT;
  std::vector<Packet *> vec_packet;
  std::string d;
  virtual std::string name() { return "BulkSendService";}
  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0)
  : Service(host, c_port), destAddr(destAddress), destP(destPort), delay_(delay), startT(startTime), stopT(stopTime){}

public:
  void send()
  {
    Packet *p = new Packet(host_->address(), destAddr, port_, destP, d);
    startT += delay_;
    std::string m = "sending data";
    log(m);
    host_->send(p);
    std::function<void()> f = [this]() {this->send();};
    if(startT < stopT)
    {
      Simulator::schedule(startT, f);
    }
  }

  void result(Packet *p)
  {
    delete p;
  }
};

#endif