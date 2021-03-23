/** @file
 *****************************************************************************
osprey server:
 1. server_provider class provide the server of prover(Data Seller)
 2. server_requester class provide the server of requester(Data Buyer)

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef OSPREY_OSPREY_SERVER_HPP
#define OSPREY_OSPREY_SERVER_HPP

//TODO::add network socket


#include<libserver/proof_systems/groth16_server.hpp>

class server_provider {
public:
    void on_ready(const std::string&& config);
    bool on_generate_and_serialize_proof();
private:
    libserver::proof_params_config* _vp;
    libserver::groth16_server* s;
};


class server_requester {
public:
    bool on_complier_tinyram();
    bool on_generate_key_pair();
    bool on_verify();
    void on_ready(const std::string&& config);

private:
    libserver::proof_params_config* _vp;
    libserver::groth16_server* s;
};


#endif //OSPREY_OSPREY_SERVER_HPP
