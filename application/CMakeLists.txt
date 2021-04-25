add_executable(
        platform_server
        platform_server.cpp
        BuyerCtrl.cc
)
target_link_libraries(platform_server libserver drogon)
