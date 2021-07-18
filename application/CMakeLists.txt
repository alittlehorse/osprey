find_package(Drogon CONFIG REQUIRED)
add_executable(platform_server platform_server.cpp BuyerCtrl.cc EchoWebsock.cc)
target_include_directories(platform_server PRIVATE ${DROGON_INCLUDE_DIRS})
target_link_libraries(platform_server
        libserver
        Drogon::Drogon)
#target_link_libraries(platform_server PRIVATE
#        Drogon)
