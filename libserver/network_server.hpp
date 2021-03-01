//
// Created by alittlehorse on 2/28/21.
//

#ifndef OSPREY_NETWORK_SERVER_HPP
#define OSPREY_NETWORK_SERVER_HPP


#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

namespace libserver{
    class network_server {
    public:
        network_server(const char *ip,const int port){
            this->ip = ip;
            this->port =port;
        }
        int init(){
            int iSvrFd;
            struct sockaddr_in sSvrAddr;
            memset(&sSvrAddr, 0, sizeof(sSvrAddr));
            sSvrAddr.sin_family = AF_INET;
            sSvrAddr.sin_addr.s_addr = inet_addr(ip);
            sSvrAddr.sin_port = htons(port);

            // 创建tcpSocket（iSvrFd），监听本机8888端口
            iSvrFd = socket(AF_INET, SOCK_STREAM, 0);
            bind(iSvrFd, (struct sockaddr*)&sSvrAddr, sizeof(sSvrAddr));
            return iSvrFd;
        }

        static int close(int fd){
            close(fd);
        }

    private:
        int port;
        const char *ip;
    };
}



#endif //OSPREY_NETWORK_SERVER_HPP
