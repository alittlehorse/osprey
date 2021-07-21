#include <drogon/drogon.h>

#include <filesystem>
using namespace drogon;
int main() {
  int port = 3498;
  printf("Your port is %d\n",port);
  app()
      .setLogPath("./")
      .setLogLevel(trantor::Logger::kWarn)
      .addListener("0.0.0.0", port)
          //.setThreadNum(16)
          //.enableRunAsDaemon()
      .run();
}