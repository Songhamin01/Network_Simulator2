#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"
#include "object.h"

class Host;

class Service : public Object {
  friend class ServiceInstaller;

private:
  virtual std::string name(){ return "Service"; }

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, int port) : host_(host), port_(port) {}

public:
  virtual ~Service(){}
  short getPort(){return port_;}
  virtual void result(Packet *p) = 0;
};

#endif