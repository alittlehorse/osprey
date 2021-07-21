find_package(Drogon CONFIG REQUIRED)
add_executable(platform_server platform_server.cpp BuyerCtrl.cc EchoWebsock.cc)
target_include_directories(platform_server PRIVATE ${DROGON_INCLUDE_DIRS})
target_link_libraries(platform_server
        libserver
        Drogon::Drogon)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../libserver/analysis_program/analysis_execute_script.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#target_link_libraries(platform_server PRIVATE
#        Drogon)
