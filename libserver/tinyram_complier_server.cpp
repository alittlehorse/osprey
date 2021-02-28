/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <libserver/tinyram_complier_server.hpp>
#include <libserver/string_helper.hpp>
#include <tuple>
#include<unordered_map>
#include <regex>
#include <fstream>
#include <cassert>
#include <string>
#include<functional>


namespace libserver{
    bool tinyram_comlier_server::complie_tinyram(std::string &&file_path) {
        //turn file content to string and process the information
        //firstly,match the bounds information
        //then delete all comment
        //label the labels
        //transform all instructiontype argument to formal pattern:
        //op immflag des arg arg2
        std::unordered_map<std::string,int> d={
                {"arg1", 0},
                {"arg2", 0},
                {"immflag", 0},
                {"des", 0}
        };
        std::unordered_map<std::string,int> labels;
        std::string parent_dir,file_name,instr,arg;
        std::string head;

        int w,k;
        int addr = 0;

        vector<std::string> lines;

        std::regex head_re("^; TinyRAM V=2.000 M=vn W=([0-9]+) K=([0-9]+)$");
        std:smatch head_match;

        std::function<std::pair<std::string,std::string>()> p = [&file_path]()->std::pair<std::string,std::string> {
            auto pos = file_path.find_last_of('/');
            std::string filename=file_path.substr(pos+1);
            string_helper::replace_all(filename,".s","");
            std::string parentdir = file_path.substr(0,pos+1);
            return std::pair<std::string,std::string>(std::move(filename), std::move(parentdir));
        };
        file_name = p().first;
        parent_dir = p().second;
        std::ifstream in(file_path);
        std::ofstream out(parent_dir+file_name+"-processed_assembly.txt");

        //-------------------
        //create\open the $1-architecture_params.txt and write the params;
        if(getline(in,head)){
            if(std::regex_match(head,head_match,head_re)){
                if (head_match.size() == 3){
                    std::string w_str =  head_match[1].str();
                    std::string k_str = head_match[2].str();
                    w = stoi(w_str);
                    k = stoi(k_str);
                    std::ofstream arch_params_file(parent_dir+file_name+"-architecture_params.txt");
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
            if(head.empty())continue;
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
        std::function<int(std::string)> parse_reg = [](const std::string& arg)->int{
            return stoi(arg.substr(1));
        };
        std::function<std::tuple<int,int>(std::string)> parse_arg2 = [labels,parse_reg](std::string arg)->std::tuple<int,int>{
            if(arg[0]=='_') return std::make_tuple(1,labels.at(arg));
            else if (arg[0] == 'r'){
                return std::make_tuple<int,int>(0, parse_reg(arg));
            }
                //parse immediate value
            else{
                return std::make_tuple<int,int>(1, stoi(arg));
            }
        };

        // complie the tinyram to mechism pattern(formal pattern)
        for(auto l:lines){
            string_helper::replace_all(l,","," ");
            string_helper::replace_all(l,"  "," ");
            size_t pos = l.find(' ');
            instr = l.substr(0,pos);
            arg = l.substr(pos+1);
            auto args = libserver::string_helper::split(arg," ");
            assert(instruction_types.at(instr).size() == args.size());
            std::function process_args = [&d,&labels,&parse_reg,&parse_arg2](const std::string& t,const std::string& v){
                if(t=="arg2"){
                    std::tie(d["immflag"], d["arg2"]) = parse_arg2(v);
                }
                else{
                    d[t] = parse_reg(v);
                }
            };
            string_helper::zip(
                    process_args,
                    instruction_types.at(instr).begin(),
                    instruction_types.at(instr).end(),
                    args.begin());
            out<<libserver::string_helper::StrFormat<std::string,int,int,int,int>("%s %d %d %d %d",instr,d["immflag"],d["des"], d["arg1"], d["arg2"])<<'\n';
        }
        return true;
    }

}
