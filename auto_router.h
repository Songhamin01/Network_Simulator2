#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

class AutoRouter : public Router {
public:
  bool v[100];
  int d[100];
  int start;

  int getSmallIndex(const std::vector<Node *> nodes) 
  {
    int index = 0;
    int min = 99999999;
    for(int i = 0; i < nodes.size(); i++)
    {
      if (d[i] < min && !v[i])
      {
        min = d[i];
        index = i;
      }
    }
    return index;
  }

  void calculate(const std::vector<Node *> &nodes,
                 const std::vector<Link *> &links) {
    // node a, node b, node c, node d
    // a <- link a (1.0) -> b
    // b <- link b (2.0) -> c

     // 어떤 노드에서, 다른 노드로 최소거리로 갈수있는, 다음 홉
    std::vector<Link *> *linker = new std::vector<Link *>[nodes.size()];
    std::vector<std::pair<int, Link *>> *vec = new std::vector<std::pair<int, Link *>>[nodes.size()];
    double matrix[100][100];

    for(int i = 0; i < nodes.size(); i++) {
      for(int j = 0; j < nodes.size(); j++) {
        Node* a = nodes[i];
        Node* b = nodes[j];

        matrix[i][j] = 99999999;
        for(int k = 0; k < links.size(); k++) {
          Link* l = links[k];
          if(l->nodeA() == a && l->nodeB() == b) 
          {
            matrix[i][j] = l->delay();
            matrix[j][i] = l->delay();
            for (int x = 0; x < nodes.size(); x++)
            {
              if (nodes[x] == l->other(nodes[i]))
              {
                vec[i].push_back(std::make_pair(x, l));
              }
            }
          }

          if(i == j)
            matrix[i][j] = 0;
        }
      }
    }

    for(int i = 0; i < nodes.size(); i++)
    {
      if (nodes[i] == this)
      {
        start = i;
        break;
      }
    }
    // 다익스트라를 돌리면서 호스트에 대한 최소경로로 갈수잇는 다음 홉을 기록
    for(int i = 0; i < nodes.size(); i++)
    {
      d[i] = matrix[start][i];
    }

    v[start] = true;
    for(int i = 0; i < nodes.size()-1; i++)
    {
      int cur = getSmallIndex(nodes);
      v[cur] = true;
      std::vector<Link *> path;
      for(int j = 0; j < nodes.size(); j++)
      {
        if(!v[j])
        {
          if(d[cur] + matrix[cur][j] < d[j])
          {
            d[j] = d[cur] + matrix[cur][j];
            int next = getSmallIndex(nodes);
            for(int k = 0; k < vec[i].size(); k++)
            {
              if (vec[i][k].first == next)
              {
                path.push_back(vec[i][k].second);
              }
            }
          }
          linker[j] = path;
        }
      }
    }

    for(int i = 0; i < nodes.size(); i++) 
    {
      Node* node = nodes[i];
      Host* host = dynamic_cast<Host*>(node);
      if(host != nullptr) 
      {
        RoutingEntry re;
        re.destination = host->address(); 
        re.nextLink = linker[i][0];
        routingTable_.push_back(re);
      }
    }

    vec->clear();
    linker->clear();
    delete[] vec;
    delete[] linker;
  }
};

#endif