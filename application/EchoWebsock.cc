#include "EchoWebsock.h"
/**
 * @param jsonParams
 * @param done shared variable to record whether the task has been done
 * @param m mutex for editing 'done'
 * @param wsBuf streamBuf to record std::cout
 */
void performTask(boost::json::object jsonParams, bool &done, std::mutex &m, std::streambuf *&wsBuf) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  auto oldBuf = std::cout.rdbuf();
  std::cout.rdbuf(wsBuf);
  libserver::server_provider::f();
  // ÃÓ»Îsimulate÷–µƒ¬ﬂº≠
  std::lock_guard<std::mutex> lock(m);
  done = true;
  std::cout.rdbuf(oldBuf); // reset cout
}

void EchoWebsock::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr,
                                   std::string &&message,
                                   const WebSocketMessageType &type) {
  //write your application logic here
  if (message.empty()) {
    wsConnPtr->send("please input your parameter");
    wsConnPtr->forceClose();
    return;
  }
  boost::json::error_code ec;
  auto decode_val = boost::json::parse(message, ec);
//  std::string tmp = boost::json::serialize(decode_val);
//  wsConnPtr->send("Your json:\n" + tmp);
  std::cout << "22";
  wsConnPtr->send("json format syntax: \n" + ec.message());
  if (ec.message() != "Success") {
    wsConnPtr->forceClose();
    return;
  }
  std::mutex m;
  bool done;
  std::stringstream ss;
  std::streambuf *wsBuf = ss.rdbuf();
  std::thread t(performTask, decode_val.as_object(), std::ref(done), std::ref(m), std::ref(wsBuf));
  do {
    std::lock_guard<std::mutex> lock(m);
    if (!ss.str().empty()) {
      wsConnPtr->send(ss.str());
      ss.clear(); // clear state
      ss.str(""); // clear content
    }
  } while (!done);
  t.join();
  wsConnPtr->forceClose();
}
void EchoWebsock::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
  //write your application logic here
}
void EchoWebsock::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
  //write your application logic here
}