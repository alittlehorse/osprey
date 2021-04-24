add_executable(
        platform_server
        platform_server.cpp
        TestCtrl.cc
)
target_link_libraries(platform_server libserver drogon)
