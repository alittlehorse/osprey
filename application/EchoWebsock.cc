#include "EchoWebsock.h"
void performTask(bool &done, std::mutex &m, std::streambuf *&wsBuf) {
  std::cout.rdbuf(wsBuf);
  std::cout << "start to perform task:\n";
  for (int second = 0; second < 10; second++) {
    std::string msg = std::to_string(second);
    std::cout << msg << std::endl;
    sleep(1);
  }
  std::lock_guard<std::mutex> lock(m);
  done = true;
}

void EchoWebsock::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr,
                                   std::string &&message,
                                   const WebSocketMessageType &type) {
  //write your application logic here
}
void EchoWebsock::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
  std::mutex m;
  bool done;
  std::stringstream ss;
  std::streambuf *wsBuf = ss.rdbuf();
  std::thread t(performTask, std::ref(done), std::ref(m), std::ref(wsBuf));

  do {
    sleep(0.5);
    std::lock_guard<std::mutex> lock(m);
    std::string cur;
    if (!ss.str().empty()) {
      //ss >> cur;
      wsConnPtr->send(ss.str());
      ss.clear(); // clear state
      ss.str(""); // clear content
    }
  } while (!done);
  t.join();
  //write your application logic here
}
void EchoWebsock::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
  //write your application logic here
}