#include <libserver/ram_ppsnark_server.hpp>

using namespace libserver;

int main()
{
    libserver::proof_program p("avarage");
    libserver::ram_ppsnark_server server(p);
    auto proof =  server.construct_proof();
}
