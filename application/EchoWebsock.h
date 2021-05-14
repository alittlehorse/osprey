#pragma once
#include <drogon/WebSocketController.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <string>
#include <boost/json/src.hpp>
#include <libserver/osprey_server.hpp>
using namespace drogon;
class EchoWebsock : public drogon::WebSocketController<EchoWebsock> {
 public:
  virtual void handleNewMessage(const WebSocketConnectionPtr &,
                                std::string &&,
                                const WebSocketMessageType &) override;
  virtual void handleNewConnection(const HttpRequestPtr &,
                                   const WebSocketConnectionPtr &) override;
  virtual void handleConnectionClosed(const WebSocketConnectionPtr &) override;
  WS_PATH_LIST_BEGIN
    //list path definitions here;
    WS_PATH_ADD("/compute_query");
  WS_PATH_LIST_END
};
