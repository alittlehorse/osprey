# include <libserver/ram_ppsnark_server.hpp>

using namespace libserver;

int main()
{
    proof_program p("avarage");
    ram_ppsnark_server ppsnark_server(p);
    auto proof = ppsnark_server.construct_proof();
//bool bit = ppsnark_server.test_proof();

}
