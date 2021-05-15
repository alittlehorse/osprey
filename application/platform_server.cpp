#include <drogon/drogon.h>

#include <filesystem>
using namespace drogon;
int main() {
  app()
      .setLogPath("./")
      .setLogLevel(trantor::Logger::kWarn)
      .addListener("0.0.0.0", 3498)
          //.setThreadNum(16)
          //.enableRunAsDaemon()
      .run();
}