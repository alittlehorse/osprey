add_executable(platform_server platform_server.cpp BuyerCtrl.cc EchoWebsock.cc)
target_link_libraries(platform_server libserver drogon)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../libserver/analysis_program/analysis_execute_script.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})