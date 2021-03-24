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
    bool on_complier_tinyram();
    bool on_generate_key_pair();
    bool on_verify();
    bool on_lock_pay(double money);
    void on_ready(const std::string&& config,const std::string& smart_contract_address);
    const std::string& get_address();

private:
    libserver::proof_params_config* _vp;
    libserver::groth16_server* s;
    std::string smart_contract_address;
};

class osprey_plateform{
private:
    //TODO: embedded plateform_address;
    static std::string plateform_address;
    std::string server_address;
    std::string requester_address;
    double lock_money;
public:
    static const std::string& get_address();
    void submit_requester_address(const std::string& requester_address);
    void submit_server_address(const std::string&);
    static bool on_lock(double lock_money);
    static bool on_finish_and_pay();
};


#endif //OSPREY_OSPREY_SERVER_HPP
