#include <string>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <istream>
#include <fstream>


enum class request_state : unsigned int{
    request_server =0,
    quote = 1,
    reques_proof = 2,  //mean: begin to construct proof
    proof_pass = 3,
    already_paid = 4,
    proof_failed = 5,
    failed_paid = 5
};

enum class prover_state : unsigned int{
    prover_account = 0,
    primary_input =1,
    send_prover = 2,
};


using namespace std;

struct event_base* base;

static void on_quote(){
    printf("begin quote");
}
static void on_request_proof(){
    printf("begin on_request_proof");
}
static void on_request_server(){
    printf("begin on_request_server");
}
static void on_aready_paid(){
    printf("begin on_aready_paid");
}


static void
read_cb(struct bufferevent *bev, void *ctx)
{
    /* This callback is invoked when there is data to read on bev. */
    char buff[2048];
    struct evbuffer *input = bufferevent_get_input(bev);
    struct evbuffer *output = bufferevent_get_output(bev);
    int len = evbuffer_remove (input, buff, evbuffer_get_length(input) );
    std::string_view tag(buff,6);
    std::string_view VR(buff+6,1);
    std::string_view length(buff+7,2);
    //int l = to_len(length);
    std::string v(buff+9,len-9);
    ofstream out("Hello,world.txt");
    out<<v;
}

static void
event_cb(struct bufferevent *bev, short events, void *ctx)
{
    if (events & BEV_EVENT_ERROR)
        perror("Error from bufferevent");
    if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
        bufferevent_free(bev);
    }
}
static void
accept_conn_cb(struct evconnlistener *listener,
               evutil_socket_t fd, struct sockaddr *address, int socklen,
               void *ctx)
{
    /* We got a new connection! Set up a bufferevent for it. */
    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent *bev = bufferevent_socket_new(
            base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL , event_cb, NULL);

    bufferevent_enable(bev, EV_READ|EV_WRITE);
}
static void
accept_error_cb(struct evconnlistener *listener, void *ctx)
{
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d (%s) on the listener. "
                    "Shutting down.\n", err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

int
main(int argc, char **argv)
{
    struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;

    int port = 10086;

    if (argc > 1) {
        port = atoi(argv[1]);
    }
    if (port<=0 || port>65535) {
        puts("Invalid port");
        return 1;
    }

    base = event_base_new();
    if (!base) {
        puts("Couldn't open event base");
        return 1;
    }

    /* Clear the sockaddr before using it, in case there are extra
     * platform-specific fields that can mess us up. */
    memset(&sin, 0, sizeof(sin));
    /* This is an INET address */
    sin.sin_family = AF_INET;
    /* Listen on 0.0.0.0 */
    sin.sin_addr.s_addr = htonl(0);
    /* Listen on the given port. */
    sin.sin_port = htons(port);
    printf("Hello,World!");
    listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
                                       LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
                                       (struct sockaddr*)&sin, sizeof(sin));
    if (!listener) {
        perror("Couldn't create listener");
        return 1;
    }
    evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_dispatch(base);
    return 0;
}

