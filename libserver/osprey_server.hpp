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

#include<libserver/proof_systems/groth16_server.hpp>


class server_provider {
public:
    void on_ready(const std::string&& config,const std::string& smart_contract_address);
    bool on_generate_and_serialize_proof();
    const std::string& get_address();
private:
    libserver::proof_params_config* _vp;
    libserver::groth16_server* s;
    std::string smart_contract_address;
};


class server_requester {
public:
    //bool on_complier_tinyram();
    bool on_lock_pay(int money);
    void on_ready(const std::string&& config,const std::string& smart_contract_address,const std::string& private_key);
    const std::string& get_address();

private:
    std::string account;
    std::string private_key;
    const std::string& get_private_key();
};

class osprey_plateform{
private:
    std::string server_address;
    libserver::proof_params_config* _vp;
    libserver::groth16_server* s;
public:
    void set_server_address(const std::string& account);
    bool on_finish_and_pay();
    bool on_verify();
    bool on_ready(const std::string& config);
    bool on_generate_keypair();
};


#endif //OSPREY_OSPREY_SERVER_HPP
