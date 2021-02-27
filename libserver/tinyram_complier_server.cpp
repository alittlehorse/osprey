/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <libserver/tinyram_complier_server.hpp>
#include <libserver/string_helper.hpp>
#include <regex>
#include <fstream>
#include <cassert>
#include <unordered_map>


namespace libserver{
    bool tinyram_comlier_server::complie_tinyram(std::string &&file_path) {
        //turn file content to string and process the information
        //firstly,match the bounds information
        //then delete all comment;
        //relpace all instruction type;
        std::string parent_dir,file_name;
        std::string head;

        int w,k;

        int addr = 0;
        vector<std::string> lines;

        parent_dir = tinyram_comlier_server::parent_dir();
        file_name  = tinyram_comlier_server::file_name();
        std::regex head_re("^; TinyRAM V=2.000 M=vn W=([0-9]+) K=([0-9]+)$");
        std:smatch head_match;
        std::ifstream in(file_path);


        //-------------------
        //create\open the $1-architecture_params.txt and write the params;
        if(getline(in,head)){
            if(std::regex_match(head,head_match,head_re)){
                if (head_match.size() == 3){
                    std::string w_str =  head_match[1].str();
                    std::string k_str = head_match[2].str();
                    w = stoi(w_str);
                    k = stoi(k_str);
                    std::string arch_params_file_name = std::move(parent_dir+file_name+"-architecture_params.txt");
                    std::ofstream arch_params_file(arch_params_file_name);
                    arch_params_file << w_str.append(" ");
                    arch_params_file <<k_str;
                    arch_params_file.close();
                }
            }
        }
        else return false;
        // delete the comments
        // write the labels[lale] = addr
        // append the processed-line to lines;
        while(getline(in,head)){
            if(size_t indx = head.find(';');indx !=  string::npos){
                head = head.substr(0,indx);
                string_helper::trim(head);
            }
            if(size_t indx = head.find(':');indx !=  string::npos){
                std::string&& lable = std::move(head.substr(0,indx));
                labels[lable] = addr;
                head = head.substr(indx);
                string_helper::trim(head);
            }
            if(!head.empty()){
                head.shrink_to_fit();
                lines.push_back(head);
                addr += 2*(w/8);
            }
        }
        std::string instr,arg;
        vector<string> args;
        std::unordered_map<std::string,int> d={
                {"arg1", 0},
                {"arg2", 0},
                {"immflag", 0},
                {"des", 0}
        };


        // complie the tinyram to mechism formal
        std::ostream out(file_path+file_name+"processed_assembly.txt");
        for(auto l:lines){
            string_helper::replace_all(l,","," ");
            string_helper::replace_all(l,"  "," ");
            size_t pos = l.find(' ');
            instr = l.substr(0,pos);
            arg = l.substr(pos);
            args = libserver::string_helper::split(arg," ");
            assert(instruction_types.at(instr).size() ==args.size());
            string_helper::zip(
                    [d,this](std::string t,std::string v){
                        if(t=="arg2"){
                            d.at("immflag"), d.at("arg2") = parse_arg2(v);
                        }
                        else{
                            d[t] = parse_reg(v);
                        }
                    },
                    instruction_types.at(instr).begin(),
                    instruction_types.at(instr).end(),
                    args.begin());
            out<<"";
        }

    }

    std::string&& tinyram_comlier_server::parent_dir() {
        return "";
    }

    std::tuple<int, int> tinyram_comlier_server::parse_arg2(std::string s) {
        if(s[0] == '_'){
            return std::make_tuple(1,labels[s]);
        }

        else if (s[0] == 'r'){
            return std::make_tuple<int,int>(0, parse_reg(s));
        }

        else{
            return std::make_tuple<int,int>(1, stoi(s));
        }

    }

    int tinyram_comlier_server::parse_reg(std::string s) {
        std::string a = s.substr(1);
        return stoi(a);
    }


}
