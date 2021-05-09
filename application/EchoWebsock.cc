#include "EchoWebsock.h"
/**
 *
 * @param done shared variable to record whether the task has been done
 * @param m mutex for editing 'done'
 * @param wsBuf streamBuf to record std::cout
 */
void performTask(bool &done, std::mutex &m, std::streambuf *&wsBuf) {
  auto oldBuf = std::cout.rdbuf();
  std::cout.rdbuf(wsBuf);
  std::cout << "start to perform task:\n";
  for (int second = 0; second < 10; second++) {
    std::string msg = std::to_string(second);
    std::cout << msg << std::endl;
    sleep(1);
  }
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
  std::string tmp = boost::json::serialize(decode_val);
  wsConnPtr->send("Your json:\n" + tmp);
  wsConnPtr->send("json format syntax: \n" + ec.message());
  if (ec.message() != "Success") {
    wsConnPtr->forceClose();
    return;
  }
  std::mutex m;
  bool done;
  std::stringstream ss;
  std::streambuf *wsBuf = ss.rdbuf();
  std::thread t(performTask, std::ref(done), std::ref(m), std::ref(wsBuf));
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