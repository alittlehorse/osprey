
#include <sys/socket.h>
#include <netinet/in.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <cstdio>


#include <libserver/network_server.hpp>

using namespace std;

struct event_base* base;


void onAccept(evutil_socket_t iSvrFd, short what, void *arg)
{
    int iCliFd;
    struct sockaddr_in sCliAddr;
    socklen_t iSinSize = sizeof(sCliAddr);
    iCliFd = accept(iSvrFd, (struct sockaddr*)&sCliAddr, &iSinSize);
    // 连接注册为新事件 (EV_PERSIST为事件触发后不默认删除)
    printf("connect from %s",iCliFd);

}

int main()
{
    libserver::network_server network("127.0.0.1",10086);
    int iSvrFd = network.init();
    listen(iSvrFd, 10);

    // 初始化base
    base = event_base_new();
    struct event* evListen = event_new(base,iSvrFd,EV_READ|EV_PERSIST,onAccept,NULL);
    // 添加事件
    event_add(evListen, NULL);

    // 事件循环
    event_base_dispatch(base);
    return 0;

}
