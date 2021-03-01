
#include <sys/socket.h>
#include <netinet/in.h>
#include <event.h>
#include <cstdio>
#include <cstdlib>

#include <libserver/network_server.hpp>

using namespace std;

struct event_base* base;

void onRead(int iCliFd, short iEvent, void *arg)
{
    int iLen;
    char buf[1500];
    iLen = recv(iCliFd, buf, 1500, 0);
    if (iLen <= 0) {

        struct event *pEvRead = (struct event*)arg;
        event_del(pEvRead);
        delete pEvRead;
        libserver::network_server::close(iCliFd);
        return;
    }
    buf[iLen] = 0;
    printf("Client Close %s",buf );
}


void onAccept(int iSvrFd, short iEvent, void *arg)
{
    int iCliFd;
    struct sockaddr_in sCliAddr;
    socklen_t iSinSize = sizeof(sCliAddr);
    iCliFd = accept(iSvrFd, (struct sockaddr*)&sCliAddr, &iSinSize);
    // 连接注册为新事件 (EV_PERSIST为事件触发后不默认删除)
    struct event *pEvRead = new event;
    event_set(pEvRead, iCliFd, EV_READ|EV_PERSIST, onRead, pEvRead);
    event_base_set(base, pEvRead);
    event_add(pEvRead, NULL);
}

int main()
{
    libserver::network_server network("127.0.0.1",10086);
    int iSvrFd = network.init();
    listen(iSvrFd, 10);

    // 初始化base
    base = event_base_new();
    struct event evListen;
    // 设置事件
    event_set(&evListen, iSvrFd, EV_READ|EV_PERSIST, onAccept, NULL);

    // 设置为base事件
    event_base_set(base, &evListen);
    // 添加事件
    event_add(&evListen, NULL);

    // 事件循环
    event_base_dispatch(base);
    return 0;

}
